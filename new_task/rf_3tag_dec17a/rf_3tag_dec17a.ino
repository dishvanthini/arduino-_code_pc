//compare two id that already existing , new one

#include <SPI.h>
#include <MFRC522.h>
int rs = 17;
int ss = 10;
MFRC522 rf(ss, rs);
//void PCD_Init(byte chipSelectPin, byte resetPowerDownPin);
char dish[]="1222171137";  
  char new_one[]="1138210839";
  char new_two[]="14418916534";
 char s[12]="";
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rf.PCD_Init();
}

void loop() {
  //int dish[] ={0x1D, 0xEA, 0xB8, 0x9 };//1222171137 
  // int new1[]={0x90, 0xBD, 0xA5, 0x22};//90BDA522 //14418916534 
  //int new2[]={0x71, 0x52, 0x6C, 0x27};//71526C27//UID 1138210839 
  
  read_rf();//uid 
  rf.PICC_HaltA();
  rf.PCD_StopCrypto1();
  conv_string();
  cmp();

  
  delay(2000);

}

void read_rf(){
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
}
void conv_string() {
  int index = 0;
  for (int i = 0; i < rf.uid.size; i++) {
    index += sprintf(s + index, "%d", rf.uid.uidByte[i]); 
  }
  s[index] = '\0'; 
}
void cmp(){
  conv_string();
  if(strcmp(s,dish)==0){
    Serial.println("dish");
  }
  else if (strcmp(s,new_one)==0){
    Serial.println("new_one");
  }
  else if(strcmp(s,new_two)==0){
    Serial.println("new_two");
  }
  else{
    Serial.println("someother");
  }
}
