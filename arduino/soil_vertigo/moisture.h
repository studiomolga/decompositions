/*
  moisture sensor code for soil vertigo project
  erik overmeire
*/

#ifndef moisture_h
#define moisture_h

#include "Arduino.h"

class MoistureSensor
{
  public:
    MoistureSensor();
    void init(uint8_t sensPin, uint8_t powerPin, float alpha);
    uint16_t getMoisture();
  private:
    uint16_t getVal();
  
    uint8_t _sensPin;
    uint8_t _powerPin;
    float _alpha;
    float smoothVal;
};

#endif
