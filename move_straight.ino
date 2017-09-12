#include <Servo.h>

Servo leftservo;   //create servo object for left wheel
Servo rightservo;
//create servo object for right wheel

int LF=A0;
int LB=A1;
int RF=A2;
int RB=A3;
int black= 1000; //black sensor reading
  int white= 850; // white sensor reading 
void setup() {
  Serial.begin(9600);
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6); //Connect right servo white wire to pin 6
  

  
}

void loop() {
//move_straight();
move_one();
//figure_eight();  
}

void move_straight(){
  if (analogRead(LF)==analogRead(RF)){
  leftservo.write(120);     
  rightservo.write(60); 
} 



}

void move_one(){
  while((LF>=black && LB>=black && RF>=black && RB>=black)!=true){
    move_straight();}
     leftservo.write(90);     
    rightservo.write(90); 
  }


void figure_eight(){
 if  ((LF>=black && LB>=black&& RF>=black && RB>=black)!=true){
  move_one();
  }

 else{
  turn_right();
  move_one();
  turn_right();
  move_one();
  turn_right();
  move_one();
  turn_right();
  move_one();
   turn_left();
  move_one();
  turn_left();
  move_one();
  turn_left();
  move_one();
  turn_left();
  move_one();
 }
 
  }

 void turn_right(){
  
 leftservo.write(180);      
 rightservo.write(180);
  delay(1);
  while((analogRead(LF)>=black && analogRead(RF)>=black)!=true){
   leftservo.write(180);     
   rightservo.write(180); }
  
  }
 
 void turn_left(){
  leftservo.write(0);     
  rightservo.write(0);
    delay(1);
  while((analogRead(LF)>=black && analogRead(RF)>=black)!=true){
    leftservo.write(0);     
    rightservo.write(0); }
  
  }
 
  

