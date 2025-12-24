
//wifi connect sta mode 
#include<time.h>
#include<WiFi.h>
const int gmtoff=19800;//sec
const int dst=0;//daylight saving time
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin("dish","dish123!");//wifi 
  Serial.print("connected to..");
  Serial.print(WiFi.localIP());
  configTime(gmtoff,dst,"216.239.35.0");//connect to server 
}

void loop() {
  struct tm time;
  // put your main code here, to run repeatedly:
  Serial.print("time ");
  if(getLocalTime(&time)){
    Serial.printf("current %d:%d:%d ",time.tm_hour,time.tm_min,time.tm_sec);
    Serial.printf("|Date %02d:%02d:%04d",time.tm_mon,time.tm_mday,time.tm_year);
  }
  else{
    Serial.print("not getting the time....");
  }

}
//time libr for time func and manage 
//connect to NTP using address addr pool.ntp.org // 216.239.35.0
//gmt offset
//dst offsect
//print the time 
         