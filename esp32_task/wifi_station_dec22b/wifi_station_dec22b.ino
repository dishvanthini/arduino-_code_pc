#include"WiFi.h"
char wifi_name[]="Dummy";
char password[]="pass";

void setup() {
  //serial monitor
  WiFi.mode(WIFI_AP_STA);
  Serial.begin(115200);
  //begin wifi 
  //WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_name,password);
  //WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP_new","123!");
  // WiFi.mode(WIFI_AP_STA);
}

void loop() {
  Serial.println("Connecting");
  //Serial.print(WiFi.status())
  delay(1000);
  Serial.println(WiFi.localIP());
  Serial.println("the ESP32 default ip ");
  Serial.println(WiFi.softAPIP());

}
