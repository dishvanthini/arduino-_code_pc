#include <LiquidCrystal.h>
#include<time.h>
#include<WiFi.h>//ntp

const int offset=19800;

int SW1=35;//ok button 
int SW2=34;//++
int SW3=39;//++
int SW4=36;//back

int en=12;
int rs=13;

static int sw=0;
int sw_update;
LiquidCrystal l(rs,en,14,27,26,25);
int buzzer=23;
char stime[9];
int alarm_tone=2000;
int alarm_hour = 0;
int alarm_min  = 0;
bool alarm_en = false;
int is12HourMode = 0;

const char* Items[] = {
  "1.SET 24/12hr",
  "2.ALARM",
  "3.TONE", 
  "4.BACK"
 };

int menuIndex = 0;  //  pos
int menuSize = 4;
int topIndex=0;

void setup() {
l.clear();
l.begin(8,2);
//l.backlight();

pinMode(SW1,INPUT);pinMode(SW2,INPUT);pinMode(SW3,INPUT);pinMode(SW4,INPUT);
pinMode(buzzer,OUTPUT);


//Serial.begin(9600);
WiFi.mode(WIFI_STA);
//WiFi.begin("dish","dish123!");
WiFi.begin("Petal","Petal#2024");
//Serial.begin(WiFi.localIP());

configTime(offset,0,"216.239.35.0");
delay(1200);

welcome_updatepage();

}
void loop() {
  showCursor();

  if (buttonPressed(SW3)) {
    if (menuIndex < 1) {
      menuIndex++;
    } else {
      menuIndex = 0;
      topIndex++;
      if (topIndex > menuSize - 2) {
        topIndex = 0;
      }
    }
  }

 
  if (buttonPressed(SW2)) {
    if (menuIndex > 0) {
      menuIndex--;
    } else {
      menuIndex = 1;
      topIndex--;
      if (topIndex < 0) {
        topIndex = menuSize - 2;
      }
    }
  }

  if (buttonPressed(SW1)) {
    execute(topIndex + menuIndex);
  }

  check_alarm();
  delay(200);
}
bool buttonPressed(int pin) {
  if (digitalRead(pin) == LOW) {
    delay(30);
    while (digitalRead(pin) == LOW);
    return true;
  }
  return false;
}
void showCursor() {
  l.clear();l.setCursor(0, 0);
  if (menuIndex == 0) l.print(">");

  else l.print(" ");
  l.print(Items[topIndex]);

  l.setCursor(0, 1);
  if (menuIndex == 1) l.print(">");
  else l.print(" ");
  l.print(Items[topIndex + 1]);
}


void execute(int index){l.clear();
switch(index){
   case 0: // SET 12/24-hour
    l.clear();
    l.setCursor(0,0);
    l.print("Select Mode:");

    while(true) {
        l.setCursor(0,1);
        l.print("SW2:12hr SW3:24hr");

        if(buttonPressed(SW2)) { 
            is12HourMode = 1;
            l.clear();
            l.print("12-Hour Mode");
            welcome_updatepage();//goback
            delay(1000);
            return; // exit m
        }

        if(buttonPressed(SW3)) {
            is12HourMode = 0;
            l.clear();
            l.print("24-Hour Mode");
            welcome_updatepage();//goback
            delay(1000);
            return; 
        }

        if(buttonPressed(SW4)) {
            return;
        }
    }
    break;
    //break;
  
    case 1:
    set_alarm();
    //check_alarm();
    //comparing the stores alram with the new real time clock 
    break;

    case 2:
    l.clear();
    l.setCursor(0,1);
    l.print("SELECT TONE:");
    select_tone(); 
    sw=0;
    break;

    case 3:
    welcome_updatepage();//goback
    //time_12();
    sw=0;
    break;

  }

}

void welcome_updatepage() {
    l.clear();

    l.setCursor(0,0);
    l.print("WELCOME..");
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) return;
    char timeStr[9];
    char dateStr[11];

    sprintf(dateStr,"%02d/%02d", timeinfo.tm_mday, timeinfo.tm_mon + 1);
    // mode
    if (is12HourMode==1) {
        strftime(timeStr, sizeof(timeStr), "%I:%M:%S", &timeinfo);//12
    } else {
        strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);//24
    }

    l.setCursor(0,1);l.print(dateStr); l.print(" ");
    l.print(timeStr);
    delay(2000);
}


//tone(buzzer,1000,2000);
void time_24(){
    struct tm time;
    if(getLocalTime(&time)){//24h
    l.clear();
    //l.setCursor(0,1);//c,r
   // l.print("24hr:");
   char stime[9];
    strftime(stime,sizeof(stime),"%H:%M:%S",&time);
    l.setCursor(0,1);//l.print(dateStr); l.print(" ");
    l.print(stime);
    
    }
}

                                                                                                                                                     
void time_12()
{
  struct tm time;
  if(getLocalTime(&time)){                                                    
    l.clear();
    l.setCursor(0,0);//c,r
    l.print("12hrs:");
    strftime(stime,sizeof(stime),"%I:%M:%S",&time);//12h
    l.setCursor(5,0);
    l.print(stime);
  }

}


void check_alarm() {
  if (!alarm_en) return;

    struct tm time;
      if (!getLocalTime(&time)) return;

      if (time.tm_hour == alarm_hour &&time.tm_min == alarm_min &&time.tm_sec == 0) 
      {
        beep_alarm();
      }
}


void beep_alarm() {
  l.clear();
  l.print("BEEP !!!");

  while (alarm_en) {
    tone(buzzer, alarm_tone);
    delay(300);
    noTone(buzzer);
    delay(300);

    // Stop alarm when SW4 pressed
    if (buttonPressed(SW4)) {
      alarm_en = false;
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
  l.print("SET ALARM");
 
  int a = 0;  

while (true) {
   
    l.setCursor(0, 1);
    if (alarm_hour < 10) l.print("0");
        l.print(alarm_hour);   l.print(":");
    if (alarm_min < 10) l.print("0");
        l.print(alarm_min);

if (buttonPressed(SW2)) {       
  if (a == 0) {         
  alarm_hour++;
      
  if (alarm_hour > 23) alarm_hour = 0;  
      } else {                   
  alarm_min++;
  if (alarm_min > 59) alarm_min = 0;   
      }
      delay(300); 
    }

 if (buttonPressed(SW3)) {       
    if (a == 0) {          
      alarm_hour--;
      if (alarm_hour < 0) alarm_hour = 23; }
      else {                alarm_min--;
          if (alarm_min < 0) alarm_min = 59;  
      }
      delay(300); 
    }

    
if (buttonPressed(SW1)) {
  a++;
  if (a > 1) {
    alarm_en = true;
    l.clear();
    l.print("SAVED");
    delay(1000);
    sw = 0;        
    return;       
  }
}

//deL
if (buttonPressed(SW4)) {     
  l.clear();
  l.print("DEL"); alarm_en = false;
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