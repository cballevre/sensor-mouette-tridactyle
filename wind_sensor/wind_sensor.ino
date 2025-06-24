
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(A0);
  Serial.print("sensorValue :");
  Serial.println(sensorValue);
  float outvoltage = sensorValue * (3.3 / 4095.0);
  Serial.print("outvoltage = ");
  Serial.print(outvoltage);
  Serial.println("V");
  int Level = 6 * outvoltage;//The level of wind speed is proportional to the output voltage.
  Serial.print("wind speed is ");
  Serial.print(Level);
  Serial.println(" level now");
  Serial.println();
  delay(500);
}

