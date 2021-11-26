#include <Servo.h>

const int TRIG_PIN  = 6;  
const int ECHO_PIN  = 7;  
const int SERVO_PIN = 9; 
const int DISTANCE_THRESHOLD = 100; // distance in centimeters

Servo servo; // servo object for controlling the garage door

float duration_us, distance_cm;

void setup() {
  Serial.begin (9600);       
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);  
  servo.attach(SERVO_PIN); 
  servo.write(0);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if(distance_cm < DISTANCE_THRESHOLD)
    servo.write(360); // rotate servo motor to 360 degree to open the door
  else
    servo.write(0);  // rotate servo motor to 0 degree to close the door

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}