#include <Wire.h>

#include <LiquidCrystal_I2C.h> //LCD Library

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int buttonpin = 10;
int h=0;
int m=0;
int s=0;
int state = 0;
String time;
void setup() {
  // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
  Serial.begin(9600);
  pinMode (buttonpin, INPUT);
  lcd.begin(16, 2);

  // 閃爍三次
  for(int i = 0; i < 3; i++) {
    lcd.backlight(); // 開啟背光
    delay(250);
    lcd.noBacklight(); // 關閉背光
    delay(250);
  }
    lcd.backlight();

  // 輸出初始化文字
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print("NKNU YUYT-Lab");
    delay(1000);
    lcd.setCursor(0, 1); // 設定游標位置在第二行行首
    lcd.print("Hello, Maker!");
    delay(1000);
    lcd.clear(); //顯示清除
  }
  void loop() {
    lcd.clear();
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print("NKNU YUYT-Lab");
    lcd.setCursor(0,1);  
    lcd.print("TIME:");
    if(h < 10){
      lcd.print("0");
    } 
    lcd.print(h); 
    lcd.print(":");
    if(m < 10){
      lcd.print("0");
    }  
    lcd.print(m); 
    lcd.print(":"); 
    if(s < 10){
      lcd.print("0");
    } 
    lcd.print(s);
    delay(1000);
    s=s+1;
    if(s==60){ 
       s=0; 
       m=m+1; 
      } 
    if(m==60) { 
       m=0; 
       h=h+1; 
    } 
 }
