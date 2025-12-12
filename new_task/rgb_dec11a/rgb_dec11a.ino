#include <Adafruit_NeoPixel.h>
int led=4;//led=n
int pin=8;

Adafruit_NeoPixel glow(pin ,led,NEO_GRB + NEO_KHZ800);


void setup() {
  glow.begin();
  glow.show();

}

void loop() {
    


    for(int i=0;i<pin;i++){
       glow.setPixelColor(i, glow.Color(255,0,0));
    }
   glow.show();
    delay(1000);
    
for(int i=0;i<pin;i++){
       glow.setPixelColor(i, glow.Color(0,255,0));//gr
    }
   glow.show();
    delay(1000);
    

}
