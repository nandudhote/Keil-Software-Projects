#include <Wire.h>

const byte i2c1 = 0x0A;  // CT1 MCU I2C ADDRESS
const byte i2c2 = 0x10;  // CT2 MCU I2C ADDRESS
const byte i2c3 = 0x52;  // CT3 MCU I2C ADDRESS

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  sendData(i2c1, "Hello CT");  // Send string
  //delay(1000);

  Wire.requestFrom((uint8_t)i2c1, (uint8_t)19);  // slave address, number of bytes to read
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
  delay(100);
}

void sendData(const byte i2cAddr, const char* str) {
  Wire.beginTransmission(i2cAddr);
  Wire.write((const uint8_t*)str, strlen(str));
  Wire.endTransmission();
}
