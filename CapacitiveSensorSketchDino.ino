#include <CapacitiveSensor.h>

long minVal1;
long minVal2;
long maxVal1;
long maxVal2;
long readVal1;
long readVal2;
long midVal1;
long midVal2;
long lastTouch;
long touchElapsed;
bool touch;
bool buzz;

// for Gemma
 /*
int c1 = 0;
int c2 = 2;
int buzzPin = 1;
 */
//end Gemma

//for Arduino debugging
// /*
int ledPin = LED_BUILTIN;
int c1 = 16; //A2
int c2 = 18; //A4
int c3 = 4; //D4
int c4 = 6; //D6
int buzzPin = 9; //D9
// */
//end debug

CapacitiveSensor   cs1 = CapacitiveSensor(c1,c2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs2 = CapacitiveSensor(c3,c4);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()                    
{
  
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

  pinMode(buzzPin, OUTPUT);

  Serial.begin(9600);
  //for Arduino debugging
   /*
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); 
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH); 
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH); 
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
   */
  //end debug
  
}

void loop()                    
{
  long start = millis();
  readVal1 =  cs1.capacitiveSensor(30);
  readVal2 =  cs2.capacitiveSensor(30);
    
  midVal1 = setMinMax(readVal1, 1);
  midVal2 = setMinMax(readVal2, 2);

  //for Arduino debugging
  ///*
  Serial.print("readVal 1: ");
  Serial.print(readVal1);
  Serial.print("\t minVal 1: ");
  Serial.print(minVal1);
  Serial.print("\t maxVal 1: ");
  Serial.print(maxVal1);
  Serial.print("\t midVal 1: ");
  Serial.println(midVal1);
  Serial.print("readVal 2: ");
  Serial.print(readVal2);
  Serial.print("\t minVal 2: ");
  Serial.print(minVal2);
  Serial.print("\t maxVal 2: ");
  Serial.print(maxVal2);
  Serial.print("\t midVal 2: ");
  Serial.println(midVal2);
  //*/
  //end debug
  
  if (readVal1 > midVal1 || readVal2 > midVal2) {
    touch = true;
    lastTouch = millis();  
  } else {
    touch = false;
  }
  
  touchElapsed = millis() - lastTouch;

  //for Arduino debugging
  ///*
  //Serial.print("\t touchElapsed: ");
  //Serial.println(touchElapsed);
  //Serial.print("readVal 1: ");
  //Serial.print(readVal1);
  //Serial.print("\t readVal 2: ");
  //Serial.println(readVal2);
  digitalWrite(ledPin, touch);
  //*/
  //end debug
  
  if (touchElapsed > 3000) {
    buzz = false;
    digitalWrite(buzzPin, LOW);
  } else {
    buzz = true;
    digitalWrite(buzzPin, HIGH);
  }
    
  delay(100);                             // arbitrary delay to limit data to serial port 
}

long setMinMax(long readVal_, int which)
{
  float midValf_;
  long midVal_;

  if (which == 1) {
    if (readVal_ < minVal1) {
    minVal1 = readVal_; 
  }

  if (readVal_ > maxVal1) {
    maxVal1 = readVal_;
  }
  } else {
    if (readVal_ < minVal2) {
    minVal2 = readVal_; 
  }

  if (readVal_ > maxVal2) {
    maxVal2 = readVal_;
  }
  }
  
  
if (which == 1) {
  midValf_ = (minVal1 + maxVal1) / 2;
} else {
  midValf_ = (minVal2 + maxVal2) / 2;
}
  
  midVal_ = (long) midValf_;
  return midVal_;
}
