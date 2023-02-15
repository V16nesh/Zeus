#include <QTRSensors.h>
QTRSensors qtr;
#define PWM1 3
#define AIN1 A1
#define AIN2 A2
#define PWM2 4
#define BIN1 A3
#define BIN2 A4

uint8_t thrs = 700;
uint8_t basesa = 100;
uint8_t basesb = 100;

const uint8_t sc = 8;
uint16_t sv[sc];
int p;
int i;
int d;
int preverr = 0;


float kp;
float kd;
float ki;

uint8_t sa = 0;
uint8_t sb = 0;

void setup()
{
  pinMode(PWM1, OUTPUT); 
  pinMode(AIN1, OUTPUT); 
  pinMode(AIN2, OUTPUT); 
  pinMode(PWM2, OUTPUT); 
  pinMode(BIN1, OUTPUT); 
  pinMode(BIN2, OUTPUT); 
  
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){5, 6, 7, 8, 9, 10, 11, 12}, sc);
  qtr.setEmitterPin(2);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 

  calib();
  digitalWrite(LED_BUILTIN, LOW); 
  
  Serial.begin(9600);
  
  delay(1000);
}

void loop()
{

  uint16_t pos = qtr.readLineBlack(sv);

  Serial.println(pos);
  
  
      

}



char slt_turn(unsigned char fnd_l, unsigned char fnd_s, unsigned char fnd_r){
  if(fnd_l)
    return 'l';
  else if(fnd_s)
    return 's';
  else if(fnd_r)
    return 'r';
  else 
    return 'b'; 
  }


void turn(char direct){
  switch(direct){
    case 'l':
    break;
    
    case 'r':
    break;

    case 'b':
    break;

    case 's':
    break;
    
    }
  
  }


void calib(){
  for (uint16_t i = 0; i < 100; i++)
  {
    qtr.calibrate();
  }
}

void maze(){
  
  while(1){
    pid();
    unsigned char fnd_l = 0;
    unsigned char fnd_r = 0;
    unsigned char fnd_s = 0;
    qtr.readLineBlack(sv);
    if(sv[0] > thrs){
      fnd_l = 1;
      }
    else if(sv[7] > thrs){
      for(int i = 0; i<100; i++){
        qtr.readLineBlack(sv);
        if(sv[0] > thrs){
          fnd_l = 1;
          delay(200);
          goto bailout;
          }
        
        }
        fnd_r = 1;
      } 
      if(fnd_l == 1){
        delay(200);
        }
    
  
  
  


bailout:
  qtr.readLineBlack(sv);
  if(sv[1] > thrs || sv[2] > thrs || sv[3] > thrs || sv[4] > thrs || sv[5] > thrs || sv[6] > thrs){
    fnd_s = 1;
    }
qtr.readLineBlack(sv);
if(sv[0] > thrs && sv[1] > thrs && sv[2] > thrs && sv[3] > thrs && sv[4] > thrs && sv[5] > thrs && sv[6] > thrs && sv[7] > thrs)
break;




  }
}

void pid(){

  while(1){
   uint16_t pos = qtr.readLineBlack(sv);
  int err = 3500 - pos;
  p = err;
  d = err-preverr;
  i = err+i;
  preverr = err;

  uint16_t motorspeed = kp*p + ki*i + kd*d;
  sa = basesa + motorspeed;
  sb = basesa - motorspeed;

  if(sa>80){
    sa = 80;
    }
  if(sb>80){
    sb = 80;
    }
  if(sa<-20){
    sa = -20;
  }
  if(sb<-20){
    sb = -20;    
    }  
  movement(sa, sb);

  if(sv[0] > thrs || sv[7] > thrs){
    movement(50, 50);
    return;
    }
  if(sv[0] < thrs && sv[1] < thrs && sv[2] < thrs && sv[3] < thrs && sv[4] < thrs && sv[5] < thrs && sv[6] < thrs && sv[7]){
    movement(50, 50);
    return;
    }
  
  } 
    }
  

void movement(int Sa, int Sb){
  if(Sa<0){
    Sa = -Sa;
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(PWM1, Sa);
    }
    else{
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(PWM1, Sa);
      }
      
    if(sb<0){
    Sb = -Sb;
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    digitalWrite(PWM1, Sb);
    }
    else{
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      digitalWrite(PWM2, Sb);
      }
  }
