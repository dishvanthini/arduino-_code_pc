#include<Wire.h>//i2c
#include<Adafruit_GFX.h>//pixcel
#include<Adafruit_SSD1306.h>//driver
int width=128;
int height =64;
int Addr=0x3C;
//int sda=21,scl=22;
int sda=17,scl=16;
Adafruit_SSD1306 esp_oled (width,height,&Wire);
void setup() {
Wire.begin(sda,scl); 

esp_oled.begin(SSD1306_SWITCHCAPVCC,Addr);
}

void loop() {
esp_oled.clearDisplay();
esp_oled.setTextSize(2);

esp_oled.setCursor(0,0);
esp_oled.setTextColor(WHITE,BLACK);

esp_oled.print("nerrr");
esp_oled.display();
delay(1000);
right_Scroll();
}
void right_Scroll(){
  for(int i=0;i<width;i++){
    esp_oled.clearDisplay();
    esp_oled.setTextSize(2);

    esp_oled.setCursor(i,15);
    esp_oled.setTextColor(WHITE,BLACK);

    esp_oled.print("right");
    esp_oled.display();
    delay(10);
}
  
}