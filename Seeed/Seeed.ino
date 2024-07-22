/*
  SD card read/write
  With Algorithim
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
   LCD attached to SPI bus as follows:
  ** SCL - pin A5
  ** SDA - pin A4
SD and OLED working together takes large RAM, use less pixels 
*/
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>
#include <iostream>       
#include <algorithm> 
#include <elapsedMillis.h>
elapsedMillis timeElapsed;  
using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int micPin = A3;
float Allowance_Start = 100;
unsigned int interval = 1000;
int Count=0;
//int dBAcount=0;
//float sum=0;
float dBA=0;
float sum_square=0;
File myFile;

void setup() {
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
 /* Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("/Andrew_NOISE2.txt", FILE_WRITE);

  // if the file opened okay, write to it:
   if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Time,Decibel");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }*/
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  float Bits = (analogRead(micPin));
  float square= pow(Bits,2);
  sum_square=sum_square + square;
  Count++;
 /* display.clearDisplay(); 
  display.drawRect(0, 32, (SCREEN_WIDTH - 1), 10, SSD1306_WHITE);
  display.fillRect(0, 32, (SCREEN_WIDTH - 1) * (Allowance_Start/100), 10, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 6);
  //display.print("POWERBEATS");
   if (Allowance_Start > 60){
    display.println("Healthy");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    } else if (Allowance_Start > 10){
    display.println("Careful");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    }
    else if (Allowance_Start > 0){
    display.println("Limit");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    }
    else{
    display.println("Over Limit");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    }*/

long int time = millis();  
if (timeElapsed > interval) 
	{	Serial.print("Bits: ");
    Serial.println(analogRead(micPin));
    Serial.print("Samples: ");
    Serial.println(Count);
    float RMS = sqrt(sum_square/Count); 
    Serial.print("RMS:");
    Serial.println(RMS);
    float RMSv = (RMS *3.3/4096) - 1.65; 
    Serial.print("RMSv:");
    Serial.println(RMSv,4);
    if (RMSv < 0.28) {
    dBA= 166.67*RMSv + 38.333;
    //dBA =  20*log10(RMSv/0.00002)-7.8764005203222565743513326330608;
    Serial.print("dBA:");
    Serial.println(dBA);
    }
    else { dBA = 2.1798*(20*log10(RMSv/0.00002))-94.114; 
      //dBA = 1.9579*(20*log10(RMSv/0.00002))-75.089; 
    Serial.print("dBA:");
    Serial.println(dBA);
    }
 /* myFile = SD.open("/Andrew_NOISE2.txt", FILE_APPEND);
  if (myFile) {
  myFile.print(time);
  myFile.print(",");
  myFile.println(dBA);//we want the dBA after the 5-sec average to be saved
  myFile.close(); 
  }*/
   /*  sum=sum+dBA;
     Serial.print("Sum: ");
     Serial.println(sum);
     dBAcount++;
if (dBAcount==5){
   float AVGdBA = sum/dBAcount;
   Serial.print("AVG dBA: ");
   Serial.println(AVGdBA);*/

  if (dBA >= 80) {
  float Weighting = 1.6667*(1/(exp(-0.13862944*dBA)*exp(18.65043535))); // 1-sec measurements 
  float Allowance = Allowance_Start - Weighting;
  Serial.print("Weighting: ");
  Serial.println(Weighting);
  Serial.print("Allowance: ");
  Serial.println(Allowance);
  
   /*if (Allowance > 60){
    display.print(abs(Allowance));
    display.println("% Remaining, Healthy Enviornment");
    display.display(); 
    } else if (Allowance > 10){
    display.print(abs(Allowance));
    display.println("% Remaining, Be Careful go to Quieter Enviornment");
    display.display(); 
    }
    else if (Allowance > 0){
    display.print(abs(Allowance));
    display.println("% Remaining, Limit Reached, Risk for Hearing Loss!");
    display.display(); 
    }
    else{
    display.print(abs(Allowance));
    display.println("% Over Limit, Danger for Hearing Loss!");
    display.display(); 
    }*/
  display.clearDisplay(); 
  display.drawRect(0, 32, (SCREEN_WIDTH - 1), 10, SSD1306_WHITE);
  display.fillRect(0, 32, (SCREEN_WIDTH - 1) * (Allowance_Start/100), 10, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 6);
  //display.print("POWERBEATS");
   if (Allowance_Start > 60){
    display.println("Healthy");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    } else if (Allowance_Start > 10){
    display.println("Careful");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    }
    else if (Allowance_Start > 0){
    display.println("Limit");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    }
    else{
    display.println("Over Limit");
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 50); // x,y
    display.print(Allowance_Start,2);
    display.println("%");
    display.display(); 
    }

    Allowance_Start=Allowance; 
}
   dBA=0;
  /* sum=0;
   dBA=0;
   dBAcount=0;
}*/
    square=0;
    sum_square=0;
    timeElapsed = 0;
    Count=0;	
  }



}

   


   

