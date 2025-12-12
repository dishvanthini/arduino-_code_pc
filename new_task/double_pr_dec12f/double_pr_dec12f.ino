int sw=15;//a1
int led =3,led1 =5;//led2=d5



void setup() {
pinMode(sw,INPUT);//HIGH 
pinMode(led,OUTPUT);pinMode(led1,OUTPUT);
Serial.begin(9600);
}

void loop() {
//double tap //
//time tw 2 tap//c=1 //led glow 
//last_p=digitalRead(sw);
if(digitalRead(sw)==LOW){//press
  Serial.println("press");//press //0 
  while(digitalRead(sw) == LOW);//release
  delay(150);//2sec


  if(digitalRead(sw)==LOW){
      Serial.println("press 2"); 
      digitalWrite(led, HIGH);
      delay(200);
      digitalWrite(led, LOW);
    while(digitalRead(sw) == LOW);
    delay(100);

     }

  else{
      Serial.println("press 1");
      digitalWrite(led1, HIGH);
      delay(200);
      digitalWrite(led1, LOW);}
}


else{
 Serial.println(" not presss");//not pressed 
}
delay(200);//1sec
}