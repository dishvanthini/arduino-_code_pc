#include<LiquidCrystal.h>
int rs=13;
int en=12;
LiquidCrystal esp_led(rs,en,14,27,26,25);
void setup() {
esp_led.begin(8,2);
}

void loop() {
esp_led.clear();
esp_led.setCursor(2,0); //c,r
esp_led.print("newesp32");
delay(1000);

}
