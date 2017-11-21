#include <Servo.h> 

Servo leftservo; 
Servo midservo; //create servo object for left wheel
Servo rightservo;


//create servo object for right wheel
//real speed for servos not moving is 94
//mux connects to left and right line sensors and left and right wall sensors
int A = 0;
int B = 0; 
int C=  0;
int LF;
int RF;
int LB=A0; //Orange wire
int RB=A2; //Green wire
int M =A3;
int black= 750; //black sensor reading
int white= 750; // white sensor reading
int threshold = 790; //over 750 is black, under 750 is white
int threshold_lb = 800;
int threshold_rb = 890;
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
//int current_front;
//int current_right;
//int current_left;
//int current_sum_front;
//int current_sum_right;
//int current_sum_left;
//int past_sum_front;
//int past_sum_right;
//int past_sum_left;
//double curr_average_front;
//double curr_average_right;
//double curr_average_left;
//double past_average_front;
//double past_average_right;
//double past_average_left;
int iteration;
int wallFront;
int wallLeft;
int wallRight;
byte currentWallValue;
int totalChannels = 8;
int addressA = 4;
int addressB = 10;
int addressC= 8;
int leftBackline;
int rightBackline;
int leftIR;
int rightIR;
int count;
int front_middle;
int front_left;
int front_right;


// DFS variables
int curr_x;
int curr_y;
int curr_direction;

int frontier[60];
int sp1=0;

int nodesSearched[60];
int sp2=0;

int path[120];
int sp3=0;

 int next_direction;// used in change_direction
int wall_map_real[][5] = { { 15, 15, 15, 15 }, { 15, 15, 15, 15}, { 15, 15, 15, 15 }, { 15, 15, 15, 15 }, { 15, 15, 15, 15 } };

int wall_map[][5] = { { 9, 1, 3, 5 }, { 8, 6, 13, 12}, { 12, 11, 6, 12 }, { 8, 3, 7, 14 }, { 10, 3, 3, 7 } };



void setup() {
  Serial.begin(9600);
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6);   //Connect right servo white wire to pin 6

curr_x=3;
 curr_y=4;
 sp1=0;
 sp2=0;
 sp3=0;
curr_direction=1;

  pinMode(addressA, OUTPUT);
  pinMode(addressB, OUTPUT);
  pinMode(addressC, OUTPUT);
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
//move_one();
//line_sense();
//leftservo.write(95);     
//rightservo.write(88); 
//
//move();
  //Serial.println("LB"+String(analogRead(LB)));
  //Serial.println("RB"+String(analogRead(RB)));
  //turn_right();
   // leftservo.write(87);     
    //rightservo.write(85);
 //figure_eight();


//wall_sense();
//analogRead(A5)
//Serial.println("front sensor "+ String(wallFront));
//Serial.println("right sensor "+ String(wallRight));
//Serial.println("left sensor  "+ String(wallLeft));
  


