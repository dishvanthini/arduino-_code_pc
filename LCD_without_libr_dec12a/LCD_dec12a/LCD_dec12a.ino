int data[4]={4,5,6,7};
int en=3;
int rs=2;
//lower nibble 3-0
//high nibble 7-4

void setup() {
  pinMode(rs,OUTPUT);
  pinMode(en,OUTPUT);
  for(int i=0;i<4;i++){
  pinMode(data[i],OUTPUT);
  }
   init_lcd();//only once init
   ///print_str("str");
}

void init_lcd(){
 // cmd(51);//(0x33)power the 8bit mode 
 
  cmd(50); //switch 4bit mode(0x32) data width
  cmd(40);// func 4bit enable 0x28
  cmd(14);//cursor on display on 0x0E
  cmd(1);//Clear Display	1
  delayMicroseconds(40);

}
void data_value(uint8_t  a){//string
  
//rs data
//rw 0 
  digitalWrite(rs,HIGH);//data
  data_pass(a);
}

void cmd(uint8_t a){
  digitalWrite(rs,LOW);//cmd
  data_pass(a);

}
void data_pass(uint8_t  a){//a single character-wide buffer.
  for(int i=0;i<4;i++){
  digitalWrite(data[i],(a>>(i+4))&1);//upper nible (data>>4)&(0001)=0000; 4 to 7  0011
  }
  enable();    
  for(int i=0;i<4;i++){
  digitalWrite(data[i],(a>>i)&1);//to acess each bit //least lower nibble (data>>0)&(0001)=0000;  0 to 3
  }
  enable();
}
 void enable(){
  digitalWrite(en,HIGH);//read the data or cmd
  delayMicroseconds(2);
  digitalWrite(en,LOW);  
  delayMicroseconds(4);
}
void print_str(char s[]){
  for(int i=0;s[i]!='\0';i++){
    data_value(s[i]);
  }
}

void print_int(uint8_t a){//1234 
  if(a==0){
    data_value('0');
return;  }

    print_int(a/10);//remove last 123 12 1 0 
    data_value((a%10)+'0');//pass last digit with ascii 4 3 2 1 

}

void loop() {

 //cmd(20);//moves chrc to right 
 //data_value('Herr');//only it takes last chr,one chr at a time 
 //data_value('h');
 ///cmd(0x00);//blinkoff
  cmd(0x28);

 cmd(0x80);//force to start 1st line...
//print_str("str....");
//delay(1000); 
cmd(0x0E);
cmd(0x10);//2nd
cmd(0x1C);//scr
delay(1000);
print_str(" str.");

//print_int(12);

}








/*EN pulse      → 1 microsecond
Normal command → 40 microseconds
Clear/Home    → 2 milliseconds
*/
