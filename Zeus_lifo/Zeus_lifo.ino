#include <QTRSensors.h>
#define ain1 A3
#define ain2 A4
#define pwm_a 10
#define bin1 A5
#define bin2 A6
#define pwm_b 9
int sa = 0;
int sb = 0;
int temp = 0;
QTRSensors qtr;
const uint8_t sc = 8;
uint16_t sv[sc];
int P = 0;
int I = 0;
int D = 0;
float Kp = 0.08;
float Ki = 0.001;
float Kd = 1;
int error = 0;
int preverror = 0;
void setup()
{
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(pwm_a, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(pwm_b, OUTPUT);
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){3, 4, 5, 6, 7, 8, 11, 12}, sc);
  qtr.setEmitterPin(2);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  calib();
  
  digitalWrite(LED_BUILTIN, LOW); 
 
  delay(1000);
}

void loop()
{
  
 pid();
 mspeed(0,0);
 
  
}
void mspeed(int sa, int sb){
  if(sa < 0){
    sa = -sa;
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, HIGH);
    analogWrite(pwm_a, sa);
    }else{
      digitalWrite(ain1, HIGH);
      digitalWrite(ain2, LOW);
      analogWrite(pwm_a, sa);
      }
  if(sb < 0){
    sb = -sb;
    digitalWrite(bin1, LOW);
    digitalWrite(bin2, LOW);
    analogWrite(pwm_b, sb);
    }else{
      digitalWrite(bin1, HIGH);
      digitalWrite(bin2, LOW);
      analogWrite(pwm_b, sb);
      }
  }

void calib(){
  mspeed(-100, 100);
  for (uint16_t i = 0; i < 150; i++)
  {
    qtr.calibrate();
  }
  mspeed(0,0);
  }

void pid(){
    while(1){
    uint16_t pos = qtr.readLineBlack(sv);
    error = 3500 - pos;
    if(sv[0]>700 && sv[1]>700 && sv[2]>700 && sv[3]>700 && sv[4]>700 && sv[5]>700 && sv[6]>700 && sv[7]>700){
      return;
      }
   
      
      
 
  if(pos ==0){
    if(sa>sb){
      mspeed(220,0);
      }
    else if(sb > sa){
        mspeed(0,220);
        }
    else if(sa == sb){
          mspeed(220,0);
          }
    }
    else{
      P = error;
      I = I + error;
      D = error - preverror;
      preverror = error;

      int speedchange = P*Kp + I*Ki + D*Kd;

      int msa = 250 + speedchange;
      int msb = 250 - speedchange;

      if(msa > 250){
        msa = 250;
        }
      if(msb > 250){
        msb = 250;
        }
      if(msa < -30){
        msa = -30;
        }
      if(msb < -30){
        msb = -30;
        }

      mspeed(msa, msb);
      } 
    }
  }
  
