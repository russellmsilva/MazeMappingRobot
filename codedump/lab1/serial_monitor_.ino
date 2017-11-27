void setup() {
  Serial.begin(9600);   // Set baudrate for serial monitor

}

void loop() {
  int val;
  val = analogRead(A0);   // A0 is an analog input
  Serial.println(val);    // Print val in serial monitor 
  delay(500);             // delay loop 500 ms

}
