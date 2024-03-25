/*
 * This sketch is used to test an SR04-M2 board
 *
 * According to documentation it uses the same interface as JSN-SR04T
 * but it needs inverted levels on Trigger Pin
 *
 */

// Ultrasonic Board is connected to Grove connector D4
const unsigned int TRIG_PIN=4; // RX
const unsigned int ECHO_PIN=5; // TX

// Use 9600 Baud for Serial output
const unsigned int BAUD_RATE=9600;

// JSN-SR04T SR04-M2 needs an inverted signal
#define TRIGGER_LOW HIGH
#define TRIGGER_HIGH LOW

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Use M5Stack Display with Adafruit Display library
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

void setup() {

  display.begin(0x3C, true);
  
  display.clearDisplay();
  display.display();

  display.setRotation(3);

  display.setTextSize(2);

  display.setTextColor(SH110X_WHITE);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(BAUD_RATE);

}

int left=0 ;

void loop() {
  digitalWrite(TRIG_PIN, TRIGGER_LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, TRIGGER_HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, TRIGGER_LOW);  

  const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
  int distance= duration/29/2;


  if(duration==0){
    Serial.println("Warning: no pulse from sensor");
  } else {
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
    left=distance ;
  }


  display.clearDisplay() ;
  display.setCursor(0,0);
  display.println("Open Pipe");
  display.println("Sensor");
  display.print("Left:  ") ;
  display.println(left) ;    
 
  display.display();

  delay(100) ;
}




