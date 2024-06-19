int val;
void setup() {
  // put your setup code here, to run once:
  pinMode(12,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    val=analogRead(A1);
    delay(1000);
    Serial.println(val);
    if (val<200) {
      digitalWrite(12,HIGH);
      
    }
    else {
      digitalWrite(12,LOW);
      
    }
}
