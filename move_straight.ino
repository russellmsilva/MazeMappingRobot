#include <Servo.h>

Servo leftservo; 
Servo midservo; //create servo object for left wheel
Servo rightservo;


//create servo object for right wheel

int LF=A0;
int LB=A1;
int RF=A2;
int RB=A3;
int M =A4;
int black= 750; //black sensor reading
int white= 700; // white sensor reading 
void setup() {
  Serial.begin(9600);
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6); //Connect right servo white wire to pin 6
  midservo.attach(5);  

  
}

void loop() {
 if (analogRead(M) <= white){
  empty();
 }
 else{
 move();

//move_straight();
//move_one();
//figure_eight();  
 }
}

void move_straight(){
  if (analogRead(M) >= black && analogRead(LF) <= white && analogRead(RF) <= white){
 
  leftservo.write(120);     
  rightservo.write(60); //if its on a line, move forward
} 

/*else if(){
   leftservo.write(180);     
   rightservo.write(180);} 

else if(){
     leftservo.write(0);     
    rightservo.write(0);}*/
}

void move(){

  Serial.println(analogRead(LF));
  Serial.println(analogRead(M));
  Serial.println(analogRead(RF));
  if (analogRead(LF)<= white&&analogRead(RF)<=white){ //if side sensors are white, move for
    leftservo.write(120);     
    rightservo.write(60); 
} 

else if(analogRead(LF)<=white){ //if leftfront sensor is white, move right
   leftservo.write(100);     
   rightservo.write(180);}

else if(analogRead(RF)<=white){ //if rightfront sensor is white, move left
     leftservo.write(0);     
    rightservo.write(80);}

/*else if(analogRead(RF)<=white && analogRead(LF)<=white){
     leftservo.write(0);     
    rightservo.write(80);}*/
}
  
void empty(){
  while (analogRead(LF)<=white&&analogRead(RF)<=white&&analogRead(M)<=white == true){
      move_straight(); //if all three sensors are white, move forward until line is found
  }
  
  leftservo.write(90);     
  rightservo.write(90); 
}
  
  


void move_one(){ //move forward until it's at a cross section
  while((M>=black && RF>=black && RB>=black)!=true){
    move_straight();}
    leftservo.write(90);     
    rightservo.write(90); 
  }


void figure_eight(){
 if  ((M>= white && LF<=white && LB<=white&& RF>=black && RB>=black)!=true){
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
 
  

