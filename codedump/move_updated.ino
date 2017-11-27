#include <Servo.h>

Servo leftservo; 
Servo midservo; //create servo object for left wheel
Servo rightservo;


//create servo object for right wheel
//real speed for servos not moving is 94

int LF=A0;
int LB=A1;
int RF=A2;
int RB=A3;
int M =A4;
int black= 750; //black sensor reading
int white= 750; // white sensor reading
int threshold = 840; //over 750 is black, under 750 is white
int threshold_l = 780;
int threshold_r = 950;
int backblack = 900;
int backwhite = 500;

void setup() {
  Serial.begin(9600);
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6); //Connect right servo white wire to pin 6

  
}

void loop() {

 
//move();
//Serial.println(analogRead(LB));
//Serial.println(analogRead(RB));

//move_straight();
//move_one();
figure_eight();  
 
}

void move_straight(){
  Serial.println(analogRead(LF));
  Serial.println(analogRead(M));
  Serial.println(analogRead(RF));
  
  
  if (analogRead(M) >= black && analogRead(LF) <= white && analogRead(RF) <= white){
 
  leftservo.write(180);     
  rightservo.write(0); //if its on a line, move forward
} 

/*else if(){
   leftservo.write(180);     
   rightservo.write(180);} 
else if(){
     leftservo.write(0);     
    rightservo.write(0);}*/
}

//move is the line follow
void move(){

  //Serial.println(analogRead(LF));
 // Serial.println(analogRead(M));
 //Serial.println(analogRead(LF));
  if (analogRead(M) >= threshold /*&& (analogRead(LF) >= white||analogRead(RF) >= white)*/){ //if at least two sensors are black, move forward
    leftservo.write(103);     
    rightservo.write(85); 
} 

//if leftfront and middle sensor is white and rightfront is black, move right, left wheel faster
else if((analogRead(LF)<=threshold) /*&& analogRead(M)<=threshold) && analogRead(RF)>=threshold*/){
   leftservo.write(98);     
   rightservo.write(94);
   /*if((analogRead(M) <= threshold && analogRead(LF) <= threshold) && analogRead(RF) <= threshold) {
      leftservo.write(94);     
      rightservo.write(88);
      delay(250);*/
}


//if rightfront and middle sensor is white and leftfront is black, move left, right wheel faster
else if(analogRead(RF)<=threshold /*&& analogRead(M)<=threshold) && analogRead(RF)>=threshold*/){
    leftservo.write(94);     
    rightservo.write(89);
    /*if((analogRead(M) <= threshold && analogRead(LF) <= threshold) && analogRead(RF) <= threshold) {
       leftservo.write(100);     
       rightservo.write(94);
       delay(250);*/
}
}

/*if((analogRead(M) <= threshold && analogRead(LF) <= threshold) && analogRead(RF) <= threshold) {
  leftservo.write(94);     
  rightservo.write(94); 
}*/



/*else if(analogRead(RF)<=white && analogRead(LF)<=white){
     leftservo.write(0);     
    rightservo.write(80);}*/

  
void empty(){
  while (analogRead(LF)<=white&&analogRead(RF)<=white&&analogRead(M)<=white == true){
      move_straight(); //if all three sensors are white, move forward until line is found
  }
  
  leftservo.write(90);     
  rightservo.write(90); 
}
  
  


void move_one(){ //move forward until it's at a cross section
  while((analogRead(LB) >= threshold_l &&analogRead(RB) >=threshold_r)!=true){
    move();
    Serial.print(analogRead(LB));
    Serial.println(analogRead(RB));}
  leftservo.write(94);     
  rightservo.write(94);   
  //delay(1000);// just for testing  
    // just for testing 
  }


void figure_eight(){ 
 //if  ((M>= black && LB>=black && RB>=black)!=true){
  move_one();
  Serial.println("turn right");
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
 //}
 
  }

 void turn_right(){
 leftservo.write(98);      
 rightservo.write(94);
 delay(500);
 while(analogRead(M)<=threshold){
   leftservo.write(98);     
   rightservo.write(94);
   }
  
  }
 
 void turn_left(){
  leftservo.write(94);     
  rightservo.write(89);
    delay(500);
  while(analogRead(M)<=threshold){
    leftservo.write(94);     
    rightservo.write(89); }
  
  }