DFS();
 //move_to(4,2);
 //move_to(4,1);
 //move_to(4,0);
  //move_to(3,0);
   //move_to(2,0);
   //move_to(1,0);
    //move_to(0,0);
   // move_to(0,1);
    //move_to(0,2);
   // move_to(0,3);
   // move_to(0,2);
   // move_to(0,1);
    //move_to(1,1);
    // move_to(1,0);
    //move_to(2,0);

    // move_to(1,0);
 //move_to(3,1);
 //move_to(3,2);
 //move_to(3,3);
  
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
  if(front_right<=750 /*&& analogRead(M)<=threshold) && analogRead(RF)>=threshold*/){
    leftservo.write(93);     
    rightservo.write(84);
    //Serial.println("third if");
    /*if((analogRead(M) <= threshold && analogRead(LF) <= threshold) && analogRead(RF) <= threshold) {
       leftservo.write(100);     
       rightservo.write(94);
       delay(250);*/
  }


  
  //if leftfront and middle sensor is white and rightfront is black, move right, left wheel faster
   else if(front_left<=760) /*&& analogRead(M)<=threshold) && analogRead(RF)>=threshold*/{
   leftservo.write(95);     
   rightservo.write(92);
   //Serial.println("second if");
  }



    else if (analogRead(A3)>650) /*&& (analogRead(LF) >= white||analogRead(RF) >= white)*/{ //if at least two sensors are black, move forward
    leftservo.write(95);     
    rightservo.write(88);
    
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

  
leftservo.write(95);     
    rightservo.write(88);
    delay(100);
  while((((analogRead(LB)+analogRead(RB))/2) >=920)!=true){
    //Serial.println("middle line: " + String(analogRead(M), DEC));
    //Serial.println("right back: "+ String(analogRead(RB), DEC));
    //Serial.println("left back: "+ String(analogRead(LB), DEC));
    //Serial.println("LB"+String(analogRead(LB)));
   //Serial.println("RB"+String(analogRead(RB)));
    move();
    
    //past= analogRead(A5);
    
    //current=analogRead(A5);
    
    
    } 

leftservo.write(90);      
rightservo.write(94);
delay(100);
    
  /*if(current+15<past){
      leftservo.write(90);      
      rightservo.write(90);
      delay(10000);  
      } */ 
  }


 void turn_right(){
 leftservo.write(100);      
 rightservo.write(97);
 delay(200);
 //this is dependent on left front line
   // A = 1;
   // B = 1;
    //digitalWrite(addressA, A);
    //digitalWrite(addressB, B); 
 while(analogRead(A3)<=threshold){
   leftservo.write(99);     
   rightservo.write(97);
   }
  
  }
 
 void turn_left(){
  leftservo.write(87);     
  rightservo.write(86);
    delay(200);

   // A = 1;
   // B = 0;
   // digitalWrite(addressA, A);
   // digitalWrite(addressB, B);
   //this is dependent on right front line
  while(analogRead(A3)<=threshold){
    leftservo.write(87);     
    rightservo.write(85); }
  
  }

  void line_sense() {
    //Analog pin for front sensor
    front_middle = analogRead(M); //middle line sensor
    //Analog pin for left sensor
    A = 1;
    B = 1;
    C = 0;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(20);
    front_left = analogRead(A1);//left line sensor
    //Serial.println("Left Front: " + String(front_left, DEC));
    //Analog pin for right sensor
    A = 0;
    B = 1;
    C = 0;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(20);
    front_right = analogRead(A1); //right line sensor
    //Serial.println("Right Front: " + String(front_right, DEC));
    //Serial.println("Sensor Direct: " + String(analogRead(A5), DEC));
    Serial.println(" ");
  }

