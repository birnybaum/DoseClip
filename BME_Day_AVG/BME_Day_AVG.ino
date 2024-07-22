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
float sum_square=0;
int Count=0;
float dBA=0;
float sum_dBA=0;
float sum_RMS=0;
int dBAcount=0;

File myFile;

void setup() {
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  // Initialize SD Card Module
 /* Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

 //If file Dr.Richter.txt exists then open and add to file
 myFile = SD.open("/Dr.Richter.txt", FILE_Append);
 
   if (myFile) {
    //Serial.print("Writing to test.txt...");
    myFile.println("Allowance Was Reset");
    myFile.println("Time,Decibel,Allowance");
  // if the file opened okay, write to it:
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, write a new file Dr.Richter.txt :
    myFile = SD.open("/Dr.Richter.txt", FILE_WRITE);
    myFile.println("Time,Decibel,Allowance");
  }*/
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  float Bits = (analogRead(micPin));
  float Bitsv = (Bits *3.3/4096) - 1.65; 
  float square= pow(Bitsv,2);
  sum_square=sum_square + square;
  Count++;
long int time = millis();  
if (timeElapsed > interval) 
	{ float RMS = sqrt(sum_square/Count); 
    Serial.print("RMS:");
    Serial.println(RMS,4);
    dBA =  20*log10(RMS/0.00002)-7.8764005203222565743513326330608;
    Serial.print("dBA:");
    Serial.println(dBA);
   //WE NEED A SINGLE EQUATION RECALIBRATED
    /*if (RMS < 0.28) {
    dBA = 166.67*RMS + 38.333;
    Serial.print("dBA:");
    Serial.println(dBA);
    }
    else { dBA = 2.1798*(20*log10(RMS/0.00002))-94.114; 
    Serial.print("dBA:");
    Serial.println(dBA);
    }*/
     sum_dBA=sum_dBA+dBA;
     sum_RMS=sum_RMS+RMS;
     dBAcount++;
if (dBAcount==5){
   float AVG_dBA = sum_dBA/dBAcount;
   float AVG_RMS = sum_RMS/dBAcount;
   Serial.print("AVG dBA: ");
   Serial.println(AVG_dBA);
   Serial.print("AVG RMS: ");
   Serial.println(AVG_RMS,4);

  if (AVG_dBA >= 80) {
  float Weighting = 8.333*(1/(exp(-0.13862944*AVG_dBA)*exp(18.65043535))); // 5-sec measurements 
  float Allowance = Allowance_Start - Weighting;
  Serial.print("Weighting: ");
  Serial.println(Weighting);
  Serial.print("Allowance: ");
  Serial.println(Allowance);
 /*myFile = SD.open("/Dr.Richter.txt", FILE_APPEND);
  if (myFile) {
  myFile.print(time/60000); //time in minutes 
  myFile.print(",");
  myFile.print(AVG_dBA);//we want the dBA after the 5-sec average to be saved
  myFile.print(",");
  myFile.println(Allowance);//we want the dBA after the 5-sec average to be saved
  myFile.close(); 
  }*/
  display.clearDisplay(); 
  display.drawRect(0, 32, (SCREEN_WIDTH - 1), 10, SSD1306_WHITE);
  display.fillRect(0, 32, (SCREEN_WIDTH - 1) * (Allowance_Start/100), 10, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 6);
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
    sum_dBA=0;
    sum_RMS=0;
    dBAcount=0;
  }  	
    square=0;
    sum_square=0;
    timeElapsed = 0;
    Count=0;
}
}
   

  

   

