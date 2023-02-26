#include <QTRSensors.h>
#define ain1 A4
#define ain2 A3
#define pwm_a 10
#define bin1 A6
#define bin2 A5
#define pwm_b 11
uint8_t sa = 0;
uint8_t sb = 0;
QTRSensors qtr;
const uint8_t sc = 8;
uint16_t sv[sc];
uint16_t P = 0;
uint16_t I = 0;
uint16_t D = 0;
float Kp = 0.07;
float Ki = 0.005;
float Kd = 0.7;
uint16_t error = 0;
uint16_t preverror = 0;
void setup()
{
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(pwm_a, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(pwm_b, OUTPUT);
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){3, 4, 5, 6, 7, 8, 9, 12}, sc);
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
  
  

  
}
void mspeed(uint8_t sa, uint8_t sb){
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
  for (uint16_t i = 0; i < 100; i++)
  {
    qtr.calibrate();
  }
  mspeed(0,0);
  }

void pid(){
  uint16_t pos = qtr.readLineBlack(sv);
  error = 3500 - pos;
  if(pos ==0){
    if(sa>sb){
      mspeed(150,0);
      }else if(sb > sa){
        mspeed(0,150);
        }else if(sa == sb){
          mspeed(0,150);
          }
    }else{
      P = error;
      I = I + error;
      D = error - preverror;
      preverror = error;

      uint16_t speedchange = P*Kp + I*Ki + D*Kd;

      uint16_t msa = 150 + speedchange;
      uint16_t msb = 150 - speedchange;

      if(msa > 150){
        msa = 150;
        }
      if(msb > 150){
        msb = 150;
        }
      if(msa < 0){
        msa = 0;
        }
      if(msb > 0){
        msb = 0;
        }

      mspeed(msa, msb);
      } 
  }
