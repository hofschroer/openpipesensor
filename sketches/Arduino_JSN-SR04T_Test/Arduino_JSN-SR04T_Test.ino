/*
 * This sketch is used to test a SR04-M2 board
 *
 * According to documentation it uses the same interface as JSN-SR04T
 * 
 */

// 
const unsigned int TRIG_PIN=4; // RX
const unsigned int ECHO_PIN=5; // TX


// Use 9600 Baud for Serial output
const unsigned int BAUD_RATE=9600;

// JSN-SR04T SR04-M2 needs an inverted signal
#define TRIGGER_LOW HIGH
#define TRIGGER_HIGH LOW

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
  delay(5000) ;
  Serial.println("starting") ;
}

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
  }
  delay(100);
}
