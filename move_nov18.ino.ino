#include <Servo.h>

Servo leftservo; 
Servo midservo; //create servo object for left wheel
Servo rightservo;


//create servo object for right wheel
//real speed for servos not moving is 94
//mux connects to left and right line sensors and left and right wall sensors
int A = 0;
int B = 0; 
int LF;
int RF;
int LB=A0; //Orange wire
int RB=A2; //Green wire
int M =A3;
int black= 750; //black sensor reading
int white= 750; // white sensor reading
int threshold = 790; //over 750 is black, under 750 is white
int threshold_lb = 780;
int threshold_rb = 950;
//int threshold_rf =
//int threshold_lf =
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
int iteration;
bool wallFront;
bool wallLeft;
bool wallRight;
byte currentWallValue;
int totalChannels = 8;
int addressA = 4;
int addressB = 10;
int leftBackline;
int rightBackline;
int leftIR;
int rightIR;
int count;
int front_middle;
int front_left;
int front_right;



void setup() {
  Serial.begin(9600);
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6);   //Connect right servo white wire to pin 6

  pinMode(addressA, OUTPUT);
  pinMode(addressB, OUTPUT);
 // pinMode(A0, OUTPUT);
 // pinMode(A1, INPUT);
  //pinMode(A2, INPUT);
  //pinMode(A3, INPUT);
  //pinMode(A5, INPUT);
  //pinMode(A4, INPUT);
 // pinMode(13, OUTPUT);
}

void loop() {
  //analogWrite(A4, 100);
  //Serial.println("Sensor Direct: " + String(analogRead(A4), DEC));
  move_one();

//leftservo.write(99);     
  //rightservo.write(84); 

  
  //turn_right();
    //leftservo.write(90);     
    //rightservo.write(90);
 //figure_eight();
  
}

/*void move_straight(){
  Serial.println(analogRead(LF));
  Serial.println(analogRead(M));
  Serial.println(analogRead(RF));
  
  
  if (analogRead(M) >= black && analogRead(LF) <= white && analogRead(RF) <= white){
 
  leftservo.write(180);     
  rightservo.write(0); //if its on a line, move forward
  } 
}*/


//move is the line follow
void move(){

  //Serial.println("print");
  

  
  //Serial.println("finished line sense");
 
  
    line_sense(); 
  
  //if rightfront and middle sensor is white and leftfront is black, move left, right wheel faster
  if(front_right<=790 /*&& analogRead(M)<=threshold) && analogRead(RF)>=threshold*/){
    leftservo.write(97);     
    rightservo.write(82);
    //Serial.println("third if");
    /*if((analogRead(M) <= threshold && analogRead(LF) <= threshold) && analogRead(RF) <= threshold) {
       leftservo.write(100);     
       rightservo.write(94);
       delay(250);*/
  }


  
  //if leftfront and middle sensor is white and rightfront is black, move right, left wheel faster
   else if(front_left<=750) /*&& analogRead(M)<=threshold) && analogRead(RF)>=threshold*/{
   leftservo.write(99);     
   rightservo.write(89);
   //Serial.println("second if");
  }



    while (analogRead(A3)>790) /*&& (analogRead(LF) >= white||analogRead(RF) >= white)*/{ //if at least two sensors are black, move forward
    leftservo.write(99);     
    rightservo.write(84);
    
    //Serial.println("first if");
    } 
  
  
  
  
  //Serial.println("finishes if");
  //Serial.println(" ");
  //intersection_action();
}


