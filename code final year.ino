#include <Servo.h>

#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo horizontal; // horizontal servo
int servoh = 5; 
int servohLimitHigh = 100;
int servohLimitLow = 2;

// 65 degrees MAX

Servo vertical; // vertical servo
int servov = 45; 
int servovLimitHigh = 60;
int servovLimitLow = 1;

// LDR pin connections
// name = analogpin;
int ldrlt = A2; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = A3; //LDR top rigt - BOTTOM RIGHT
int ldrld = A0; //LDR down left - TOP LEFT
int ldrrd = A1; //ldr down rigt - TOP RIGHT

void setup(){

lcd.init();
lcd.backlight();

horizontal.attach(9);
vertical.attach(10);
horizontal.write(180);
vertical.write(45);
delay(2500);
 lcd.setCursor(0,0);
lcd.print("2 AXIS SOLAR TRACKER");

lcd.setCursor(0,1);
lcd.print("ANJALI");
   
   lcd.setCursor(10,1);
lcd.print("PRIYANKA");
  
lcd.setCursor(0,3);
lcd.print("PAYAL");

lcd.setCursor(10,3);
lcd.print("NUNI");



   pinMode(ldrlt,INPUT); 
   pinMode(ldrld,INPUT);
   pinMode(ldrrt,INPUT);
   pinMode(ldrrd,INPUT);
}
void loop() {

int lt = analogRead(ldrlt); // top left
int rt = analogRead(ldrrt); // top right
int ld = analogRead(ldrld); // down left
int rd = analogRead(ldrrd); // down right
int dtime = 10; int tol = 90; // dtime=diffirence time, tol=toleransi
int avt = (lt + rt) / 2; // average value top
int avd = (ld + rd) / 2; // average value down
int avl = (lt + ld) / 2; // average value left
int avr = (rt + rd) / 2; // average value right
int dvert = avt - avd; // check the diffirence of up and down
int dhoriz = avl - avr;// check the diffirence og left and rigt

if (-1*tol > dvert || dvert > tol) 
 {
 if (avt > avd)
 {
 servov = ++servov;
 if (servov > servovLimitHigh)
 {servov = servovLimitHigh;}
 }
 else if (avt < avd)
 {servov= --servov;
 if (servov < servovLimitLow)
 { servov = servovLimitLow;}
 }
 vertical.write(servov);
 }
if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
 {
 if (avl > avr)
 {
 servoh = --servoh;
 if (servoh < servohLimitLow)
 {
 servoh = servohLimitLow;
 }
 }
 else if (avl < avr)
 {
 servoh = ++servoh;
 if (servoh > servohLimitHigh)
 {
 servoh = servohLimitHigh;
 }
 }
 else if (avl = avr)
 {
 delay(5000);
 }
 horizontal.write(servoh);
 }
 
 delay(dtime);
 
}
