#include <Ultrasonic.h>
int trigerpin=3;
int echopin=2;

int val=0;
int dis=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(12,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(trigerpin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigerpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigerpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerpin,LOW);
  
  val= pulseIn(echopin,HIGH);
  //delay(1000);

  dis= val*0.017;
  Serial.println(dis);
  //delay(1000);
  if ( (dis<25)&&(dis >10) ){
    
    digitalWrite(12,HIGH);
    delay(1000);
    digitalWrite(12,LOW);
    delay(1000);
    }

    if (dis<10) {
       digitalWrite(12,HIGH);
    delay(100);
    digitalWrite(12,LOW);
    delay(100);
    
  }
  else {
    digitalWrite(12,LOW);
  }
}
