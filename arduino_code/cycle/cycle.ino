int LED_Y = 6;
int LED_G = 7;
const unsigned long timeout_1 = 1000;  // Timeout in milliseconds (2 seconds)
const unsigned long timeout_2 = 4000;
unsigned long lastReceivedTime = 0; 
void setup() {
  pinMode(LED_G, OUTPUT);  // LED pin 25
  pinMode(LED_Y, OUTPUT);  // LED pin 27
  Serial.begin(115200); // Match Python baudrate
  digitalWrite(LED_G, LOW); // Ensure LEDs are off at start
  digitalWrite(LED_Y, LOW);
  Serial.setTimeout(500); 
}

void loop() {
  // if (Serial.available() > 0) 
  // {
  //   String input = Serial.readString();
  //   if(input == "no signal")
  //   {
  //     Serial.println("no signal recevied");
  //   }
  //   else
  //   {
  //     int value = input.toInt(); 
  //     Serial.println(value);
  //   }
  // }
  if (Serial.available() > 0) {
    // Read incoming data
    String received = Serial.readString();
    
    // Turn on LED at pin 27 when data is received
    digitalWrite(LED_Y, HIGH);
    digitalWrite(LED_G, LOW);
    Serial.println("yes");
    // Update last received time
    lastReceivedTime = millis();
  }
  // Check if timeout period has elapsed
  Serial.println(lastReceivedTime);
  
  if (millis() - lastReceivedTime > timeout_1 && millis() - lastReceivedTime <= timeout_2 && lastReceivedTime != 0) {
    // Turn on LED at pin 23 and turn off LED at pin 27
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_Y, LOW);
  }
    if(millis() - lastReceivedTime > timeout_2 && lastReceivedTime != 0)
  {
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_Y, LOW);
  }

  // if (millis() - lastReceivedTime > timeout_1 && millis() - lastReceivedTime <= timeout_2) {
  //   digitalWrite(LED_G,HIGH);
  //   digitalWrite(LED_Y, LOW);
  // }
  // if(millis() - lastReceivedTime > timeout_2)
  // {
  //   digitalWrite(LED_G, LOW);
  //   digitalWrite(LED_Y, LOW);
  // }

}
