/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  NOTE:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  App project setup:
    Value Display widget attached to Virtual Pin V5
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLS7Tj-jQW"
#define BLYNK_DEVICE_NAME "OVER HEAT DETECTOR"
#define BLYNK_AUTH_TOKEN "91M3nPN2b9xp0nniSRkGx2MY6m9-qf8C"
int voltage,fanspeed,Tc,pwmvalue,relayvalue;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
String text=" ";
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "91M3nPN2b9xp0nniSRkGx2MY6m9-qf8C";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo Y75 5G";
char pass[] = "manikandan";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V2,text);
  Blynk.virtualWrite(V1,Tc);
  }
// this below code for to read the virutal pin data  
BLYNK_WRITE(V8) {
fanspeed=param.asInt();
}
BLYNK_WRITE(V3) {
relayvalue=param.asInt();
}
void setup()
{
  // Debug console
  Serial.begin(9600);
   pinMode(8,OUTPUT);
   pinMode(11,OUTPUT);
 
// Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{

//  code for read and convert into celsius
  voltage=analogRead(A1);
  delay(500);
  R2 = R1 * (1023.0 / (float)voltage - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  pwmvalue=map(Tc,20,200,0,255);  
//Serial.println(Tc);
// Serial.println(pwmvalue); 
  
 if (isalpha(relayvalue)==0){
  digitalWrite(8,relayvalue); }
 if(Tc>110)
 { 
  digitalWrite(8,HIGH); 
  delay(1000); 
   } 
// manual control for cooling fan
if ((isalpha(fanspeed)==0)&&(fanspeed>80))
{
   analogWrite(11,fanspeed);
   delay(1000);
}
else
{ analogWrite(11,pwmvalue); 
  delay(1000);  
  }  
  Blynk.run();
  timer.run(); // Initiates BlynkTime
}