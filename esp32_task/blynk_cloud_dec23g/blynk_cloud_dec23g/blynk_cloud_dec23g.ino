#define BLYNK_TEMPLATE_ID "TMPL3dymcEOTO"
#define BLYNK_TEMPLATE_NAME "Esp32"
#define BLYNK_AUTH_TOKEN "QIHMFnSDWS_0RdixPOIi61gAuTwCnjcO"   
#include<WiFi.h>
#include<BlynkSimpleEsp32.h>

int led=2;

void setup(){
  Serial.begin(9600);  
  pinMode(32,INPUT);
  pinMode(led,OUTPUT);
  WiFi.mode(WIFI_STA);//station mode to connect to wifi 
  WiFi.begin("dish","dish123!"); //Serial.println("the token shared");  Blynk.begin(BLYNK_AUTH_TOKEN,"dish","dish123!");
  Blynk.config(BLYNK_AUTH_TOKEN);  // only configure token
  Blynk.connect();
   Serial.print("connected to.. ");
  Serial.print(WiFi.localIP());
  Serial.println(" ");
}
void loop(){
  Blynk.run();//read incoming data , decodes the blynk data 
  int value =analogRead(32);
  Serial.println(value);
  Blynk.virtualWrite(V2,value);
}
//if sw by blynk app then blink 

  BLYNK_WRITE(V0){//push vo value to esp32
  int sw=param.asInt();
  if(sw==1)    digitalWrite(led,HIGH);
  else  digitalWrite(led,LOW);
  }
  


//wifi connects
//tcp connects to the server using token 
//begin the connection 
//pinmode
//sw state
//led based on switch.
