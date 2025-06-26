
// Enregistre des données horodatées de température sur une carte microSD
// Les données sont également transmises sur le port série



////Librairies
//Pour le capteur temperature DS18B20
#include <OneWire.h>                    
#include <DallasTemperature.h>          

// Pour horloge RTC
#include <DS3231.h>
#include <Wire.h> 

// Pour la carte SD:
#include "FS.h"
#include "SD.h"
#include "SPI.h"


//// Declarations 
//pour le capteur température
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor_ds18b20(&oneWire);
float temp;

//pour la RTC
DS3231 Clock;
bool Century = false;
bool h12;
bool PM;
int second, minute, hour, date, month, year;

//pour la carte SD
const int cspin_SD=5;
String datafile = "/data.txt"; //Le ficher dans lequel on enregistre les données

// On prépare une cahine de caractère pour organiser les données
String dataline ="" ;

void setup() {
  // Initialisation de la communication série
  Serial.begin(115200);
  // Initialisation de la communication avec le capteur de température
  sensor_ds18b20.begin();
  // Initialisation de la communcation avec la RTC (wire car c'est de l'I2C)
    Wire.begin();
  // Initialisation de la carte SD
  if(!SD.begin(cspin_SD)){
     Serial.println("Card Mount Failed");
     return;
  }

}

void loop() {
   // On lit le capteur température
   sensor_ds18b20.requestTemperatures(); // Send the command to get temperatures
  temp = sensor_ds18b20.getTempCByIndex(0);

  // On lit la RTC
   second = Clock.getSecond();
   minute = Clock.getMinute();
   hour = Clock.getHour(h12, PM);
   date = Clock.getDate();
   month = Clock.getMonth(Century);
   year = Clock.getYear();

   //On arrange tout ca pour faire une ligne de donnes
  dataline = String(String(year)+ "/"+ String(month) + "/"+ String(date)+ " ");
  dataline = String(dataline + String(hour)+ ":" + String(minute) + ":"+ String(second) + ";");
  dataline = String(dataline + String(temp));
  Serial.println(dataline);

  // On sauvegarde la ligne dans un fichier :
  File file = SD.open(datafile, FILE_APPEND); // fichier en mode appends : les données sont 
                                              //rajoutées a la suite des données existantes
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


  delay(1400);
}