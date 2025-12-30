#include <LiquidCrystal.h>
#include<time.h>
#include<WiFi.h>//ntp
LiquidCrystal l(13,12,14,27,26,25);
int buzzer=23;

int SW1=35;//ok button 
int SW2=34;//++
int SW3=39;//++
int SW4=36;//back

static int sw=0;
int sw_update;

char stime[9];
const char* Items_tone[] = {
  "1.Tone 1000 Hz",
  "2.Tone 2000 Hz",
  "3.Tone 5000 Hz", 
  "4.Tone 7000 Hz"
 };

const char* Items[] = {
  "1.SET 24/12hr",
  "2.ALARM      ",
  "3.TONE       ", 
  "4.BACK       "
};



struct clockSet{

bool is12HourMode;
int offset;

};

struct alarmSet{
int alarm_hour;
int alarm_min;
int alarm_tone[4];
int toneIndex;       
int alarm_duration;
int snooze_min;
bool alarm_en;
bool  isPM = false; //its AM 

};
struct Menu{

int menuIndex;  // pos
int menuSize;
int topIndex;
bool inMenu;

};

clockSet clk= {false, 19800 };  //  24-hour clk mode enable 
alarmSet a = {0, 0, {1000,2000,5000,7000},0, 5,false}; ///alarm en 
Menu menu={0,4,0,false};

void setup() {
l.clear();
l.begin(8,2);
//l.backlight();

pinMode(SW1,INPUT_PULLUP);pinMode(SW2,INPUT_PULLUP);pinMode(SW3,INPUT_PULLUP);pinMode(SW4,INPUT_PULLUP);
pinMode(buzzer,OUTPUT);


//Serial.begin(9600);
WiFi.mode(WIFI_STA);
//WiFi.begin("dish","dish123!");
WiFi.begin("Petal","Petal#2024");
//Serial.begin(WiFi.localIP());

configTime(19800,0,"216.239.35.0");
delay(1200);

//welcome_updatepage();


}

void loop() {
  if(!menu.inMenu){
     welcome_updatepage();

  if (buttonPressed(SW1)){
      menu.inMenu=true;
      menu.menuIndex=0;
      menu.topIndex=0;
      l.clear();
      showCursor();
  }
  return;
}
  
  showCursor();


  if (buttonPressed(SW3)) {
    if (menu.menuIndex < 1) {
      menu.menuIndex++;
    } else {
      menu.menuIndex = 0;
      menu.topIndex++;
      if (menu.topIndex > menu.menuSize - 2) {
        menu.topIndex = 0;
      }
    }
  }

 
  if (buttonPressed(SW2)) {
    if (menu.menuIndex > 0) {
      menu.menuIndex--;
    } else {
      menu.menuIndex = 1;
      menu.topIndex--;
      if (menu.topIndex < 0) {
        menu.topIndex = menu.menuSize - 2;
      }
    }
  }

  if (buttonPressed(SW1)) {
    execute(menu.topIndex + menu.menuIndex);
  }
  
  if(buttonPressed(SW4)){
    menu.inMenu=false;
    l.clear();
  }
  
  check_alarm();
  delay(200);

}


void execute(int index){  ////l.clear();
switch(index){
    case 0: // SET 12/24-hour
    l.setCursor(0,0);
    l.print("Select Mode:  ");
    
  l.setCursor(0,1);
  l.print("SW2:12hr SW3:24hr");
while(true){
  if(buttonPressed(SW2)) {
        l.clear();
        l.print("12-Hour Mode");      delay(1000);

        clk.is12HourMode = true; return;
        }
        
      if(buttonPressed(SW3)) {
        l.clear(); 
      l.print("24-Hour Mode");
      delay(1000);
        clk.is12HourMode = false; return;
        }

      if(buttonPressed(SW4)) {
        l.print("default mode");      delay(1000);

        return;
        }

}
    
    break;
  
    case 1:
    if (!clk.is12HourMode){
      set_alarm();//24hours
      }
    else set_12_alarm();

    break;

    case 2:
    l.clear();
    l.setCursor(0,0);
    l.print("SELECT TONE:"); 
    set_tone_duration(); 
    l.clear();//new
    select_tone();

    sw=0;
    break;

    case 3:
    menu.inMenu=false;
    sw=0;
    break;

  }

}

