#include <LiquidCrystal.h>

//int data[4]={4,5,6,7};
int en=3;
int rs=2;
LiquidCrystal l(rs, en, 4, 5, 6, 7);
void setup(){
l.begin(8,2);//chr size=5x10;
  l.setCursor(0,1);///(col,row)
   l.print("LCD");
    l.setCursor(0,0);///(col,row)
    l.print("New");
}
void loop(){  

  //l.print("LCD");
  
}