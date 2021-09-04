#include "moisture.h"
#include <CRC.h>
#include <FastLED.h>

#define SENSOR_AMOUNT 4
#define NUM_LEDS 4
#define LED_PIN A5
#define LED_POWER_PIN 7

struct SensorData{
  uint8_t sensPin;
  uint8_t powerPin;
  float alpha;
};

SensorData sensorData[SENSOR_AMOUNT] = {{A0, 2, 0.5}, {A1, 3, 0.5}, {A2, 4, 0.5}, {A3, 5, 0.5}};

MoistureSensor sensors[SENSOR_AMOUNT];

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < SENSOR_AMOUNT; i++) {
    sensors[i].init(sensorData[i].sensPin, sensorData[i].powerPin, sensorData[i].alpha);
  }

  pinMode(LED_POWER_PIN, OUTPUT);
  digitalWrite(LED_POWER_PIN, HIGH);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Red;
  }
  FastLED.setBrightness(255);
  FastLED.show();
}

void loop() {
  for(uint16_t i = 0; i < SENSOR_AMOUNT; i++){
    uint16_t val = (uint16_t) sensors[i].getMoisture();
    uint8_t crcArr[] = {(uint8_t) (i >> 8), (uint8_t) i, (uint8_t) (val >> 8), (uint8_t) val};
    uint16_t crc = CRC::crc16(crcArr, sizeof(crcArr));
    uint8_t sendArr[] = {(uint8_t) (i >> 8), (uint8_t) i, (uint8_t) (val >> 8), (uint8_t) val, (uint8_t) (crc >> 8), (uint8_t) crc};
    for(int j = 0; j < 6; j += 2){
      uint8_t arr[] = {sendArr[j], sendArr[j+1]};
      char cstr[sizeof(uint8_t)*2];
      itoa(arr[0], cstr, 16);
      if(strlen(cstr) == 2){
        Serial.print(cstr);
      } else {
        uint8_t diff = 2 - strlen(cstr);
        for(int zi = 0; zi < diff; zi++){
          Serial.print(0);
        }
        Serial.print(cstr);
      }
      itoa(arr[1], cstr, 16);
      if(strlen(cstr) == 2){
        Serial.print(cstr);
      } else {
        uint8_t diff = 2 - strlen(cstr);
        for(int zi = 0; zi < diff; zi++){
          Serial.print(0);
        }
        Serial.print(cstr);
      }
    }
    Serial.print('\n');
    delay(2500);
  }
}