void set_alarm() {
  l.clear();
  l.print("SET ALARM");
  int a1 = 0;  

while (true) {
   
    l.setCursor(0, 1);
    if (a.alarm_hour < 10) l.print("0");
        l.print(a.alarm_hour);   l.print(":");
    if (a.alarm_min < 10) l.print("0");
        l.print(a.alarm_min);

if (buttonPressed(SW2)) {       
  if (a1 == 0) {         
  a.alarm_hour++;
      
  if (a.alarm_hour > 23) a.alarm_hour = 0;  
      } else {                   
  a.alarm_min++;

  if (a.alarm_min > 59) a.alarm_min = 0;   
      }
      delay(300); 
    }

 if (buttonPressed(SW3)) {       
    if (a1== 0) {          
      a.alarm_hour--;
      if (a.alarm_hour < 0) a.alarm_hour = 23;
       }
      else { 
        a.alarm_min--;
        if (a.alarm_min < 0) a.alarm_min = 59;  
      }
      delay(300); 
    }

    
if (buttonPressed(SW1)) {
  a1++;
  if (a1 > 1) {
    a.alarm_en = true;
    l.clear();
    l.print("SAVED");
    delay(1000);
    set_snooze();
    sw = 0;        
    return;       
  }
}

//deL
if (buttonPressed(SW4)) {     
  l.clear();
  l.print("DEL"); 
  a.alarm_en = false;
  delay(1000);
  return;
  }
  }
}


void set_12_alarm() {
  l.clear();
  l.print("SET ALARM 12hrs");

  int a1 = 0;   // 0hr 1min 2AM/PM
  int Hour12 = 1;
 a.isPM = false; //its AM 

while (true) {
    l.setCursor(0,1);
    if (Hour12 < 10) l.print("0");
    l.print(Hour12);
    l.print(":");

    if (a.alarm_min < 10) l.print("0");
    l.print(a.alarm_min);
    l.print(a.isPM ? " PM" : " AM");

  
if (buttonPressed(SW2)) {
      if (a1 == 0) {
        Hour12++;
        if (Hour12 > 12) Hour12 = 1;
      } 
      else if (a1 == 1) {
        a.alarm_min++;
        if (a.alarm_min > 59) a.alarm_min = 0;
      } 
      else {
        a.isPM = !a.isPM;
      }
      delay(300);
    }
  
if (buttonPressed(SW3)) {
      if (a1 == 0) {
        Hour12--;
        if (Hour12 < 1) Hour12 = 12;
      } 
      else if (a1 == 1) {
        a.alarm_min--;
        if (a.alarm_min < 0) a.alarm_min = 59;
      } 
      else {
        a.isPM = !a.isPM;
      }
      delay(300);
    }

if (buttonPressed(SW1)) {
      a1++;
      if (a1 > 2) {
       
        if (Hour12 == 12)///////////convert
          a.alarm_hour = a.isPM ? 12 : 0;
        else
          a.alarm_hour = a.isPM ? Hour12 + 12 : Hour12;//0-12 Am 

        a.alarm_en = true;
        l.print(" SAVED");
        delay(1000);
        set_snooze();
        return;
      }
    }

    if (buttonPressed(SW4)) return;
  }
}


void beep_alarm() {
  l.clear();
  l.print("BEEP!!!!");
  l.setCursor(0, 1);
  l.print("3.snooze 4.stop");
  // a.toneIndex = pos;          
    //int selectedTone = a.alarm_tone[pos]; 
    
  while (a.alarm_en) {
tone(buzzer, a.alarm_tone[a.toneIndex], a.alarm_duration*1000);
    delay(300);
    noTone(buzzer);
    delay(300);

    // Stop alarm when SW4 pressed
    if (buttonPressed(SW4)) {
      a.alarm_en = false;
      noTone(buzzer);
      ////l.clear();
      l.print("STOPPED");
      delay(1000);
      return;
    }
    if (buttonPressed(SW3)){//sw3 snooze
      noTone(buzzer);
      a.alarm_min+=a.snooze_min;
      check_alarm();
      tone(buzzer, a.alarm_tone[a.toneIndex], a.alarm_duration*1000);
      delay(300);
      noTone(buzzer);
      delay(300);
      //l.clear();
      l.print("will Snooze");
      delay(1000);
      return;
    }
  }
}


