#include <iostream>       
#include <algorithm>   
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>   
using namespace std;
#include <elapsedMillis.h>
elapsedMillis timeElapsed;
const int micPin = A3;
  
unsigned int interval = 1000;
int Ncount=0;
int dBAcount=0;
float sum=0;
float localMax=0;
float localMin=4096;
float Allowance_Start = 100;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  void setup() {
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}  

/*float algo(float pktopk){
     if (pktopk > 3000) {
       return false;
     } else {
       return true;
  }
}*/
void loop() {

display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0, 0);

  float Voltage = (analogRead(micPin));

  if (Voltage > localMax){
    localMax = Voltage;
  }
  if (Voltage < localMin){
    localMin = Voltage;
  }
  Ncount++;
  if (timeElapsed > interval) 
	{	
   /* Serial.println(analogRead(micPin));
    Serial.print("count: ");
    Serial.println(Ncount);
    Serial.print("Max: ");
    Serial.println(localMax);
    Serial.print("Min: ");
    Serial.println(localMin);
		Serial.println(timeElapsed);*/
    float Peak2Peak = ((localMax)*3.3/4096)-1.65;
    // float Peak2Peak = ((localMax-localMin)*3.3/4096)-1.65;
    
    Serial.print("Peak2Peak: ");
    Serial.print(Peak2Peak);
    Serial.println(" volts");
  float dBA =  20*log10(Peak2Peak/0.00002)-7.8764005203222565743513326330608;
  //float dBA = 83.51*pow(Peak2Peak,0.1672)+35.78;
    sum=sum+dBA;
     Serial.print("Sum: ");
     Serial.println(sum);
    dBAcount++;
if (dBAcount>5){
   dBA = sum/dBAcount;
   Serial.print("dBA: ");
   Serial.println(dBA);
   sum=0;
   dBAcount=0;

if (dBA >= 80) {
    float Weighting = 80.3333*(1/(exp(-0.13862944*dBA)*exp(18.65043535))); // 5-second measurements 
    float Allowance = Allowance_Start - Weighting;
  Serial.print("Weighting: ");
  Serial.println(Weighting);
  Serial.print("Allowance: ");
  Serial.println(Allowance);

   if (Allowance > 60){
    display.print(abs(Allowance));
    display.println("%"); 
    display.println("Healthy");
    display.display(); 
    }
    else if (Allowance > 10){
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
    }

    Allowance_Start=Allowance; 
}
}
    /*if(algo(Peak2Peak)){
      Serial.println("true");
    }else{
      Serial.println("false");
    }*/

		timeElapsed = 0;
    Ncount=0;	
    localMax=0;
    localMin=4096;	
	}
}
    






