int pot=A0;
int ir=6;
void setup() {
  pinMode(pot,OUTPUT);
  Serial.begin(9600);

}

void loop() {
 potf();
 //irf();
}
void irf(){
  int v =digitalRead(ir);
  if(v==HIGH){
    Serial.println("detected");
      delay(2000);
  }
  else{
    Serial.println("No...");
        delay(2000);

  }
}
void potf(){
  int v=analogRead(pot);
  Serial.println("v ");
  Serial.print(v);
  delay(1000);

}
