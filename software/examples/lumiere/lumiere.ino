
// LUMIERE 
#include "Wire.h"
#define address 0x23                 //I2C address 0x23


uint8_t buf[4] = {0};
uint16_t data, data1;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
}


void loop()
{
  float Lux = lux_value();
  Serial.print("LUX:");
  Serial.print(Lux);
  Serial.print("lx");
  Serial.print("\n");
  delay(500);
}

int lux_value() {
  readReg(0x10, buf, 2);              //Register address 0x10
  data = buf[0] << 8 | buf[1];
  float Lux = (((float)data )/1.2);
  return Lux;
}
  
 // Serial.print("LUX:");
 // Serial.print(Lux);
 // Serial.print("lx");
 // Serial.print("\n");
 // delay(500);

uint8_t readReg(uint8_t reg, const void* pBuf, size_t size)
{
  if (pBuf == NULL) {
    Serial.println("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  Wire.beginTransmission(address);
  Wire.write(reg);
  if ( Wire.endTransmission() != 0) {
    return 0;
  }
  delay(20);
  Wire.requestFrom(address, (uint8_t) size);
  for (uint16_t i = 0; i < size; i++) {
    _pBuf[i] = Wire.read();
  }
  return size;
}