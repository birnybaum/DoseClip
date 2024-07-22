// These constants won't change:

const int micPin = A0;       // pin that the mic is attached to

// These variables will change:
int micValue = 0;         // the mic value
int interval = 0;      // interval for while loop
float Allowance_Start = 100;  // allowance start value

void setup() {
// initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
  
 // read the sensor:
  micValue = analogRead(micPin);

// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V):
  float voltage = micValue * (3.3 / 1023.0);

   // print out the value you read:
  Serial.println(voltage);

  while (interval < 12) {
    
    interval = interval + 1;
    float dBA =  20*log10(voltage/0.00002);
  }
    if (dBA >= 80) {
    float Weighting = 100*(1/12)*(1/(np.exp(-0.13862944*dBA)*np.exp(18.65043535)));
    float Allowance = Allowance_Start - Weighting;
    }
    if (Allowance > 60){
    Serial.println(round(Allowance));
    Serial.println("% Remaining, Healthy Enviornment");
    }
    else if (Allowance > 10){
    Serial.println(round(Allowance));
    Serial.println("% Remaining, Be Careful go to Quieter Enviornment");
    }
    else if (Allowance > 0){
    Serial.println(round(Allowance));
    Serial.println("% Remaining, Limit Reached, Risk for Hearing Loss!");
    }
    else{
    Serial.println(round(abs(Allowance_)));
    Serial.println("'% Over Limit, Danger for Hearing Loss!'!");
    }

    }
    
    

  }

}


const int micPin = A0; // analog pin connected to microphone sensor
const int numSamples = 200; // number of voltage samples to take
char quote[50];


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
char quote[44];
int Start=100;

sprintf(quote,"%d Start", Start);
Serial.println(quote);

}

void loop() {
  // put your main code here, to run repeatedly:

for (int i=0; i<=2; i++) {
  unsigned long startTime = millis(); 
  float data[10][3];
  float dB[10][3];
  int count = 0;
  for (int x=0; x<10; x++) { 
      
      data[x][i] = {(analogRead(micPin)*3.3/1024)-1.6};
      data[x][i] = {abs(data[x][i])};
      dB[x][i] = {(20*log10(data[x][i]/0.00002))-7.8764005203222565743513326330608};
      Serial.println(dB[x][i]);
    delay(2000);

  }
  
}
}

/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
And Time Conversion 
*/
#include <SPI.h>
#include <SD.h>
#include <stdio.h>
#include <math.h>


using namespace std;

#include <DHT.h>

#define DHTPIN 2     
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321



int interval=1;
float Allowance_Start = 100;

unsigned long time;
File myFile;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  Serial.println(F("DoseClip example!"));

  dht.begin();
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
   if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Time,Voltage,Decibel,Weighting,Allowance");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  /*// re-open the file for reading:
  if (myFile) {
    Serial.println("test.txt:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } 
  */
}

void loop() {

double Rand = .15+((double) rand() / (RAND_MAX));
float Voltage = DHTPIN*Rand;

myFile = SD.open("test.txt", FILE_WRITE);

 if (myFile) 
  {

   float dBA =  20*log10(Voltage/0.00002)-7.8764005203222565743513326330608;

   long int time = millis();
   Serial.print("Time:"); 
   long int hour=time/3600000;
   long int over=time%3600000;
   long int minute=over/60000;
   over=over%60000;
   long int second=over/1000;
   long int ms=over%1000;
   Serial.print(hour);
   Serial.print(":");
   Serial.print(minute);
   Serial.print(":");
   Serial.print(second);
   Serial.print(".");
   Serial.println(ms);

   myFile.print(hour);
   myFile.print(":");
   myFile.print(minute);
   myFile.print(":");
   myFile.print(second);
   myFile.print(".");
   myFile.print(ms);
   myFile.print(",");
   interval = interval + 1;
   delay(1000); // Fast=125 Slow=1000
   Serial.print(F("Voltage: "));
   Serial.print(Voltage);
   Serial.print(F("  Decibel: "));
   Serial.print(dBA);
   Serial.println(F("dBA"));

    

   

   myFile.print(Voltage);
   myFile.print(",");
   myFile.print(dBA);
   myFile.print(",");
   if (dBA >= 80) {
    float Weighting = 8.333333333*(1/(exp(-0.13862944*dBA)*exp(18.65043535)));
    float Allowance = Allowance_Start - Weighting;
  Serial.print(F("Weighting: "));
  Serial.println(Weighting);
  Serial.print(F("Allowance: "));
  Serial.println(Allowance);

  myFile.print(Weighting);
  myFile.print(",");
  myFile.println(Allowance);
  

  if (Allowance > 60){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Healthy Enviornment");
    }
    else if (Allowance > 10){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Be Careful go to Quieter Enviornment");
    }
    else if (Allowance > 0){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Limit Reached, Risk for Hearing Loss!");
    }
    else{
    Serial.print(round(abs(Allowance)));
    Serial.println("'% Over Limit, Danger for Hearing Loss!'!");
    }
    
   Allowance_Start=Allowance;
    
    }
     myFile.close();
    
  }
  
  

}


// OLED Code
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
using namespace std;
#include <DHT.h>

#define DHTPIN 2     
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
float Allowance_Start = 100;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

 
}

