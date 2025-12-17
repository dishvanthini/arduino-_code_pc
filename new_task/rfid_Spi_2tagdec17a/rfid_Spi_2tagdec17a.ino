//compare two id that already existing , new one

#include <SPI.h>
#include <MFRC522.h>
int rs = 17;
int ss = 10;
MFRC522 rf(ss, rs);
//void PCD_Init(byte chipSelectPin, byte resetPowerDownPin);


void setup() {
  Serial.begin(9600);
  SPI.begin();
  rf.PCD_Init();
}

void loop() {
  
  //new card 	virtual bool PICC_IsNewCardPresent();
  int dish[] ={0x1D, 0xEA, 0xB8, 0x9 };//1222171137 


  if (!rf.PICC_IsNewCardPresent()) { Serial.println("Place the card ");}
    //is new card or not
    if (rf.PICC_ReadCardSerial()) {
      //good to read the addr but not matching ?

      //Serial.println(rf.uid.size);
      Serial.print("UID ");

      for (int i = 0; i < rf.uid.size; i++) {
        Serial.print(rf.uid.uidByte[i]);  // int old[]=rf.uid.uidByte[i];
      }
      Serial.println(" ");
     
    }
bool flag=true;
for (int i = 0; i < rf.uid.size; i++) {
        if (dish[i] != rf.uid.uidByte[i]) {
          //Serial.print("already-dish");
          flag=false;
          break;
        }
      }
if(!flag){
  Serial.println("DISH already in");
 
}

rf.PICC_HaltA();
rf.PCD_StopCrypto1();
delay(2000);
}
