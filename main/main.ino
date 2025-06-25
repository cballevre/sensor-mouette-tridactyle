#include "Grove_Temperature_And_Humidity_Sensor.h"

// Configuration for temperature and humidity
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN 25
DHT dht(DHTPIN, DHTTYPE);

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