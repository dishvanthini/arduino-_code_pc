#include<Wire.h>//i2c comm
#include <Adafruit_GFX.h>//pixel 
#include<Adafruit_SSD1306.h>//oled driver , send to oled via i2c
int width=128;
int height=64;
int addr=0x3C;int ir=6;

Adafruit_SSD1306 conf(width, height,&Wire);//&wire reference to I²C bus 

void setup() {
//reset pin of oled will reset from the begin (-1 skip the reset pin )
Wire.begin();//i2c
conf.begin(SSD1306_SWITCHCAPVCC,addr);//SSD1306_SWITCHCAPVCC powered internally 
pinMode(ir,INPUT);

}

void loop() {
 
 conf.clearDisplay();
 conf.setTextSize(2);//font max 11 one cha
 conf.setCursor(0,0);
 conf.setTextColor(BLACK,WHITE);
 irf();
  ///conf.setTextColor(SSD1306_WHITE);

 //conf.println("Oledddddddddddd");
 //conf.startscrolldiagright(0,4);//page



  //conf.clearDisplay();
 //conf.setCursor(55,0);

 //conf.setTextColor(INVERSE);
  //conf.println("OLED");
 //conf.setCursor(0,20);

  //conf.setTextColor(conf.color565(255,100,0)); // 
  //conf.println("red");//write

  /*******bit
  uint8_t face[]= {
  0b00000111, 0b11100000,
  0b00000111, 0b11100000,
  0b00000111, 0b11100000,
  0b00000111, 0b11100000,

  0b00000111, 0b11100000,
  0b00000111, 0b11100000,
  0b00000111, 0b11100000,
  0b00000111, 0b11100000,

  0b11111111, 0b11111111,
  0b01111111, 0b11111110,
  0b00111111, 0b11111100,
  0b00011111, 0b11111000,
  0b00001111, 0b11110000,
  0b00000111, 0b11100000,
  0b00000011, 0b10000000,
  0b00000001, 0b00000000
};

// void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h,uint16_t color);
//x col , y row 
conf.fillScreen(0); 
for(int i=1;i<10;i++) {

conf.clearDisplay();
conf.drawCircleHelper(60, 30, 30,i,1);//circle arc 
conf. fillCircle(60, 30, 20, 1);  
conf.drawBitmap(50,20,face,16,16,0); 
conf.display();

delay(1000);

}
bit*/
//x=rigt,y=down
//conf. drawCircle(60, 30, 30, 0);    

/*right
 for (int x =0 ; x <width ; x++) {
    conf.clearDisplay();
    conf.setCursor(x, 10);   //moving crusor          
    conf.print("RIGHT");
    conf.display();
    delay(30);                        
  }
//

//left scrolling 
 for (int x =width; x >0; x--) {
    conf.clearDisplay();
    conf.setCursor(x, 20);   //moving crusor          
    conf.print("left");
    conf.display();
    delay(30);                        
  }
*/

}
void irf(){
  int v =digitalRead(ir);
  if(v==HIGH){
    conf.clearDisplay();
    conf.setCursor(30, 20);   //moving crusor          
    conf.print("hand");
    conf.display();
    delay(2000);
  }
  else{
     conf.clearDisplay();
    conf.setCursor(30, 20);   //moving crusor          
    conf.print("no hand");
    conf.display();
    delay(2000);

  }
}