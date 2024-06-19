int motor1pin1 = 4;
int motor1pin2 = 5;

int motor2pin1 = 6;
int motor2pin2 = 7;
char a;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
   a=Serial.read();
   if (a=='w') {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
   digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);}
  else if (a=='s'){
    digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);}
  else if(a=='a'){
     digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
    
  }
  else if(a=='d'){
     digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
    
  }
}

  