void select_tone() {
  int pos = 0;
  int topIndex = 0;

  while (true) {

    l.setCursor(0,0);
    if (topIndex == pos) l.print(">"); else l.print(" ");


    l.print(Items_tone[topIndex]);          // u

    l.setCursor(0,1);
    if (topIndex+1 == pos) l.print(">"); else l.print(" ");
    l.print(Items_tone[topIndex+1]);        // d

    //new 
    //l.clear();
    if (buttonPressed(SW3)) { 
      pos++;
      if (pos > 3) pos = 0;
      topIndex = min(pos, 2);
    }

    if (buttonPressed(SW2)) { 
      pos--;
      if (pos < 0) pos = 3;
      topIndex = min(pos, 2);
    }

    if (buttonPressed(SW1)) { 
      //new clear
      //l.clear();
      a.toneIndex = pos;
      int selectedTone = a.alarm_tone[pos];
      tone(buzzer, selectedTone, a.alarm_duration*1000);
      l.clear();
      l.setCursor(0,0);
      l.print("TONE SELECTED");
      delay(1000);
      
      return;
    }

    if (buttonPressed(SW4)) return;
  }
}



void set_snooze() {
  l.clear();//new
  l.print("SET SNOOZE");
  a.snooze_min=0;//reset to go with the new snooze time 
  while (true) {
    l.setCursor(0,1);
    l.print("MIN: ");
    if (a.snooze_min < 10) l.print("0");
    l.print(a.snooze_min);
    l.print("   ");

    if (buttonPressed(SW2)) {
      a.snooze_min++;
      if (a.snooze_min > 30) a.snooze_min = 1;
    }

    if (buttonPressed(SW3)) {
      a.snooze_min--;
      if (a.snooze_min < 1) a.snooze_min = 30;
    }

    if (buttonPressed(SW1)) {
      l.clear();//new
      l.print("SNOOZE SAVED");
      delay(1000);
      return;
    }

    if (buttonPressed(SW4)) return;
  }
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
//l.clear();
 l.setCursor(0, 0);
  if (menu.menuIndex== 0) l.print(">");

  else l.print(" ");
  l.print(Items[menu.topIndex]);

  l.setCursor(0, 1);
  if (menu.menuIndex == 1) l.print(">");
  else l.print(" ");
  l.print(Items[menu.topIndex + 1]);
}
void check_alarm() {
  if (!a.alarm_en) return;

    struct tm time;
      if (!getLocalTime(&time)) return;

      if (time.tm_hour == a.alarm_hour &&time.tm_min == a.alarm_min &&time.tm_sec == 0) 
      {
        beep_alarm();
      }
}

void welcome_updatepage() {
    //l.clear();

    l.setCursor(0,0);
    l.print("WELCOME..");
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) return;
    char timeStr[9];
    char dateStr[11];

    sprintf(dateStr,"%02d/%02d", timeinfo.tm_mday, timeinfo.tm_mon + 1);
    // mode
    if (clk.is12HourMode==true) {
        strftime(timeStr, sizeof(timeStr), "%I:%M:%S", &timeinfo);//12
    } else {
        strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);//24
    }

    l.setCursor(0,1);l.print(dateStr); l.print(" ");
    l.print(timeStr);
}


void set_tone_duration() {
  l.clear();
  l.print("TONE DURATION");
  a.alarm_duration=0;//reset to go with the new snooze time 
  while (true) {
    l.setCursor(0,1);
    l.print("Sec: ");
    if (a.alarm_duration < 10) l.print("0");
    l.print(a.alarm_duration);
    l.print("   ");

    if (buttonPressed(SW2)) {
      a.alarm_duration++;
      if (a.alarm_duration > 30) a.alarm_duration = 1;
    }

    if (buttonPressed(SW3)) {
      a.alarm_duration--;
      if (a.alarm_duration < 1) a.alarm_duration = 30;
    }

    if (buttonPressed(SW1)) {
      l.clear();
      l.print("DURATION SAVED");
      delay(1000);
      return;
    }

    if (buttonPressed(SW4)) return;
  }
}
