#include <Wire.h>

const byte CT1I2cAddr = 0x0A;  // CT1 MCU I2C ADDRESS

unsigned long startMillis = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();   // Initialize I2C
}

void loop() {
  sendData(CT1I2cAddr, "Hello CT");  // Send string
  delay(100);
  readCurrent(CT1I2cAddr);
  delay(1000);
}

void sendData(const byte i2cAddr, const char* str) {
  Wire.beginTransmission(i2cAddr);
  Wire.write((const uint8_t*)str, strlen(str));
  Wire.endTransmission();
}

void readCurrent(const byte i2cAddr) {
  Wire.requestFrom((uint8_t)i2cAddr, (uint8_t)2, (uint8_t) false);
  startMillis = millis();
  while (millis() - startMillis < 2000) {
    if (Wire.available() >= 2) {
      unsigned int mergedCurAdc = (Wire.read() * 100) + Wire.read();
      Serial.print("i2cAddr : ");
      Serial.print(i2cAddr);
      Serial.print(" ");
      Serial.println(mergedCurAdc);
      break;
    }
  }
}