void wall_sense() {
    
    wallFront=analogRead(A5);

    delay(40);
    //Analog pin for left wall sensor
    C = 1;
    A = 0;
    B = 0;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(40);
    wallLeft = analogRead(A1);//left wall sensor
    //Serial.println("Left Wall: " + String(front_left, DEC));
    
    
    //Analog pin for right  wall sensor
    C = 1;
    A = 0;
    B = 1;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(40);
    wallRight = analogRead(A1); //right wall sensor
    //Serial.println("Right Wall: " + String(front_right, DEC));
    //Serial.println("Sensor Direct: " + String(analogRead(A5), DEC));
    Serial.println(" ");
  }









  
  void DFS(){

        // to stores path travelled 
    
    
     leftservo.write(90);      
     rightservo.write(94);
     delay(1000);
     writeWallInfo();
    
    frontier[sp1++]=curr_y;
    frontier[sp1++]=curr_x;
    
    nodesSearched[sp2++]=curr_y;
    nodesSearched[sp2++]=curr_x;
    path[sp3++]=curr_y;
    path[sp3++]=curr_x;
    
    Serial.println("starting x location:" + String(curr_x));
    Serial.println("starting y location:" + String(curr_y));
    Serial.println("...");
    
    // save current state to frontier
    //String wallinfo = Integer.toBinaryString(wall_map[curr_x][curr_y]);
    int wallinfo= wall_map_real[curr_y][curr_x];
   
    Serial.println("Reading in wall info as"+String(wallinfo));
    
    //System.out.println(wallinfo.length());

    // append adjacent nodes to frontier

    for (int i = 3; i >=0; i--) {

      Serial.println("first for loop");
      //Serial.println(bitRead(wallinfo,i));

      if (bitRead(wallinfo,i)==0) {
       
        delay(1000);
        if (i == 3) {
          Serial.println("west");
          int west[2] = { curr_y, curr_x - 1 };
         // Serial.println(String(west[0]));
          //Serial.println(String(west[1]));

          if (frontier_contains(west[0], west[1])!=true && nodesSearched_contains(west[0], west[1]) !=true) {
            frontier[sp1++]=west[0];
            frontier[sp1++]=west[1];
           // Serial.print("added something");
            
          }
          // append coordinates for the "west" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 2) {
          Serial.println("east");
          
          int east[2] = {curr_y, curr_x + 1 };

          if (frontier_contains(east[0], east[1])!=true && nodesSearched_contains(east[0], east[1]) !=true) {
            frontier[sp1++]=east[0];
             frontier[sp1++]=east[1];
            //Serial.print("added something");
            

          }

          // append coordinates for the "east" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 1) {
          Serial.println("south");
          
          int south[2] = { curr_y - 1, curr_x };
          if (frontier_contains(south[0], south[1])!=true && nodesSearched_contains(south[0], south[1]) !=true) {
            frontier[sp1++]=south[0];
            frontier[sp1++]=south[1];
           // Serial.print("added something");
            
          }

          // append coordinates for the "south" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 0) {
         Serial.println("north");
          
          int north[2] = { curr_y + 1, curr_x };

          if (frontier_contains(north[0], north[1])!=true && nodesSearched_contains(north[0], north[1]) !=true) {
            frontier[sp1++]=north[0];
            frontier[sp1++]=north[1];
            //Serial.print("added something");
            
          }

          // append coordinates for the "north" square onto frontier, if it is not already
          // in frontier or searched
        }
      }
    }

    //System.out.println("empty" + frontier.isEmpty());
    while (sp1>0) {
     Serial.println("while loop");

      Serial.println("frontier  "+ String(sp1));
      for(int a=0 ; a<sp1; a++){
     
        Serial.print(String(frontier[a]));
        }

         Serial.println("nodesSearched   "+String(sp1));
      for(int b=0 ; b<sp2; b++){
        Serial.print(String(nodesSearched[b]));
        }
      Serial.println("path   "+String(sp1));
      for(int c=0 ; c<sp3; c++){
        Serial.print(String(path[c]));
        Serial.print(String(sp3));
        }

        

      
     
       
      int temp_x = frontier[--sp1];
      int temp_y = frontier[--sp1];


      if((movePossible(curr_y, curr_x,temp_y,temp_x)!=true)){// if next one next location is not attainable. 
        path[--sp3];
        path[--sp3]; 
        
      Serial.println("TEST:"+String((movePossible(path[sp3-2], path[sp3-1],temp_y,temp_x)!=true)));
      while((movePossible(path[sp3-2], path[sp3-1],temp_y,temp_x)!=true)){
        
         int x=path[--sp3];
         int y=path[--sp3];
          move_to(y,x);
           
          // curr_x=path[--sp3]; // NEED TO PHYSICALLY MOVE ROBOT
           //curr_y=path[--sp3];//
           Serial.println("new x location:" + String(curr_x));
           Serial.println("new y location:" + String(curr_y));
           Serial.println("...");

        }
        // once more so you don't skip a spot
         int x=path[--sp3];
         int y=path[--sp3];
          move_to(y,x);


           
           //curr_x=path[--sp3]; // NEED TO PHYSICALLY MOVE ROBOT
           //curr_y=path[--sp3];//
           path[sp3++]=curr_y;
           path[sp3++]=curr_x;
           Serial.println("new x location:" + String(curr_x));
           Serial.println("new y location:" + String(curr_y));
           Serial.println("...");

      }

        move_to(temp_y,temp_x);
      //curr_x=temp_x; // NEED TO PHYSICALLY MOVE ROBOT
      //curr_y=temp_y;//
      
      path[sp3++]=temp_y;
      path[sp3++]=temp_x;
      nodesSearched[sp2++]=temp_y;
      nodesSearched[sp2++]=temp_x;
      

      Serial.println("x location:" + String(curr_x));
      Serial.println("y location:" + String(curr_y));

      
      //Serial.println("check:" + nodesSearched_contains(curr_x,curr_y));

      //Serial.println(String(wall_map[curr_y][curr_x]));
      

      //Serial.println("out of bounds error x check:" + robot.getX());
      //Serial.println("out of bounds error y check:" + robot.getY());

      wallinfo = wall_map_real[curr_y][curr_x];
      Serial.println("Reading in wall info as"+String(wallinfo));
     /* while (wallinfo.length() < 4) {
        wallinfo = "0" + wallinfo;
      }*/
      //System.out.println("wall info is: " + wallinfo);
      // append adjacent nodes to frontier

      for (int b = 3; b >=0; b--) {
        //Serial.println("embedded for loop" + " substring is:" + bitRead(wallinfo,b));
        
        if (bitRead(wallinfo,b) == 0) {

         
          
          if (b == 3) {
            int west[2] = { curr_y, curr_x - 1 };
            //System.out.println("check 1 :" + nodesSearched.contains(west));
            if (frontier_contains(west[0], west[1])!=true && nodesSearched_contains(west[0], west[1]) !=true) {
              frontier[sp1++]=west[0];
              frontier[sp1++]=west[1];
              //Serial.println("added west:" + String(west[0]) + String(west[1]));
            }
            // append coordinates for the "west" square onto frontier, if it is not already
            // in frontier or searched
          }

          else if (b == 2) {
            int east[2] = { curr_y, curr_x + 1 };

            if (frontier_contains(east[0], east[1])!=true && nodesSearched_contains(east[0], east[1]) !=true) {
              frontier[sp1++]=east[0];
               frontier[sp1++]=east[1];


               
              //System.out.println("added east" + east[0] + east[1]);
            }

            // append coordinates for the "east" square onto frontier, if it is not already
            // in frontier or searched
          }

          else if (b == 1) {

            int south[2] = {curr_y + 1, curr_x };
            if (frontier_contains(south[0], south[1])==false && nodesSearched_contains(south[0], south[1])==false) {
              frontier[sp1++]=south[0];
              frontier[sp1++]=south[1];
              //System.out.print("added south");
            }

            // append coordinates for the "south" square onto frontier, if it is not already
            // in frontier or searched
          }

          else if (b == 0) {
            

            int north[2] = {curr_y-1, curr_x };

            if (frontier_contains(north[0], north[1])==false && nodesSearched_contains(north[0], north[1]) ==false) {
              frontier[sp1++]=north[0];
              frontier[sp1++]=north[1];
              
              
             // Serial.println("added"+String(north[0])+ String(north[1]));
            }

            // append coordinates for the "north" square onto frontier, if it is not already
            // in frontier or searched

          }
        }
      }

    }

    Serial.print("all searched" );

    
    
    }


