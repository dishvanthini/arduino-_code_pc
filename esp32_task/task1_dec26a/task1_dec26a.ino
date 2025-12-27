#include <LiquidCrystal.h>
#include<time.h>
#include<WiFi.h>//ntp
const int offset=19800;
int SW1=35,SW2=34,SW3=39,SW4=36;
int en=12;
int rs=13;int sw=0;

LiquidCrystal l(rs,en,14,27,26,25);
int buzzer=23;
char stime[9];
int alarm_tone=2000;
int alarm_hour = 0;
int alarm_min  = 0;
bool alarm_enable = false;
void setup() {
l.clear();
l.begin(8,2);
welcome_page();//lcd
pinMode(SW1,INPUT);pinMode(SW2,INPUT);pinMode(SW3,INPUT);pinMode(SW4,INPUT);
pinMode(buzzer,OUTPUT);


//Serial.begin(9600);
WiFi.mode(WIFI_STA);
WiFi.begin("dish","dish123!");
//Serial.begin(WiFi.localIP());

configTime(offset,0,"216.239.35.0");
}
bool buttonPressed(int pin) {
  if (digitalRead(pin) == LOW) {
    delay(30);
    while (digitalRead(pin) == LOW);
    return true;
  }
  return false;
}

void loop(){
  
  time_12();
  l.clear();
  l.setCursor(0, 0);
  l.print("1.SET  2.ALARM");
  l.setCursor(0, 1);
  l.print("3.TONE 4.BACK");
  //l.autoscroll();
  //////////menu
  /*if (digitalRead(SW1) == LOW) sw = 1;
  if (digitalRead(SW2) == LOW) sw = 2;
  if (digitalRead(SW3) == LOW) sw = 3;
  if (digitalRead(SW4) == LOW) sw = 4;*/
  if (buttonPressed(SW1)) sw = 1;
  else if (buttonPressed(SW2)) sw = 2;
  else if (buttonPressed(SW3)) sw = 3;
  else if (buttonPressed(SW4)) sw = 4;

//print menu option menu are;
  switch(sw){
    case 1://menu//setting 12hrous 24hours
    l.clear();
    time_24(); 
    break;

    case 2:
    set_alarm();
    //check_alarm();
    //comparing the stores alram with the new real time clock 
    break;

    case 3:
    l.clear();
    l.setCursor(0,1);
    l.print("SELECT TONE:");
    select_tone();
    sw=0;
    break;

    case 4:
    welcome_page();
    time_12();
    sw=0;
    break;

  }
  check_alarm();
  delay(2000);
}

//tone(buzzer,1000,2000);
void time_24(){
    struct tm time;
    if(getLocalTime(&time)){//24h
    l.clear();
    l.setCursor(0,1);//c,r
    l.print("24hr:");
      strftime(stime,sizeof(stime),"%H:%M:%S",&time);
      l.setCursor(5,1);
      l.print(stime);
    }
}
void welcome_page()
{
  l.setCursor(0,0);
  l.print("WELCOME..");
}


void time_12()
{
  struct tm time;
  if(getLocalTime(&time)){
    l.clear();
    l.setCursor(0,1);//c,r
    l.print("12hrs:");
    strftime(stime,sizeof(stime),"%I:%M:%S",&time);//12h
    l.setCursor(5,1);
    l.print(stime);
  }

}


void check_alarm() {
  if (!alarm_enable) return;

    struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) return;

      if (timeinfo.tm_hour == alarm_hour &&timeinfo.tm_min == alarm_min &&timeinfo.tm_sec == 0) 
      {
        beep_alarm();
      }
}


void beep_alarm() {
  l.clear();
  l.print("BEEP !!!");

  while (alarm_enable) {
    tone(buzzer, alarm_tone);
    delay(300);
    noTone(buzzer);
    delay(300);

    // Stop alarm when SW4 pressed
    if (buttonPressed(SW4)) {
      alarm_enable = false;
      noTone(buzzer);
      l.clear();
      l.print("STOPPED");
      delay(1000);
      return;
    }
  }
}

void set_alarm() {
  l.clear();
  l.print("SETALARM");
 
  int a = 0;  

while (true) {
   
    l.setCursor(0, 1);
    if (alarm_hour < 10) l.print("0");
        l.print(alarm_hour);   l.print(":");
    if (alarm_min < 10) l.print("0");
        l.print(alarm_min);

if (buttonPressed(SW1)) {       
  if (a == 0) {         
  alarm_hour++;
      
  if (alarm_hour > 23) alarm_hour = 0;  
      } else {                   
  alarm_min++;
  if (alarm_min > 59) alarm_min = 0;   
      }
      delay(300); 
    }

 if (buttonPressed(SW2)) {       
    if (a == 0) {          
      alarm_hour--;
      if (alarm_hour < 0) alarm_hour = 23; }
      else {                alarm_min--;
          if (alarm_min < 0) alarm_min = 59;  
      }
      delay(300); 
    }

    
if (buttonPressed(SW3)) {
  a++;
  if (a > 1) {
    alarm_enable = true;
    l.clear();
    l.print("SAVED");
    delay(1000);
    sw = 0;        
    return;       
  }
}

//de
if (buttonPressed(SW4)) {     
  l.clear();
  l.print("DEL");
  delay(1000);
  return;
  }
  }
}
void select_tone() {
  

  while (true) {
   if (buttonPressed(SW1)) { 
    alarm_tone = 1000; break; }
    if (buttonPressed(SW2)) { 
      alarm_tone = 1100; break; }
    if (buttonPressed(SW3)) { 
      alarm_tone = 1200; break; }
    if (buttonPressed(SW4)) { 
    alarm_tone = 1500; break; }
  }

  l.clear();
  l.print("TONE SET");
  delay(1000);
}
