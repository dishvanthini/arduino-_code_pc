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
int old_press=digitalRead(sw);
if(old_press==LOW){//press
  Serial.println("press");//press //0 
  delay(200);//2sec

  int new_press=digitalRead(sw);//reading again
  //delayMicroseconds(20);
  if(old_press==HIGH && new_press==HIGH){
    Serial.println("press 1"); 
    delay(200);
    while()
  }
 // else if(new_press==HIGH){
    //    Serial.println("1"); //delay(1000);

 // }
  else{
    Serial.println("press 2");//l
  }

}
else{
 Serial.println(" not presss");//not pressed 
}

delay(400);//1sec
}