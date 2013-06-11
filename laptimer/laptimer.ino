#include <Wire.h>
#include <LiquidCrystal.h>
#include <SD.h>

const int buttonPin = A0; 
const int buzzerPin = 13;
int test;
int laps = 0;
int buzzerLength = 500;
int mintime = 2000;
LiquidCrystal lcd( 8, 9, 3, 5, 6, 7 ); //4 och 3 byt plats pga sdkort
String extid = "12.34";

unsigned long best = 9999999;

unsigned long lasttime;
unsigned long readtime;
unsigned long time;
unsigned long last1;
float diff;
float timefloat;
File logfile;
char filename[] = "LOGGER00.CSV";

void setup()
{
    Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);  
  pinMode(buzzerPin, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print(".");
  
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(10, OUTPUT);
   
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  //filename number
  
  // create a new file
  
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      logfile.close();
      Serial.print(filename);
      Serial.println("logfile created");
      break;  // leave the loop!
    }
  }
  
  if (! logfile) {
    lcd.print("SD ERROR");
    delay(5000);
  }
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
      
      //Write to SD
      logfile = SD.open(filename, FILE_WRITE);
      logfile.println(time);
      logfile.close();
      Serial.print(time);
      Serial.println(" Written to SD");
      
      if (time < best) {
        best = time;
        digitalWrite(buzzerPin, HIGH);
        drawDisplay();
        delay(buzzerLength);
        digitalWrite(buzzerPin,LOW);
        delay(buzzerLength);
      }
      digitalWrite(buzzerPin, HIGH);
      drawDisplay();
      delay(buzzerLength);
      digitalWrite(buzzerPin,LOW);
      //writeTime();
      lasttime=readtime;
      drawDisplay();
      delay(mintime);
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
