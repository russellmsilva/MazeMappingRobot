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
int past;
int current;
bool intersection = false;
int past_front;
int past_right;
int past_left;
int current_front;
int current_right;
int current_left;
int current_sum_front;
int current_sum_right;
int current_sum_left;
int past_sum_front;
int past_sum_right;
int past_sum_left;
double curr_average_front;
double curr_average_right;
double curr_average_left;
double past_average_front;
double past_average_right;
double past_average_left;
int iterations;
bool wallFront;
bool wallLeft;
bool wallRight;
byte currentWallValue; 


void setup() {
  Serial.begin(9600);
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6); //Connect right servo white wire to pin 6

  
}

void loop() {

  move_one();
  intersection_action();
 
}

void move_straight(){
  Serial.println(analogRead(LF));
  Serial.println(analogRead(M));
  Serial.println(analogRead(RF));
  
  
  if (analogRead(M) >= black && analogRead(LF) <= white && analogRead(RF) <= white){
 
  leftservo.write(180);     
  rightservo.write(0); //if its on a line, move forward
  } 
}


//move is the line follow
void move(){

  Serial.println(analogRead(LF));
 Serial.println(analogRead(M));
 Serial.println(analogRead(LF));
  if (analogRead(M) >= threshold /*&& (analogRead(LF) >= white||analogRead(RF) >= white)*/){ //if at least two sensors are black, move forward
    leftservo.write(103);     
    rightservo.write(85); 
    
    } 

//if leftfront and middle sensor is white and rightfront is black, move right, left wheel faster
  else if((analogRead(LF)<=threshold) /*&& analogRead(M)<=threshold) && analogRead(RF)>=threshold*/){
   leftservo.write(98);     
   rightservo.write(94);
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


  
void empty(){
  while (analogRead(LF)<=white&&analogRead(RF)<=white&&analogRead(M)<=white == true){
      move_straight(); //if all three sensors are white, move forward until line is found
  }
  
  leftservo.write(90);     
  rightservo.write(90); 
}
  
  


void move_one(){ //move forward until it's at a cross section
  while((analogRead(LB) >= threshold_l &&analogRead(RB) >=threshold_r)!=true){
    wall_locate();
    move();
    past= analogRead(A5);
    delay(50);
    current=analogRead(A5);
    
    
    }
    
  if(current+15<past){
      leftservo.write(94);      
      rightservo.write(94);
      delay(10000);  
      }  
  }


 void turn_right(){
 leftservo.write(98);      
 rightservo.write(98);
 delay(500);
 while(analogRead(LF)<=threshold){
   leftservo.write(98);     
   rightservo.write(98);
   }
  
  }
 
 void turn_left(){
  leftservo.write(89);     
  rightservo.write(89);
    delay(500);
  while(analogRead(RF)<=threshold){
    leftservo.write(89);     
    rightservo.write(89); }
  
  }

  //run continously until it hits an intersection - put this into move one
  void wall_locate() {
  while((analogRead(LB) >= threshold_l &&analogRead(RB) >=threshold_r)!=true){
  move();

  currentWallValue= 0;
    
  if (iterations < 8) //why less than 8
  {
    //Analog pin for front long distance sensor
    past_front = analogRead(A5);
    //Analog pin for left long distance sensor
    past_left = analogRead(A6);
    //Analog pin for right distance sensor
    past_right = analogRead(A7);

    //Sums past values
    past_sum_front = past_sum_front + past_front;
    past_sum_left = past_sum_left + past_left;
    past_sum_right = past_sum_right + past_right;
    iterations++;
    delay(10);
  }

  else
  {
    //Analog pin for front sensor
    current_front = analogRead(A5);
    //Analog pin for left sensor
    current_left = analogRead(A6);
    //Analog pin for right sensor
    current_right = analogRead(A7);

    //Sums current values
    current_sum_front = current_sum_front + current_front;
    current_sum_left = current_sum_left + current_left;
    current_sum_right = current_sum_right + current_right;
    iterations++;
    delay(10);
  }

  if (iterations = 7)
  {
    past_average_front = past_sum_front / double(iterations);
    past_sum_front = 0;
    past_average_left = past_sum_left / double(iterations);
    past_sum_left = 0;
    past_average_right = past_sum_right / double(iterations);
    past_sum_right = 0;
  }

  if (iterations = 14)
  {
    curr_average_front = current_sum_front / double(iterations - 7);
    current_sum_front = 0;
    curr_average_left = current_sum_left / double(iterations - 7);
    current_sum_left = 0;
    curr_average_right = current_sum_right / double(iterations - 7);
    current_sum_right = 0;
    iterations = 0;
}
   
  
  // robot will be continuously reading data but will only act upon the data received at each intersection
  //at intersection the wall action will be taken dependent on values collected at the intersection/prior to it with the summation of the values
//
//maximum of 280 milliseconds(14 iterations * 20 millisecond delay per iteration)

    if(curr_average_front+4<past_average_front)
    {
        wallFront = true;
    }  

  else
    wallFront = false;

    if(curr_average_left+4<past_average_left)
    {
                        wallLeft = true;
    }  

  else
    wallLeft = false;

    if(curr_average_right+4<past_average_right)
    {
                  wallRight = true;
    }  

  else
    wallRight = false;


            //Convert bool values into currentWallValue (first bit: wallFront, second bit: wallLeft,                //third bit: wallRight)
  if (wallFront && wallLeft && wallRight)
    currentWallValue = B111;

  else if (wallFront && wallLeft && !wallRight)
    currentWallValue = B110;

  else if (wallFront && !wallLeft && wallRight)
    currentWallValue = B101;

  else if (wallFront && !wallLeft && !wallRight)
    currentWallValue = B100;

  else if (!wallFront && wallLeft && wallRight)
    currentWallValue = B011;

  else if (!wallFront && wallLeft && !wallRight)
    currentWallValue = B010;

  else if (!wallFront && !wallLeft && wallRight)
    currentWallValue = B001;

  else
    currentWallValue = B000;
  }
}

void intersection_action() {
            //UNAVOIDABLE ACTIONS (e.g. if there is a dead end you must turn around)
            //if there are wall on all sides, turn around
if (currentWallValue = B111)
      {
          turn_right();
          turn_right();
      }

                       //ACTIONS CAN BE MODIFIED (e.g. if there is only a wall in front you can move
    //left or right

                       //walls left and front of the robot: can turn right or turn around
else if (currentWallValue = B110)
      {
          turn_right();
      }

                        //walls right and front of the robot: can turn left or turn around
    else if (currentWallValue = B101)
      {
          turn_left();
      }

                       //wall in front of the robot
else if (currentWallValue = B100)
      {
          turn_right();
      }

                       //no walls just goes into next set of moving forward to the next intersection
  
  }


