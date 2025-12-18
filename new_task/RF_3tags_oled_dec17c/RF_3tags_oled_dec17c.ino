#include<Wire.h>//i2c comm
#include <Adafruit_GFX.h>//pixel 
#include<Adafruit_SSD1306.h>//oled driver , send to oled via i2c

#include <SPI.h>
#include <MFRC522.h>
int width=128;
int height=64;
int addr=0x3C;
Adafruit_SSD1306 conf(width, height,&Wire);//&wire reference to I²C bus 

int ss = 10;int rs = 17;

MFRC522 rf(ss, rs);
char dish[]="1222171137";  
char new_one[]="1138210839";
char new_two[]="14418916534";
char s[12]="";

void setup() {
//reset pin of oled will reset from the begin (-1 skip the reset pin )
Wire.begin();//i2c
conf.begin(SSD1306_SWITCHCAPVCC,addr);//SSD1306_SWITCHCAPVCC powered internally 

Serial.begin(9600);
SPI.begin();
rf.PCD_Init();}

void loop() {
 
  read_rf();//uid 
  rf.PICC_HaltA();
  rf.PCD_StopCrypto1();
  conv_string();
  cmp();
  delay(2000);


}


void confr(){
 conf.clearDisplay();
 conf.setTextSize(2);//font max 11 one cha
 conf.setCursor(2,2);
 conf.setTextColor(BLACK,WHITE);
}
void read_rf(){
if (!rf.PICC_IsNewCardPresent()) { //Serial.println("Place the card ");
 confr();
 conf.print("place card");
 conf.display();}
    //is new card or not
    if (rf.PICC_ReadCardSerial()) {
      //good to read the addr but not matching ?
      //Serial.println(rf.uid.size);
      //Serial.print("UID ");
        confr();
        conf.print("got!");
        conf.display();

      for (int i = 0; i < rf.uid.size; i++) {
        Serial.print(rf.uid.uidByte[i]);  // int old[]=rf.uid.uidByte[i];
      }
      Serial.println(" ");
     
    }
  delay(1000);
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
    //Serial.println("dish");
    confr();
    confr();
    conf.print("dish");
    conf.display();
  }
  else if (strcmp(s,new_one)==0){
    //Serial.println("new_one");
    confr();
    conf.print("new_one");
    conf.display();
  }
  else if(strcmp(s,new_two)==0){
      confr();
      conf.print("new_two");
      conf.display();
  }
  else{
     confr();
      conf.print("no card");
      conf.display();
  }
}