void loop() {
double Rand = .15+((double) rand() / (RAND_MAX));
float Voltage = DHTPIN*Rand;
float dBA =  20*log10(Voltage/0.00002)-7.8764005203222565743513326330608;
int time = millis();
if (dBA >= 80) {
    float Weighting = 8.333333333*(1/(exp(-0.13862944*dBA)*exp(18.65043535)));
    float Allowance = Allowance_Start - Weighting;

  if (Allowance > 60){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Healthy Enviornment");
    }
    else if (Allowance > 10){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Be Careful go to Quieter Enviornment");
    }
    else if (Allowance > 0){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Limit Reached, Risk for Hearing Loss!");
    }
    else{
    Serial.print(round(abs(Allowance)));
    Serial.println("'% Over Limit, Danger for Hearing Loss!'!");
    }
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Allowance : ");
      display.print(round(abs(Allowance)));
      display.println("%");
      display.print("Sec : ");
      display.println(time/1000);
      display.display(); 
      delay(1000);
      Allowance_Start=Allowance;
        
    }
 
 
}

//OLED and SD
#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>
//using namespace std;
#include <DHT.h>

#define DHTPIN 2     
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
float Allowance_Start = 100;
unsigned long time;
File myFile;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 8 // OLED display height, in pixels

//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  
   Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
   if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Time,Voltage,Decibel,Weighting,Allowance");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
}

void loop() {

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 0);
double Rand = .15+((double) rand() / (RAND_MAX));
float Voltage = DHTPIN*Rand;
float dBA =  20*log10(Voltage/0.00002)-7.8764005203222565743513326330608;
int time = millis();

myFile = SD.open("test.txt", FILE_WRITE);
if (myFile) {
  myFile.print(time);
  myFile.print(",");
  myFile.print(dBA);
  }


if (dBA >= 80) {
    float Weighting = 8.333333333*(1/(exp(-0.13862944*dBA)*exp(18.65043535)));
    float Allowance = Allowance_Start - Weighting;


  if (Allowance > 99.8){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Healthy Enviornment");
    display.print(round(abs(Allowance)));
    display.print("%");
    display.println(" Healthy");
    display.display(); 
    delay(1000);
    }
    else if (Allowance > 99.4){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Be Careful go to Quieter Enviornment");
    display.print(round(abs(Allowance)));
    display.print("%");
    display.println(" Careful");
    display.display(); 
    delay(1000);
    }
    else if (Allowance > 99.2){
    Serial.print(round(Allowance));
    Serial.println("% Remaining, Limit Reached, Risk for Hearing Loss!");
    display.print(round(abs(Allowance)));
    display.print("%");
    display.println(" Limit");
    display.display(); 
    delay(1000);
    }
    else{
    Serial.print(round(abs(Allowance)));
    Serial.println("'% Over Limit, Danger for Hearing Loss!'!");
    display.print(round(abs(Allowance)));
    display.print("%");
    display.println(" Over");
    display.display(); 
    delay(1000);
    }
      
    Allowance_Start=Allowance;
        
    }
  
 myFile.close();
}
