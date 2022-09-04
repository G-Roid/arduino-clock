#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int setPin = 6;
const int hoursPin = 8;
const int minutesPin = 9;
const int secondsPin = 10;

unsigned long myTime;
unsigned long previousTime;

long currentHours = 0;
long currentMinutes = 0;
long currentSeconds = 0;

int hoursSet = 0;
int minutesSet = 0;
int secondsSet = 0;

unsigned long baseSeconds = 0;
int set = 0;
int getBase = 0;


void setup() {
    Serial.begin(9600);  
    lcd.begin(16,2);
    pinMode(6, INPUT);
    pinMode(10, INPUT); 
  
    myTime = 0;
    previousTime = 0;
    
 while (set == 0) {  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ENTER TIME:");
    lcd.setCursor(0,1);
    lcd.print(String(currentHours) + ":" + String(currentMinutes) + ":" + String(currentSeconds));
    getBase = digitalRead(setPin);
    
    hoursSet = digitalRead(hoursPin);
    minutesSet = digitalRead(minutesPin);
    secondsSet = digitalRead(secondsPin);

    if(hoursSet == 1) {
      currentHours = (currentHours + 1) % 24;  
      delay(250);
    }


    if(minutesSet == 1) {
      currentMinutes = (currentMinutes + 1) % 60;  
      delay(250);
    }

    if(secondsSet == 1) {
      currentSeconds = (currentSeconds + 1) % 60;  
      delay(250);
    }
    
    if(getBase == 1) {
      Serial.println("LETS START");
//      startClock(); 
      baseSeconds = (currentHours * 3600) + (currentMinutes * 60) + currentSeconds;
      set = 0;
      break; 
    }
    delay(10);
  
  } 

}

void loop() {  
 
  myTime = millis()/1000 + baseSeconds;
//  Serial.println(myTime);
//  Serial.println(baseSeconds);
//  unsigned long rawTime = millis();
  
//  Serial.println(myTime);
  if(myTime != previousTime) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CURRENT TIME:");
    lcd.setCursor(0, 1);
   
    lcd.print(calculateTime(myTime));  
  }
  previousTime = myTime; 
}

String calculateTime(long seconds) {
   Serial.println(seconds);
   int hours = (seconds/3600) % 24;
   int minutes = (seconds % 3600) / 60;
   int sec = (seconds % 3600 % 60);
   Serial.print("hours:");
   Serial.print(hours);
   Serial.print(", ");

   Serial.print("minutes:");
   Serial.print(minutes);
   Serial.print(", ");

   Serial.print("seconds:");
   Serial.print(sec);
   Serial.println();
   
   

   return String(hours) + ":" + String(minutes) + ":" + String(sec);
}

void startClock() {
  return;  
}
