int trig=A2,echo=A3;
void setup() {
  pinMode(13,OUTPUT);//SMD led
  pinMode(trig,OUTPUT);//trigA2//RED16
  pinMode(echo,INPUT);//echoA3
  Serial.begin(9600);

}
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);//trig transmit sgnl
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

 int a=pulseIn(echo,HIGH);//duration
  int dis=(0.0343*a)/2;//speed*time

 Serial.println("distance : "); 
 Serial.println(dis);

 delay(1000);

}
