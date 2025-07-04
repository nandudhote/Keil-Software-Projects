#include <Wire.h>

const byte CT1I2cAddr = 0x0A;  // CT1 MCU I2C ADDRESS
// const byte CT2I2cAddr = 0x10;  // CT2 MCU I2C ADDRESS
// const byte CT3I2cAddr = 0x52;  // CT3 MCU I2C ADDRESS

unsigned long startMillis = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  readCurrent(CT1I2cAddr);
  // readCurrent(CT2I2cAddr);
  // readCurrent(CT3I2cAddr);
}


void readCurrent(const byte i2cAddr) {
  // 0x0A // 0x10 // 0x52
  float Current = 0.0;
  unsigned int duration = 2000;
  Wire.requestFrom((uint8_t)i2cAddr, (uint8_t)2, (uint8_t) false);
  startMillis = millis();
  while (millis() - startMillis < duration) {
    if (Wire.available()) {
      unsigned int mergedCurAdc = (Wire.read() * 100) + Wire.read();
      Serial.print("i2cAddr : ");
      Serial.print(i2cAddr);
      Serial.print(" ");
      Serial.println(mergedCurAdc);
    }
  }
}