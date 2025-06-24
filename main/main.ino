void setup() {
  Serial.begin(9600);
}

void loop() {
  int wind = read_wind();
  Serial.print(wind);
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