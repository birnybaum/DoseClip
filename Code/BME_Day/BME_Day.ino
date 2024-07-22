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
float dBA=0;
//long unsigned sum_square=0;
File myFile;

void setup() {
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  /*Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("/BME_Day_Noise.txt", FILE_WRITE);

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
  float Voltage = (Bits*3.3/4096)-1.65;
  float square= pow(Voltage,2);
  float sum_square=sum_square + square;
  /* Serial.print("Bits:");
   Serial.println(Bits,4);
   Serial.print("Voltage:");
   Serial.println(Voltage,4);
   Serial.print("square:");
   Serial.println(square,4);
   Serial.print("sum square:");
   Serial.println(sum_square,4);*/
  Count++;
long int time = millis();  
if (timeElapsed > interval) 
	{ float RMSv = sqrt(sum_square/Count); 
   Serial.print("sum square:");
   Serial.println(sum_square,4);
   Serial.print("Count:");
   Serial.println(Count,4);
    //float RMSv = (RMS *3.3/4096) - 1.65; 
    Serial.print("RMSv:");
    Serial.println(RMSv,4);
    
    if (RMSv >.25 && RMSv < 0.28) {
    dBA= 166.67*RMSv + 38.333;
    Serial.print("dBA:");
    Serial.println(dBA);
    }
    else { dBA = 2.1798*(20*log10(RMSv/0.00002))-94.114; 
    Serial.print("dBA:");
    Serial.println(dBA);
    }
  /*myFile = SD.open("/BME_Day_Noise.txt", FILE_APPEND);
  if (myFile) {
  myFile.print(time);
  myFile.print(",");
  myFile.println(dBA);//we want the dBA after the 5-sec average to be saved
  myFile.close(); 
  }*/
  if (dBA >= 80) {
  float Weighting = 1.6667*(1/(exp(-0.13862944*dBA)*exp(18.65043535))); // 1-sec measurements 
  float Allowance = Allowance_Start - Weighting;
  Serial.print("Weighting: ");
  Serial.println(Weighting);
  Serial.print("Allowance: ");
  Serial.println(Allowance);

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
    square=0;
    sum_square=0;
    timeElapsed = 0;
    Count=0;	
  }



}

   


   

