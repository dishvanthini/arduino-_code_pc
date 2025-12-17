#include<SPI.h>
#include<MFRC522.h>
int rs=17;
int ss=10;
	MFRC522 rf(ss, rs);
  	//void PCD_Init(byte chipSelectPin, byte resetPowerDownPin);


void setup() {
  Serial.begin(9600);
  SPI.begin();
  rf.PCD_Init();

  
}

void loop() {
//new card 	virtual bool PICC_IsNewCardPresent();
  if(rf.PICC_IsNewCardPresent()){
//is new card or not 
    if(rf.PICC_ReadCardSerial()){
    //good to read the addr but not matching ?
      
        //Serial.println(rf.uid.size);
        Serial.print("UID ");

  for(int i =0;i<rf.uid.size;i++){
    Serial.print(rf.uid.uidByte[i]);
  }
  Serial.println(" ");
}}
else {
  Serial.println("Place the card ");

}
  delay(1000);
}