//if button limit cross-then stop 

int sw=15;//a1

void setup() {
pinMode(sw,INPUT);//HIGH 
Serial.begin(9600);
}


void loop() {
static int count=0,limit=5;


if(digitalRead(sw)==LOW){//press
  Serial.println("press");//press //0 
  while(digitalRead(sw) == LOW);//release
  delay(150);//2sec
count++;
Serial.print(count);
    if(count>limit){
     goto print;
    }
}
else{
 Serial.println(" Not presss");//not pressed 
}

print:
Serial.print("go cant press");
delay(200);//1sec
}
millis();

