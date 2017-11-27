#include <Servo.h>

Servo myservo;    //create servo object

void setup() {
  Serial.begin(9600);
  myservo.attach(3);    //Connect servo's white wire to pin 2

}

void loop() {
  int val;
  val = analogRead(A0);  // Set A0 as an input
  Serial.println(val);   // Print val on serial input
  myservo.write(val);    // Speed can be determined b/w 0-89 clockwise or 91-180 counterclockwise

}