boolean frontier_contains( int y, int x){

     for(int i=0; i<sp1; i=i+2){

       if (frontier[i]==y && frontier[i+1]==x){

        //Serial.println("this is is found in frontier"+ String(y)+String(x));
        return true;
        
        }
     }
  return false;
  
  }



  boolean nodesSearched_contains( int y, int x){

     for(int i=0; i<sp2; i=i+2){

       if (nodesSearched[i]==y && nodesSearched[i+1]==x){
        // Serial.println("this is is found in nodesSearched"+ String(y)+String(x));
        return true;
        
        }
     }
  return false;
  
  }


  boolean movePossible(int curr_y, int curr_x, int pos_y, int pos_x){

   
    //int wall_map[][5] = { { 9, 1, 3, 5 }, { 8, 6, 13, 12}, { 12, 11, 6, 12 }, { 8, 3, 7, 14 }, { 10, 3, 3, 7 } };
    int wallinfo= wall_map_real[curr_y][curr_x];
    if(abs(curr_y-pos_y)>1 ||abs(curr_x-pos_x)>1|| (abs(curr_y-pos_y)== 1&& abs(curr_x-pos_x)==1)){return false;}


     else if (pos_y==curr_y - 1 && pos_x==curr_x&& bitRead(wallinfo,0) == 0) {return true;}
     else if (pos_y== curr_y + 1&& pos_x==curr_x && bitRead(wallinfo,1) == 0) {return true;}
     else if (pos_y==curr_y  &&pos_x==curr_x + 1&& bitRead(wallinfo,2) == 0) {return true;}
     else if (pos_y== curr_y && pos_x==curr_x - 1 && bitRead(wallinfo,3) == 0) {return true;}


     else return false;
    
    }

 void writeWallInfo(){
  
  // will be writing into wall_map_real for the actual wall map instead of the hardcoded one 
 
  //read in direction

  // WESN
     // W=+8
     // E=+4
     // S=+2
     // N=+1

  int front=0;
  int right=0;
  int left=0;
  wall_sense();
  
  Serial.println("front sensor "+ String(wallFront));
  Serial.println("right sensor   "+ String(wallRight));
  Serial.println("left sensor   "+ String(wallLeft));
  
  if (wallFront> 400){ front=1;}  /// THESE IF STATEMENTS NEED TO BE REWRITTEN TAKING INTO ACCOUNT PAST VALUES COMPARED TO CURRENT

  if (wallRight> 400){ right=1;}

  if (wallLeft> 150)  {left=1;}

  // if direction= 1 north , then front = north , right equals east, left equals west, south equals 0
  // if direction= 2 east , then front= east
  // if direction= 3 south  then front = south
  // if direction= 4 west , then front= west

  int walls=15;  
  
  
  if(curr_direction==1){   
    walls= (front*1)+(left*8)+(right*4)+2;
    }

  else if (curr_direction==2){ walls= (front*4)+(left*1)+(right*2)+8; }

  else if(curr_direction==3){ walls= (front*2)+(left*4)+(right*8)+1; }

  else if(curr_direction==4){ walls= (front*8)+(left*2)+(right*1)+4; }

  wall_map_real[curr_y][curr_x]=walls;
   Serial.println("the wall value at this location is :" + String(walls)); 
  
  }

  
  void move_to(int next_y, int next_x) {
    //looks at current location (curr_x and curr_y) and looks towards location that should be moved to (next_x and next_y) taking into account curr_direction
   
    //to figure out the next direction find the difference between the current y locations and x location
    
    
    if((next_y-curr_y) < 0)
      next_direction = 1;
    else if ((next_y-curr_y) > 0)
      next_direction = 3;
    else if ((next_x-curr_x) > 0)
      next_direction = 2;
    else if ((next_x-curr_x) < 0)
      next_direction = 4;

    change_direction();
    curr_direction=next_direction;
    
    move_one();
    
   

    curr_y=next_y;
    curr_x=next_x;

    writeWallInfo();

    
   }

  void change_direction() {
    int direction_difference = curr_direction - next_direction;
    
   if(direction_difference == -3){
     turn_left();
      
      }

    else if(direction_difference == -1) {
      turn_right();
    }

     else if(direction_difference == -2) {
      turn_right();
       turn_right();
    }
    
    else if(direction_difference == 3)
      turn_right();
    else if(direction_difference == 2) {
      turn_right();
      turn_right();
    }
   
    else if(direction_difference == 1) {
      turn_left();
    }
  }



  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  /*void wall_locate() {
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
    
  }*/
