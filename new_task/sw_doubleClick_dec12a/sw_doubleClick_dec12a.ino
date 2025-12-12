int sw=15;//a0
int led =3,led1 =5,duration;//led2=d5

int c=0;
int last_press=HIGH,new_press,last_dr;


void setup() {
pinMode(sw,INPUT_PULLUP);//HIGH 
pinMode(led,OUTPUT);pinMode(led1,OUTPUT);
Serial.begin(9600);
}

void loop() {
//double tap //
//time tw 2 tap//c=1 //led glow 
//last_p=digitalRead(sw);
new_press=digitalRead(sw);
last_dr=millis();
if(new_press==LOW && last_press==HIGH)//pressed
{int sw=15;//a0
int led =3,led1 =5,duration;//led2=d5

int c=0;
int last_press=HIGH,new_press,last_dr;


void setup() {
pinMode(sw,INPUT_PULLUP);//HIGH 
pinMode(led,OUTPUT);pinMode(led1,OUTPUT);
Serial.begin(9600);
}

void loop() {
//double tap //
//time tw 2 tap//c=1 //led glow 
//last_p=digitalRead(sw);
new_press=digitalRead(sw);
last_dr=millis();
if(new_press==LOW && last_press==HIGH)//pressed
{
duration=millis();//millis sec reads 
Serial.print("d= ");

Serial.println(duration);
  if(duration-last_dr <=500){
    c++;   
    last_dr=duration;

  }
    Serial.println("c");    Serial.println(c);


      if(c==2){
        digitalWrite(led,HIGH);
        delay(1000);
        digitalWrite(led,LOW);

        c=0;
      }
      else{
        digitalWrite(led1,HIGH);
        delay(1000);
        digitalWrite(led1,LOW);
      
      }
  }
  last_press=new_press;

}
duration=millis();//millis sec reads 
Serial.print("d= ");

Serial.println(duration);
  if(duration-last_dr <=500){
    c++;   
    last_dr=duration;

  }
    Serial.println("c");    Serial.println(c);


      if(c==2){
        digitalWrite(led,HIGH);
        delay(1000);
        digitalWrite(led,LOW);

        c=0;
      }
      else{
        digitalWrite(led1,HIGH);
        delay(1000);
        digitalWrite(led1,LOW);
      
      }
  }
  last_press=new_press;

}