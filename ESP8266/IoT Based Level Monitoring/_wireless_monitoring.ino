#define BLYNK_TEMPLATE_ID "TMPL3uHip_vaY"
#define BLYNK_TEMPLATE_NAME "WIRELESS LEVEL MONITORING"
#define BLYNK_AUTH_TOKEN "8Nq00mdqKJQ92_LDAjU5dkpKyCZ0rTS6"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SUBA";
char pass[] = "12345678";
#include <Ultrasonic.h>
const int trigerpin = 12;
const int echopin = 14;
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
long duration;
int distanceCm;
int level;
bool value1;
#define pumpcontrol D8
int pumpcount_sec=0;
int pumpcount_min=0;
int pumpcount_hr=0;
SimpleTimer timer;
BLYNK_WRITE(V2) {
value1 = param.asInt();
// Check these values and turn the relay1 ON and OFF
}
void setup()
{
// Debug console
pinMode(pumpcontrol, OUTPUT);
pinMode(echopin,INPUT);
pinMode(trigerpin,OUTPUT);
Serial.begin(9600);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
// You can also specify server:
//Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
//Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
timer.setInterval(1000L, sendUptime);
}
void loop()
{
// Clears the trigPin
digitalWrite(trigerpin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigerpin, HIGH);
delayMicroseconds(10);
digitalWrite(trigerpin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echopin, HIGH);
// Calculate the distance
distanceCm = duration * SOUND_VELOCITY/2;
level=map(distanceCm,12,0,0,12); 
Serial.println(distanceCm);
if (value1 == 1)
{
digitalWrite(pumpcontrol, HIGH);
pumpcount_sec=pumpcount_sec+1;
if (pumpcount_sec==59){
pumpcount_sec=0;
pumpcount_min=pumpcount_min+1;
if (pumpcount_min==59){
pumpcount_min=0;
pumpcount_hr=pumpcount_hr+1;
}
}
delay(1000);
}
else if ((level>=0) && (level<7))
{
digitalWrite(pumpcontrol, HIGH);
pumpcount_sec=pumpcount_sec+1;
if (pumpcount_sec==59){
pumpcount_sec=0;
pumpcount_min=pumpcount_min+1;
if (pumpcount_min==59){
pumpcount_min=0;
pumpcount_hr=pumpcount_hr+1;
}
}
delay(1000);
}
else {
digitalWrite(pumpcontrol, LOW);
}
Blynk.run();
// You can inject your own code or combine it with other sketches.
// Check other examples on how to communicate with Blynk. Remember
// to avoid delay() function!
timer.run();
}
void sendUptime(){
Blynk.virtualWrite(V0,level);
Blynk.virtualWrite(V1, pumpcount_sec);
Blynk.virtualWrite(V3, pumpcount_min);
Blynk.virtualWrite(V4, pumpcount_hr);
//delay(1000);
}