void figure_eight(){ 
 //if  ((M>= black && LB>=black && RB>=black)!=true){
  move_one();
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


  
/*void empty(){
  while (analogRead(LF)<=white&&analogRead(RF)<=white&&analogRead(M)<=white == true){
      move_straight(); //if all three sensors are white, move forward until line is found
  }
  
  leftservo.write(90);     
  rightservo.write(90); 
} */
  
  


void move_one(){ //move forward until it's at a cross section
    
  while((analogRead(LB) >= threshold_lb && analogRead(RB) >=threshold_rb)!=true){
    //Serial.println("middle line: " + String(analogRead(M), DEC));
    Serial.println("right back: "+ String(analogRead(RB), DEC));
    //Serial.println("left back: "+ String(analogRead(LB), DEC));
   
    move();
    
    //past= analogRead(A5);
    
    //current=analogRead(A5);
    
    
    } 

leftservo.write(90);      
rightservo.write(94);
delay(1000);
    
  /*if(current+15<past){
      leftservo.write(90);      
      rightservo.write(90);
      delay(10000);  
      } */ 
  }


 void turn_right(){
 leftservo.write(100);      
 rightservo.write(90);
 delay(500);
 //this is dependent on left front line
   // A = 1;
   // B = 1;
    //digitalWrite(addressA, A);
    //digitalWrite(addressB, B); 
 while(analogRead(A3)<=threshold){
   leftservo.write(100);     
   rightservo.write(94);
   }
  
  }
 
 void turn_left(){
  leftservo.write(90);     
  rightservo.write(85);
    delay(500);

   // A = 1;
   // B = 0;
   // digitalWrite(addressA, A);
   // digitalWrite(addressB, B);
   //this is dependent on right front line
  while(analogRead(A3)<=threshold){
    leftservo.write(90);     
    rightservo.write(85); }
  
  }

  void line_sense() {
    //Analog pin for front sensor
    front_middle = analogRead(M); //middle line sensor
    //Analog pin for left sensor
    A = 1;
    B = 1;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    delay(20);
    front_left = analogRead(A1);//left line sensor
    Serial.println("Left Front: " + String(front_left, DEC));
    //Analog pin for right sensor
    A = 0;
    B = 1;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    delay(20);
    front_right = analogRead(A1); //right line sensor
    Serial.println("Right Front: " + String(front_right, DEC));
    Serial.println("Sensor Direct: " + String(analogRead(A5), DEC));
    Serial.println(" ");
  }

  void wall_locate() {
    past_sum_front = current_sum_front;
    past_sum_left = current_sum_left;
    past_sum_right = current_sum_right;
    past_average_front = curr_average_front;
    past_average_left = curr_average_left;
    past_average_right = past_average_right;
    
  while(iteration < 7) {
    //Analog pin for front sensor
    //current_front = analogRead(A5);
    //Analog pin for left sensor
    A = 0;
    B = 0;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    current_left = analogRead(A1);
    //Analog pin for right sensor
    A = 0;
    B = 1;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    current_right = analogRead(A1);

    //Sums current values
    current_sum_front = current_sum_front + current_front;
    current_sum_left = current_sum_left + current_left;
    current_sum_right = current_sum_right + current_right;
    iteration++;
    delay(10);
  }

  if (iteration == 7)
  {
    curr_average_front = current_sum_front / double(iteration - 7);
    current_sum_front = 0;
    curr_average_left = current_sum_left / double(iteration - 7);
    current_sum_left = 0;
    curr_average_right = current_sum_right / double(iteration - 7);
    current_sum_right = 0;
    iteration = 0;
  }
   
  
  // robot will be continuously reading data but will only act upon the data received at each intersection
  //at intersection the wall action will be taken dependent on values collected at the intersection/prior to it with the summation of the values
  //
  //maximum of 280 milliseconds(14 iterations * 20 millisecond delay per iteration)
  //change the difference value of this addition to fix wall sensing

    if(curr_average_front+10<past_average_front)
    {
        wallFront = !wallFront;
    }  

    if(curr_average_left+50<past_average_left)
    {
        wallLeft = !wallLeft;
    }  

    if(curr_average_right+50<past_average_right)
    {
        wallRight = !wallRight;
    }  


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

void intersection_action() {
  wall_locate();
    
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
  
      currentWallValue= 0;
                         //no walls just goes into next set of moving forward to the next intersection
    
  }
