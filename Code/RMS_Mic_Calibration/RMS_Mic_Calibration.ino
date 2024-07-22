#include <iostream>       
#include <algorithm>   
using namespace std;
#include <elapsedMillis.h>
elapsedMillis timeElapsed;
const int micPin = A3;
  
unsigned int interval = 1000;
int Ncount=0;
int RMScount=0;
float sum=0;
float sum_square=0;

  void setup() {
  Serial.begin(115200);
}  

void loop() {
float Bits = (analogRead(micPin));
float Voltage = (Bits*3.3/4096)-1.65;
  float square= pow(Voltage,2);
  sum_square=sum_square + square;
  Ncount++;
 
  if (timeElapsed > interval) 
	{	Serial.print("Bits: ");
    Serial.println(analogRead(micPin));
    Serial.print("Voltage:");
    Serial.println(Voltage,4);
    Serial.print("square:");
    Serial.println(square);
    Serial.print("sum_square:");
    Serial.println(sum_square);
    Serial.print("count: ");
    Serial.println(Ncount);
   
    float RMS = sqrt(sum_square/Ncount);

    //float dBA = 1.2514*(20*log10(Voltage/.00002)-7.8)-11.843;
    Serial.print("RMS:");
    Serial.println(RMS);
    Serial.print("Voltage:");
    Serial.println(Voltage,4);
    /*Serial.print("dBA:");
    Serial.println(dBA);*/
    sum=sum+RMS;
     Serial.print("Sum: ");
     Serial.println(sum);
    RMScount++;
if (RMScount==5){
   sum = sum/RMScount;
   Serial.print("AVG RMS: ");
   Serial.println(sum);
   float dBA = 2.1798*(20*log10(sum/0.00002))-94.114; 
   Serial.print("dBA:");
   Serial.println(dBA);
   sum=0;
   RMScount=0;
}
    square=0;
    sum_square=0;
    timeElapsed = 0;
    Ncount=0;	
  }
}






