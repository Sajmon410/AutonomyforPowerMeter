#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <TimeLib.h>
#include <virtuabotixRTC.h>
#include <math.h>

const int amplitude = 100;  // Amplitude of the sine wave
const int frequency = 1;    // Frequency of the sine wave
const int offset = 127;     // Offset to center the wave around 0
const int chipSelect = 10;
virtuabotixRTC *p_obj;  // Creation of the Real Time Clock Object

void setup() {
  Serial.begin(9600);
  p_obj=new virtuabotixRTC(6, 7, 4);
  p_obj->setDS1302Time(18, 10, 10, 7, 12, 6, 2023);
  Serial.println("Initializing SD card...");

  if (SD.begin(chipSelect)) {
    Serial.println("SD card initialized!");
  } else {
    Serial.println("SD card initialization failed!");
    return;
  }
}

void loop() {
 // Convert the angle to radians
// Calculate the sine value
  static int angle = 0;
  int sineValue = amplitude * sin(angle * 0.0174533) + offset;
  angle += frequency;
  p_obj->updateTime();
 String data = "Value: "+ String(angle)+"V " +String(sineValue)+"mA\nData to be stored on SD card at: " + String(p_obj->year) + "-" + String(p_obj->month) + "-" + String(p_obj->dayofmonth) + " " + String(p_obj->hours) + ":" + String(p_obj->minutes) + ":" + String(p_obj->seconds);
  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    Serial.println("***************************************************");
    Serial.println("Data written to file: " + data);
  } else {
    Serial.println("Error opening data file!");
  }

  delay(5000); // Delay for 5 seconds before storing the next data point
  }