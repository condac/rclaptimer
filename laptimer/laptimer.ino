#include <Wire.h>
#include <LiquidCrystal.h>

const int buttonPin = A0; 
int test;
int laps = 0;
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );
String extid = "12.34";

unsigned long best = 9999999;

unsigned long lasttime;
unsigned long readtime;
unsigned long time;
unsigned long last1;
float diff;
float timefloat;


void setup()
{
    
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);  
  
  lcd.begin(16, 2);
  lcd.print(".");
}

void loop()
{
    drawDisplay();
    if (!digitalRead(buttonPin) ) {
      readtime = millis();
      last1 = time;
      time = readtime-lasttime;
      timefloat = (float) ((int)(time/10))/100;
      laps++;
      
      //diff
      diff=((float)time-(float)last1) /1000.0;
      
      if (time < best) {
        best = time;
      }
      
      //writeTime();
      lasttime=readtime;
      drawDisplay();
      delay(2000);
    }
}

void drawDisplay() {
  
  //Laps
  lcd.setCursor(0,0);
  lcd.print("LAP");
  lcd.setCursor(0,1);
  lcd.print(laps);
  
  //Best
  lcd.setCursor(10,1);
  lcd.print("");
  printMilli(best);
  
  //Last
  lcd.setCursor(3,0);
  printMilli(time);
  
  //Last1
  lcd.setCursor(3,1);
  printMilli(last1);
  
  // Diff
  lcd.setCursor(10,0);
  lcd.print(diff);
  lcd.print("    ");
  
}

void printMilli(unsigned long in2) {
  float in = (float) ((int)(in2/10))/100;
  if (in<10.0) {
    lcd.print(" ");
  }
  if (in<100.0) {
    lcd.print(" ");
  }
  lcd.print(in);
}
void printFloat(float in) {
  if (in<10.0) {
    lcd.print(" ");
  }
  if (in<100.0) {
    lcd.print(" ");
  }
  lcd.print(in);
}