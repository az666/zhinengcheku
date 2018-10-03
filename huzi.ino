#include <Servo.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
Servo myservo;  
int pos = 0;    
int up_flag;
int down_flag;
int go_flag;
int out_flag;
int up_flag2;
int down_flag2;
int go_flag2;
int out_flag2;
int val ;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(A1,INPUT);
  myservo.attach(9);  
  myservo.write(70);  
  lcd.init();             
  lcd.backlight();
  lcd.setCursor(0, 1);//打印lcd第2行信息
  lcd.print("ZhouJinHu");
  lcd.setCursor(0, 1);//打印lcd第2行信息
  delay(1000);
    lcd.setCursor(0, 1);//打印lcd第2行信息
  lcd.print("Intelligent garage");
  lcd.setCursor(0, 1);//打印lcd第2行信息
  delay(2000);
} 
void up(){
  if (up_flag )
  {
   // Serial.println("00000");
    }
  else{
   for(pos = 70; pos <= 160; pos += 1) 
  {                                 
    myservo.write(pos);              
    delay(15);                      
  } 
  up_flag =1;
  down_flag =0;  
  }
}
void down(){
  if (down_flag)
  {}
  else{
  for(pos = 160; pos>=70; pos-=1)    
  {                                
   myservo.write(pos);              
    delay(15);                 
  } 
   down_flag =1;  
   up_flag = 0;
  }
  }
  /////////////////////////////////////////////////////////out
  void up2(){
  if (up_flag2 )
  {
    //Serial.println("00000");
    }
  else{
   for(pos = 70; pos <= 160; pos += 1) 
  {                                 
    myservo.write(pos);              
    delay(15);                      
  } 
  up_flag2 =1;
  down_flag2 =0;  
  }
}
void down2(){
  if (down_flag2)
  {}
  else{
  for(pos = 160; pos>=70; pos-=1)    
  {                                
   myservo.write(pos);              
    delay(15);                 
  } 
   down_flag2 =1;  
   up_flag2 = 0;
  }
  }
  int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;
}
void jin()
{
  if(digitalRead(A0) == 0  && up_flag==0)
  {
    up();
    }  
if ( distance<10 && up_flag==1 ) 
{
  //代表车头触发超声波还未进入       
  go_flag =1;
  delay(100);
  } 
  if( distance>10 && go_flag==1)
  {
    down(); 
    go_flag =0;   // 代表已经进入
      val = val +1;
    }  
  
  }
  void chu()
  {
     if(distance<10  && up_flag2==0)
  {
    up2();
    }  
if ( digitalRead(A0) == 0 && up_flag2==1 ) 
{
  //代表车头触发超声波还未进入       
  go_flag2 =1;
  delay(100);
  } 
  if( digitalRead(A0) == 1 && go_flag2==1)
  {
    down2(); 
    go_flag2 =0;   // 代表已经进入
    val = val-1;
    } 
    }
void loop() 
{ 
  Serial.println(val);
  distance = calculateDistance();   //测距
  if(digitalRead(A1)==1) jin();else chu();
  lcd.setCursor(1, 0);//打印lcd第2行信息
  lcd.print("car number:");
  lcd.setCursor(14, 0);//打印lcd第2行信息
  lcd.print(val);
  delay(200);
  lcd.clear();//lcd清屏，所以屏幕会闪属正常现象
} 

