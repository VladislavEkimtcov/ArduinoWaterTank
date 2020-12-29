// physical settings
const int reservoirDepth = 14;
// include the library code: 
#include <LiquidCrystal.h>
// water sensor pin settigns
long int overflowAlarm = 0;  // holds the value
int respin = A5;
// ultrasonic sensor pin settings
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
int waterLevel;
// display pins
LiquidCrystal lcd(12, 13, 5, 4, 3, 2); 
// pump status var
bool pumpStatus = 0;

void setup() {
  //set sensor rates
  Serial.begin(9600);
  // alarm led
  pinMode(11, OUTPUT);
  // ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // set screen dimensions
  lcd.begin(16, 2); 
  // pump trigger
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); // okay i mean we can just read it, but to save up on the resistors we'll just control it with code
}

int to_surface() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  return distance;
}

void lock_system(){
  // announce lockdown
  lcd.clear();
  long int i = 0;
  while(true) {
      // disable pump
      togglePump(false);
      // turn on alarm led
      digitalWrite(11, HIGH);
      // print error and start timer
      lcd.setCursor(0, 0); 
      lcd.print("System locked!"); 
      lcd.setCursor(0, 1); 
      lcd.print(i); 
      delay(1000);
      i += 1;
    }  
}

void togglePump(bool on){
  if (on){
    digitalWrite(8, HIGH);
    pumpStatus = 1;
    Serial.println("pump on");
    }
  else {
    digitalWrite(8, LOW);
    pumpStatus = 0;
    Serial.println("pump off");
    }
  }

void debugRule(char * rule){
  Serial.println(String("Rule invoked: ") + String(rule));
  }


void loop(){
// manage pump
lcd.clear();
waterLevel = to_surface();

// check for system problems
overflowAlarm = analogRead(respin);
if (overflowAlarm >= 100 or waterLevel >= reservoirDepth) {
  lock_system();
}

lcd.setCursor(0, 1); 
lcd.print(String(reservoirDepth-waterLevel) + String(" cm"));
// water far and pump is off
if (waterLevel >= 12 and not pumpStatus) {
  // suggest adding water
  lcd.setCursor(0, 0); 
  lcd.print("Adding water...");  
  // engage pump
  togglePump(true);
  }
//water close and pump is on
else if (waterLevel <= 4 and pumpStatus) {
  lcd.setCursor(0, 0); 
  lcd.print("Done!");  
  togglePump(false);
  }
//water close and pump is off
else if (pumpStatus) {
  lcd.setCursor(0, 0); 
  lcd.print("Adding water...");  
  togglePump(true);
  }
else {
  //say water level sufficient
  lcd.setCursor(0, 0); 
  lcd.print("Water level:");  
  //disengage pump
  togglePump(false);
  }

Serial.println(waterLevel);
Serial.println("_______________");
delay(200);

}
