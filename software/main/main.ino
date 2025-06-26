#include "Wire.h"

// Library for temperature and humidity
#include "Grove_Temperature_And_Humidity_Sensor.h"

// Library for temperature
#include "DFRobot_MCP9808.h"

// Library for RTC
#include <DS3231.h>

// Library for SD 
#include "FS.h"
#include "SD.h"
#include "SPI.h"


// Configuration for temperature and humidity
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define DHTPIN 25
DHT dht(DHTPIN, DHTTYPE);

// Configuration for lux
#define address 0x23 // I2C address 0x23
uint8_t buf[4] = {0};
uint16_t data, data1;

// Configuration for temperature
#define I2C_ADDRESS  MCP9808_ADDRESS_7
DFRobot_MCP9808_I2C mcp9808(&Wire, I2C_ADDRESS);

// Configuration for RTC
DS3231 Clock;
bool Century = false;
bool h12;
bool PM;

// Configuration for SD 
const int cspin_SD=5;
String datafile = "/data.csv"; 
String dataline =";" ;


void setup() {
  Serial.begin(9600);
  while(!Serial);

  Wire.begin();
  dht.begin();

  setup_temperature();

  // SD
  if(!SD.begin(cspin_SD)){
     Serial.println("Card Mount Failed");
     return;
  }
  if (SD.exists(datafile) == false) {
  File file = SD.open(datafile, FILE_WRITE);
  file.println("datetime;wind;humidity;temp_dht;lux;temp_mcp");
  file.close();
}


}

void loop() {

  // Date and time
  String datetime = read_datetime();
  Serial.print("Datetime : ");
  Serial.println(datetime);


  // Wind
  int wind = read_wind();
  Serial.print("Wind speed : ");
  Serial.println(wind);

  // Temperature and humidity
  float* temp_hum_val = read_temp_and_humidity();
  Serial.print("Humidity : ");
  Serial.print(temp_hum_val[0]);
  Serial.println("%");
  Serial.print("Temperature n°1 : ");
  Serial.print(temp_hum_val[1]);
  Serial.println("°C");

  // Luminosity
  int lux = read_lux();
  Serial.print("Lux : ");
  Serial.print(lux);
  Serial.println(" lx");

  // Temperature
  float temp = read_temperature();
  Serial.print("Temperature n°2 : ");
  Serial.print(temp);
  Serial.println("°C");

  // Dataline 
  dataline = datetime + ";" +
           String(wind) + ";" +
           String(temp_hum_val[0]) + ";" +  
           String(temp_hum_val[1]) + ";" + 
           String(lux) + ";" +
           String(temp);              

  // Save 
  File file = SD.open(datafile, FILE_APPEND); 
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.println(dataline)){
      Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();


  delay(1000);
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

void setup_temperature() {
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

float read_temperature() {
  return mcp9808.getTemperature();
}

String read_datetime() {
  int second = Clock.getSecond();
  int minute = Clock.getMinute();
  int hour = Clock.getHour(h12, PM);
  int date = Clock.getDate();
  int month = Clock.getMonth(Century);
  int year = Clock.getYear();

  String dateStr = String(year) + "-" + String(month) + "-" + String(date);
  String timeStr = String(hour) + ":" + String(minute) + ":" + String(second);
  return dateStr + " " + timeStr;
}
