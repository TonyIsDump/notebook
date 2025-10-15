#include <ESP32Servo.h>

Servo myservo;  // Create servo object
int pos = 90;   // Initial servo position (middle)

void setup() {
  Serial.begin(115200);        // Start serial communication
  myservo.attach(16);          // Attach servo to pin 13
  myservo.write(pos);         // Set initial position
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read(); // Read incoming serial data
    
    if (input == 'a') {
      pos += 10;                // Move clockwise
      if (pos > 180) pos = 180; // Limit to max angle
      myservo.write(pos);
    }
    else if (input == 'd') {
      pos -= 10;                // Move counterclockwise
      if (pos < 0) pos = 0;     // Limit to min angle
      myservo.write(pos);
    }
    
    delay(15);                  // Small delay for servo movement
  }
}