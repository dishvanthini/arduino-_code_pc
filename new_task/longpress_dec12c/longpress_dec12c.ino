
///long press and single press 
int sw=15;//a1
int led =3,led1 =5;//led2=d5

void setup() {
pinMode(sw,INPUT_PULLUP);//HIGH 
pinMode(led,OUTPUT);pinMode(led1,OUTPUT);
Serial.begin(9600);
}

void loop() {
//double tap //
//time tw 2 tap//c=1 //led glow 
//last_p=digitalRead(sw);
int count=0;
int old_press=digitalRead(sw);
if(old_press==LOW){//press
  count++;//c=1
  Serial.println("press");//press //0 

  old_press=HIGH;//not press
  delay(1000);//1sec

  old_press=digitalRead(sw);
  
  if(old_press==LOW ){
    count++;//c=2 
    Serial.println(count);//2   
    count=0;///reset
  }

  else{
    Serial.println("press 1");//c=1
  }

}
else{
 //Serial.println("xxx not presss xxx");//not pressed 
 Serial.println(count);

}
  delay(400);//1sec


}