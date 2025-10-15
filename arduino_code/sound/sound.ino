int val = 0; 
int analogPin = A0; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(analogPin);  // read the input pin
  Serial.println(val);          // debug value
  
  delayMicroseconds(100); 
}
