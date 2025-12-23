#include<MFRC522.h>
int rs=17;
int en=5;
MFRC522 esp_rf(en,rs);

void setup() {
    Serial.begin(9600);
    SPI.begin();
  	esp_rf.PCD_Init();
}

void loop() {
   if(esp_rf.PICC_IsNewCardPresent())
   {
      if(esp_rf.PICC_ReadCardSerial()){
        Serial.println("card Id ");
         for(int i=0;i<esp_rf.uid.size;i++){
          Serial.print((esp_rf.uid.uidByte[i]),HEX);
         }
         Serial.println("   done");
        esp_rf.PICC_HaltA();
        esp_rf.PCD_StopCrypto1();
      }
    }
   

   else{
    Serial.println("enter new card!!!");
   }
  
delay(1000);
  
}
