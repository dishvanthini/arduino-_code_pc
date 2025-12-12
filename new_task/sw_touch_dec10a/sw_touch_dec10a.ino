int sw1=14,sw2=15,sw3=16,sw4=17;         
//sw=touch 
void setup() {
pinMode(sw1, INPUT);
pinMode(sw2, INPUT);
pinMode(sw3, INPUT);
pinMode(sw4, INPUT);

 Serial.begin(9600);
}

void loop() {

sw();
}

void sw(){
  if((digitalRead(sw1)==LOW)&&(digitalRead(sw2)==LOW)){
  Serial.println("sw1 and sw2 pressed ");
}
else if((digitalRead(sw3)==LOW)&&(digitalRead(sw4)==LOW)){
  Serial.println("sw3 and sw4 pressed ");
  }
else {
  Serial.println("someother");
}
}
void touchsensor()
{
  if((digitalRead(sw1)==HIGH)&&(digitalRead(sw2)==HIGH)){
  Serial.println("sw1 and sw2");
}
else if((digitalRead(sw3)==HIGH)&&(digitalRead(sw4)==HIGH)){
  Serial.println("sw3 and sw4");}
else {
  Serial.println("someother");
}
}
