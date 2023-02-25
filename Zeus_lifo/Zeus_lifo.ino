#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t sc = 8;
uint16_t sv[sc];

void setup()
{
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){3, 4, 5, 6, 7, 8, 9, 10}, sc);
  qtr.setEmitterPin(2);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);


  for (uint16_t i = 0; i < 100; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); 
 
  delay(1000);
}

void loop()
{
  
  uint16_t position = qtr.readLineBlack(sv);

  for (uint8_t i = 0; i < sc; i++)
  {
    Serial.print(sv[i]);
    Serial.print('\t');
  }
  Serial.println(position);

  delay(250);
}
