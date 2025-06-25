// TEMPERATURE
// Telechargement de la library DFRobot_MCP9808
// SMAPLE 1- GET TEMPERATURE
#include "DFRobot_MCP9808.h"
#define I2C_ADDRESS  MCP9808_ADDRESS_7
DFRobot_MCP9808_I2C mcp9808(&Wire, I2C_ADDRESS);

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  while(!mcp9808.begin()){
    Serial.println("begin failed!");
    delay(1000);
  } Serial.println("begin success!");

  if(!mcp9808.wakeUpMode()){
    Serial.println("Register locked, Please unlock!");
  }else{
    Serial.println("Wake up sensor successfully, can read the temperature!");
  }

  if(mcp9808.setResolution(RESOLUTION_0_125)){
    Serial.println("Set temp resolution successfully!");
  }else{
    Serial.println("parameter error!");
  }
}

void loop()
{
  Serial.print("Temperature is ="); 
  Serial.print(mcp9808.getTemperature());
  Serial.println(" C");
  delay(1000);
}
