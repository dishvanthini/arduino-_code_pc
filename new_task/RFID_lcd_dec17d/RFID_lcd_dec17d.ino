#include <LiquidCrystal.h>
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

//int data[4]={4,5,6,7};
int en=3;
int rslcd=2;
LiquidCrystal l(rslcd, en, 4, 5, 6, 7);

void setup(){
  SPI.begin();
  rf.PCD_Init();

    l.begin(8,2);//chr size=5x10;
    l.setCursor(0,0);///(col,row)
    l.print("RFID project");
    
}
void loop(){  

  read_rf();//uid 
  rf.PICC_HaltA();
  rf.PCD_StopCrypto1();
  conv_string();
  cmp();
  delay(2000);
  //l.print("LCD");
  
}

void read_rf(){
if (!rf.PICC_IsNewCardPresent()) { Serial.println("Place the card ");}
    //is new card or not
    if (rf.PICC_ReadCardSerial()) {
      //good to read the addr but not matching ?
      //Serial.println(rf.uid.size);
      l.setCursor(0,1);///(col,row)
      l.print("reading card!");
      //l.clear();
      // l.print("RFID project");

      /*for (int i = 0; i < rf.uid.size; i++) {
        Serial.print(rf.uid.uidByte[i]);  // int old[]=rf.uid.uidByte[i];
      }
      Serial.println(" ");
     */
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
    l.setCursor(0,1);///(col,row)
    l.print("Dish");
  }
  else if (strcmp(s,new_one)==0){
    l.setCursor(0,1);
    l.print("New_one");
  }
  else if(strcmp(s,new_two)==0){
    l.setCursor(0,1);///(col,row)
    l.print("New_two");
  }
  else{
   l.setCursor(0,1);///(col,row)
    l.print("Invalid"); 
  }
}
