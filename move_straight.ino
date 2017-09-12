#include <Servo.h>

Servo leftservo;   //create servo object for left wheel
Servo rightservo;  //create servo object for right wheel

void setup() {
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6);    //Connect right servo white wire to pin 6
}

void loop() {
  leftservo.write(180);     
  rightservo.write(0);  

}
