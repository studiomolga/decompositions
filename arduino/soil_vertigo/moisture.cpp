#include "Arduino.h"
#include "moisture.h"

MoistureSensor::MoistureSensor()
{
//  Serial.println(powerPin);


  smoothVal = 0;

}

void MoistureSensor::init(uint8_t sensPin, uint8_t powerPin, float alpha){
  _sensPin = sensPin;
  _powerPin = powerPin;
  _alpha = alpha;

//  Serial.println(_powerPin);
  
  pinMode(_powerPin, OUTPUT);
  digitalWrite(_powerPin, LOW);
}

uint16_t MoistureSensor::getMoisture()
{
//  Serial.println(_powerPin);
  // returns the value smoothed with an exponential filter
  float rawVal = getVal();
  smoothVal = (rawVal * _alpha) + (smoothVal * (1 - _alpha));
  return smoothVal;
}

uint16_t MoistureSensor::getVal()
{
//  Serial.println(_powerPin);
  digitalWrite(_powerPin, HIGH);
  delay(100);
  uint16_t val = analogRead(_sensPin);
  digitalWrite(_powerPin, LOW);
  delay(100);
  return val;
}
