#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "Wire.h"

// Configuration for temperature and humidity
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define DHTPIN 25
DHT dht(DHTPIN, DHTTYPE);

// Configuration for lux
#define address 0x23 // I2C address 0x23
uint8_t buf[4] = {0};
uint16_t data, data1;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
}

void loop() {
  // Wind
  int wind = read_wind();
  Serial.print("Wind speed : ");
  Serial.println(wind);

  // Temperature and humidity
  float* temp_hum_val = read_temp_and_humidity();
  Serial.print("Humidity : ");
  Serial.print(temp_hum_val[0]);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temp_hum_val[1]);
  Serial.println("°C");

  // Luminosity
  int lux = read_lux();
  Serial.print("Lux : ");
  Serial.print(lux);
  Serial.println(" lx");

  delay(500);
}

/**
  Read wind into a scale in m/s
*/
int read_wind() {
  int sensorValue = analogRead(A0);
  float outvoltage = sensorValue * (3.3 / 4095.0);
  int level = 6 * outvoltage; // The level of wind speed is proportional to the output voltage.
  return level;
}

/**
  Reading temperature or humidity takes about 250 milliseconds!
  Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
*/
float* read_temp_and_humidity() {
  static float temp_hum_val[2] = {0};
  if (!dht.readTempAndHumidity(temp_hum_val)) {
    return temp_hum_val;
  } else {
    Serial.println("Failed to get temperature and humidity value.");
    temp_hum_val[0] = 0;
    temp_hum_val[1] = 0;
    return temp_hum_val;
  }
}

/**
  Read luminosity
*/
int read_lux() {
  readReg(0x10, buf, 2); // Register address 0x10
  data = buf[0] << 8 | buf[1];
  float lux = (((float)data )/1.2);
  return lux;
}

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