#include <M5Stack.h> //use any controller by substituting the library
#include "SHT3X.h"   // the temp sensor (also the humidity sensor)
SHT3X sht30;         // creates ONE instance!!!
float temp1;         // value on ENV1
float temp2;         // value on ENV2
void setup() {
  M5.begin();
  delay(100);
  Wire.beginTransmission(0x70); //(the PaHub)
  Wire.write(0x00);             //turns off all ports
  Wire.endTransmission();
  M5.Lcd.setTextSize(3);        //or lower for StickC
  M5.Lcd.setTextColor(RED);
}
void loop() {
  Wire.beginTransmission(0x70);//(the PaHub)
  Wire.write(0x01);            //turns on port 0, ENV1
  Wire.endTransmission();
  if (sht30.get() == 0) {      //reads the ENV at port 0
    temp1 = sht30.cTemp;       //assigns the reading to "temp1"
  }
  delay(100);
  Wire.beginTransmission(0x70);//(the PaHub)
  Wire.write(0x02);            //reads the ENV at port 1
  Wire.endTransmission();
  if (sht30.get() == 0) {
    temp2 = sht30.cTemp;        //assigns the reading to "temp2"
  }
  delay(100);
  M5.Lcd.fillRect(0, 0, 320, 80, BLACK);
  M5.Lcd.setCursor(5, 5);
  M5.Lcd.print("Temp1=  ");
  M5.Lcd.setCursor(130, 5);
  M5.Lcd.print(temp1,1);        //one decimal place
  M5.Lcd.setCursor(5, 50);
  M5.Lcd.print("Temp2=  ");
  M5.Lcd.setCursor(130, 50);
  M5.Lcd.print(temp2,1);        //one decimal place
}
