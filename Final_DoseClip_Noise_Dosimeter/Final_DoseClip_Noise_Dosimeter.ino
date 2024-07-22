using namespace std;
// Require Library for code to run. Download first before uploading
code into microcontroller
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>
#include <iostream>
#include <algorithm>
#include <elapsedMillis.h>
#include <TimeLib.h>
8
// Objects //
elapsedMillis timeElapsed;
File myFile;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define BAUD_RATE 115200
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int micPin = A3; // Collects the sound data and process
sound
const int interval = 1000; // 1-sec Slow interval
float Allowance_Start = 100;
// used in RMS average.
int Count=0;
float dBA=0;
float sum_square=0;
/* Definition */
// initialization of device
void initialization(int ADRR, int CS_pin){
// Configuration of the display bar
int width = 128;
const int Color = 0xFFFF; // White in RGB565 format
const int x = 0;
const int y = 32;
const int height = 10; // Height of Bar
Serial.print("Initializing SD card...");
if (!SD.begin(CS_pin))
{
Serial.println("initialization failed!");
while (1); }
Serial.println("initialization Complete."); Serial.println("");
Serial.println("");
Serial.print("Initializing OLED Display...");
if(!display.begin(SSD1306_SWITCHCAPVCC, ADRR))
{
9
Serial.println(F("SSD1306 allocation failed"));
for(;;);
}
Serial.println ("Initializing Complete.");
Serial.println("");Serial.println("");
/* Data logging Section */
SD.mkdir("/Noise_Dosimeter"); // Creates a folder to place the user
information
if(SD.exists("/Noise_Dosimeter/Sound_User.txt"))
{
myFile = SD.open("/Noise_Dosimeter/Sound_User.txt",
FILE_APPEND); // Appends data into file
{
myFile.printf("\n");
myFile.printf("Allowance has been reset\n");
myFile.printf("%-12s%-10s%-19s\n", "Time", "dBA",
"Allowance");
myFile.printf("%-12s%-10s%-19s\n", "----", "---",
"---------");
myFile.close();
Serial.println("File is ready to append.");
Serial.println("");
}
}
else
{
myFile = SD.open("/Noise_Dosimeter/Sound_User.txt",
FILE_WRITE); // Creates an txt file for collecting data.
if (myFile)
{
myFile.printf("%-12s%-10s%-15s\n", "Time", "dBA",
"Allowance");
10
myFile.printf("%-12s%-10s%-15s\n", "----", "---",
"---------");
myFile.close();
Serial.println("File has been created.");
Serial.println("");
}
}
display.clearDisplay();
display.drawRect(x,y, (width - 1), height, Color);
display.fillRect(x,y, (width - 1) * 1, height, Color); // width *
fraction of the allowance
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(5, 6);
display.println("Healthy");
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(30, 50); // x,y
display.print(100.00);
display.println("%");
display.display();
}
// For the conversion of A/D to volts to dBA
float bits_2_Vsquare(float Bits){
// float Bits is an input from analogRead()
// bias_offset is from half the battery capacity.
// Vcc = 3.3V so bias_offset is 1.65;
float dev_resolution = 3.3/4096;
float bias_offset = 1.65;
float Bitsv = (Bits * dev_resolution) - bias_offset;
float square = pow(Bitsv,2);
return square;
11
}
float RMS_v(int &Count, float &sum_square){
// Conversation AD reading into Root Mean Square (RMS)
float RMS_v = sqrt(sum_square/Count);
Serial.print("Summed volts: "); Serial.println(sum_square);
Serial.print("Samples: "); Serial.println(Count);
Serial.print("RMS: "); Serial.println(RMS_v);
return RMS_v;
}
float RMSv_to_dBA(float RMSv){
float x = 20*log10(RMSv/0.00002);
float x_square = pow(x,2);
if (RMSv > 0.316274 && RMSv < 0.354264) // 80 dBA - 90 dBA
{
dBA = (-3.1672*x_square)+(545.23*x)-23372 ;
Serial.print("dBA: "); Serial.println(dBA);
}
else if (RMSv >= 0.354264) // 90 dBA and above
{
dBA = (2.1571*x)-93.162; Serial.print("dBA: ");
Serial.println(dBA);
}
else
{
dBA = 0; Serial.println("dBA was less than 80. Allowance not
taken off"); // Anything below 80 is not necessary and is assigned a
dummy variable.
Serial.println("");
}
return dBA;
}
}
// For configuration of the screen and allowance
float Allowance(float dBA, float Allowance_Start) {
float factor = 1.6667; // 1-sec measurements ;
12
float Weighting =
factor*(1/(exp(-0.13862944*dBA)*exp(18.65043535))); // 1-sec
measurements
float Allowance = Allowance_Start - Weighting;
Serial.print("Weighting: "); Serial.print(Weighting,5);
Serial.print("; ");
Serial.print("Allowance: "); Serial.println(Allowance);
Serial.println("");
return Allowance;
}
void Allowance_Disp_Setting(float &allowance){
int width = 128;
const int Color = 0xFFFF; // White in RGB565 format
const int x = 0;
const int y = 32;
const int height = 10; // Height of Bar
float allowance_percent = (allowance/100);
display.clearDisplay();
display.drawRect(x,y, (width - 1), height, Color);
display.fillRect(x,y, (width - 1) * allowance_percent, height,
Color); // width * fraction of the allowance
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(5, 6);
// Display text when a certain percentage has been depleted
if (allowance > 60)
{
display.println("Healthy");
}
else if (allowance > 2)
{
display.println("Careful!");
}
else if (allowance > 0)
13
{
display.println("Limit");
}
else
{
display.println("Over Limit");
}
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(35, 50); // x,y
display.print(allowance,2);
display.println("%");
display.display();
}
// For Data logging
void Data_Log(long int time,String Filename,float dBA, float Allow){
/* Time = elapse time after device is one
Filename = Naming the file to append dBA and Allowance
percentage.
*/
Serial.print("Time:");
// To convert elapse time into hour, minutes and seconds
unsigned long hours = (time /3600000UL) % 24;
unsigned long minutes = (time /60000UL) % 60;
unsigned long seconds = (time /1000UL) % 60;
Serial.print(hours); Serial.print(":");
Serial.print(minutes); Serial.print(":");
Serial.println(seconds);
myFile = SD.open(Filename, FILE_APPEND);
if (myFile)
{
myFile.printf("%02lu:%02lu:%02lu %-10.2f%-10.2f\n", hours,
minutes, seconds, dBA, Allow); //Format of the time in H:M:S
}
}
14
// Main Portion of the Code
void setup()
{
Serial.begin(BAUD_RATE);
initialization(0x3C,4);
pinMode(D7, OUTPUT); // Turning on the LED
digitalWrite(D7,LOW); // WHen the device is on, the LED is
initially off
}
void loop(){
long int time = millis(); // elapsed time
float square = bits_2_Vsquare(analogRead(micPin));
sum_square += square; Count++; // used in calculating RMS
if (timeElapsed > interval)
{
float RMSv = RMS_v(Count,sum_square); // Returns RMS voltage
float dBA = RMSv_to_dBA(RMSv); // Converts from RMS
volts to dBA based on calibration
if (dBA >= 80) { // The 80 dBA threshold is from OSHA standard
requirement
digitalWrite(D7,HIGH); // LED is turn on
float Allow = Allowance(dBA, Allowance_Start); // This is
the portion of the code where the allowance gets depleted
Allowance_Disp_Setting(Allow); // Display is updated
Allowance_Start = Allow; // Updates the allowance
percentage
if ( dBA >= 100){
// Code to blink the LED once the dBA reading is at 100 and
above.
15
digitalWrite(D7,HIGH);
digitalWrite(D7,LOW);
digitalWrite(D7,HIGH);
digitalWrite(D7,LOW);
}
Data_Log(time,"/Noise_Dosimeter/Sound_User.txt",dBA, Allow);
// where the data gets append
}
else {
// When the reading is less than 80 then the LED is turned
off.
// LED should only be on when the reading is at 80 and above
digitalWrite(D7,LOW); }
// Reset parameter for next iteration used in calculating
data.
square=0;
sum_square=0;
timeElapsed = 0;
Count=0;
}
}