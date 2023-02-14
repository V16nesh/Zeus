#include <QTRSensors.h>
QTRSensors qtr;

const uint8_t sc = 8;
uint16_t sv[sc];
int p;
int i;
int d;
int preverr = 0;


float kp;
float kd;
float ki;

void setup()
{
  
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){3, 4, 5, 6, 7, 8, 9, 10}, sc);
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

  

  
  
      

}

void calib(){
  for (uint16_t i = 0; i < 100; i++)
  {
    qtr.calibrate();
  }
}

void pid(){
  uint16_t pos = qtr.readLineBlack(sv);
  int err = 3500 - pos;
  p = err;
  d = err-preverr;
  i = err+i;
  preverr = err;
  
  }
