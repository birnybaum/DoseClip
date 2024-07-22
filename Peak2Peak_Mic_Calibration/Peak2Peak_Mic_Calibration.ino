#include <iostream>       
#include <algorithm>   
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

  void setup() {
  Serial.begin(115200);
}  

void loop() {
float Bits = (analogRead(micPin));
  
  if (Bits > localMax){
    localMax = Bits;
  }
  if (Bits < localMin){
    localMin = Bits;
  }
 
  if (timeElapsed > interval) 
	{	Serial.print("Bits: ");
    Serial.println(analogRead(micPin));
    Serial.print("count: ");
    Serial.println(Ncount);
    Serial.print("Max: ");
    Serial.print(localMax);
    Serial.println(" Bits");
    Serial.print("Min: ");
    Serial.print(localMin);
    Serial.println(" Bits");
    
}
		//Serial.println(timeElapsed);
    float Peak2Peak = ((localMax)*3.3/4096)-1.65; //shifted down, no need for dividing by 2 or min
    // float Peak2Peak = ((localMax-localMin)*3.3/4096)/2; //No shift, might need to divide by 2
    Serial.print("Peak2Peak: ");
    Serial.print(Peak2Peak);
    Serial.println(" volts");
  //float dBA =  20*log10(Peak2Peak/0.00002)-7.8764005203222565743513326330608;
  //float dBA = 83.51*pow(Peak2Peak,0.1672)+35.78;
    sum=sum+Peak2Peak; //switch Peak2Peak to localMax for just bits
     Serial.print("Sum: ");
     Serial.println(sum);
    dBAcount++;
if (dBAcount>5){
   sum = sum/dBAcount;
   Serial.print("AVG: ");
   Serial.println(sum);
   sum=0;
   dBAcount=0;
}
		timeElapsed = 0;
    Ncount=0;	
    localMax=0;
    localMin=4096;	
  
	}
    






