//#include <QList.h>
//#include "QList.h"
//#include "QList.cpp"

#include <Servo.h>

Servo leftservo; 
Servo midservo; //create servo object for left wheel
Servo rightservo;


//create servo object for right wheel
//real speed for servos not moving is 94

int LF=A0;
int LB=A1;// going to change into mux

int RF=A2;
int RB=A3;// going to change into mux
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


/// DFS variables
int curr_x;
int curr_y;
int curr_direction;

int frontier[60];
int sp1=0;

int nodesSearched[60];
int sp2=0;

int path[120];
int sp3=0;
// push  : frontier[sp1++]=1;
//pop= froniter[--sp1]


//QList<String> myList;

//QList<int[]> nodesSearched; // stores locations visited 
//QList<int> frontier;
//QList<int> path;

void setup() {
  Serial.begin(9600);
  leftservo.attach(3);     //Connect left servo white wire to pin 3
  rightservo.attach(6); //Connect right servo white wire to pin 6
 curr_x=3;
 curr_y=4;
 sp1=0;
 sp2=0;
 sp3=0;
  
}

void loop() {

 DFS();
 delay(10000);
//move();
//Serial.println(analogRead(LB));
//Serial.println(analogRead(RB));

//move_straight();move_one();
//figure_eight();  
 
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
    past= analogRead(A5);
    delay(50);
    current=analogRead(A5);
    
    
    }
    
  if(current+15<past){
      leftservo.write(94);      
      rightservo.write(94);
      delay(10000);  
      }  
    
    //Serial.print(analogRead(LB));
    /*Serial.println(analogRead(RB));*/
  //leftservo.write(94);     
  //rightservo.write(94);   
  //delay(1000);// just for testing  
    // just for testing 
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


  void DFS(){

        // to stores path travelled 
    int wall_map[][5] = { { 9, 1, 3, 5 }, { 8, 6, 13, 12}, { 12, 11, 6, 12 }, { 8, 3, 7, 14 }, { 10, 3, 3, 7 } };
    
    
   frontier[sp1++]=curr_y;
    frontier[sp1++]=curr_x;
    
    
    nodesSearched[sp2++]=curr_y;
    nodesSearched[sp2++]=curr_x;
    path[sp3++]=curr_y;
    path[sp3++]=curr_x;
    
    Serial.println("x location:" + String(curr_x));
    Serial.println("y location:" + String(curr_y));
    Serial.println("...");
     delay(1000);
    // save current state to frontier
    //String wallinfo = Integer.toBinaryString(wall_map[curr_x][curr_y]);
    int wallinfo= wall_map[curr_y][curr_x];
    /*while (wallinfo.length() < 4) {
      wallinfo = "0" + wallinfo;
    }*/
    Serial.println(String(wallinfo));
    delay(1000);
    //System.out.println(wallinfo.length());

    // append adjacent nodes to frontier

    for (int i = 3; i >=0; i--) {

      Serial.println("first for loop");
      Serial.println(bitRead(wallinfo,i));

      if (bitRead(wallinfo,i)==0) {
       
        delay(1000);
        if (i == 3) {
          Serial.println("west");
          int west[2] = { curr_y, curr_x - 1 };
          Serial.println(String(west[0]));
          Serial.println(String(west[1]));

          if (frontier_contains(west[0], west[1])!=true && nodesSearched_contains(west[0], west[1]) !=true) {
            frontier[sp1++]=west[0];
            frontier[sp1++]=west[1];
            Serial.print("added something");
            delay(1000);
          }
          // append coordinates for the "west" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 2) {
          Serial.println("east");
          delay(1000);
          int east[2] = {curr_y, curr_x + 1 };

          if (frontier_contains(east[0], east[1])!=true && nodesSearched_contains(east[0], east[1]) !=true) {
            frontier[sp1++]=east[0];
             frontier[sp1++]=east[1];
            Serial.print("added something");
            delay(1000);

          }

          // append coordinates for the "east" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 1) {
          Serial.println("south");
          delay(1000);
          int south[2] = { curr_y - 1, curr_x };
          if (frontier_contains(south[0], south[1])!=true && nodesSearched_contains(south[0], south[1]) !=true) {
            frontier[sp1++]=south[0];
            frontier[sp1++]=south[1];
            Serial.print("added something");
            delay(1000);
          }

          // append coordinates for the "south" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 0) {
          Serial.println("north");
          delay(1000);
          int north[2] = { curr_y + 1, curr_x };

          if (frontier_contains(north[0], north[1])!=true && nodesSearched_contains(north[0], north[1]) !=true) {
            frontier[sp1++]=north[0];
            frontier[sp1++]=north[1];
            Serial.print("added something");
            delay(1000);
          }

          // append coordinates for the "north" square onto frontier, if it is not already
          // in frontier or searched
        }
      }
    }

    //System.out.println("empty" + frontier.isEmpty());
    while (sp1>0) {
      Serial.println("while loop");

      Serial.println("frontier"+ String(sp1));
      for(int a=0 ; a<60; a++){
     
        Serial.print(String(frontier[a]));
        }

         Serial.println("nodesSearched"+String(sp1));
      for(int b=0 ; b<60; b++){
        Serial.print(String(nodesSearched[b]));
        }
      Serial.println("path"+String(sp1));
      for(int c=0 ; c<120; c++){
        Serial.print(String(path[c]));
        }

        

      
      delay(1000);
       
      int temp_x = frontier[--sp1];
      int temp_y = frontier[--sp1];

       while(movePossible(temp_y,temp_x,path[sp3-2], path[sp3-1])!=true){
        
            /// NEED TO PHYSICALLY MOVE ROBOT
           
           curr_x=path[--sp3]; // NEED TO PHYSICALLY MOVE ROBOT
           curr_y=path[--sp3];
           
           Serial.println("x location:" + String(curr_x));
           Serial.println("y location:" + String(curr_y));
           Serial.println("...");
   
        }

      if( temp_y!=path[sp3-2] || temp_x!=path[sp3-1]){
        
        
           curr_y=path[sp3-2];// NEED TO PHYSICALLY MOVE ROBOT
           curr_x=path[sp3-1];
           Serial.println("x location:" + String(curr_x));
           Serial.println("y location:" + String(curr_y));
           Serial.println("..."); }

     
      curr_y=temp_y;
      curr_x=temp_x; /// NEED TO PHYSICALLY MOVE ROBOT
      

      

      Serial.println("x location:" + String(curr_x));
      Serial.println("y location:" + String(curr_y));
      Serial.println("...");

      path[sp3++]=temp_y;
      path[sp3++]=temp_x;
      nodesSearched[sp2++]=temp_y;
      nodesSearched[sp2++]=temp_x;
      //Serial.println("check:" + nodesSearched_contains(curr_x,curr_y));

      Serial.println(String(wall_map[curr_y][curr_x]));
      

      //Serial.println("out of bounds error x check:" + robot.getX());
      //Serial.println("out of bounds error y check:" + robot.getY());

      wallinfo = wall_map[curr_y][curr_x];
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
              Serial.println("added west:" + String(west[0]) + String(west[1]));
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
              
              
              Serial.println("added"+String(north[0])+ String(north[1]));
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

        Serial.println("this is is found in frontier"+ String(y)+String(x));
        return true;
        
        }
     }
  return false;
  
  }



  boolean nodesSearched_contains( int y, int x){

     for(int i=0; i<sp2; i=i+2){

       if (nodesSearched[i]==y && nodesSearched[i+1]==x){
         Serial.println("this is is found in nodesSearched"+ String(y)+String(x));
        return true;
        
        }
     }
  return false;
  
  }


  boolean movePossible(int curr_y, int curr_x, int pos_y, int pos_x){

   
    int wall_map[][5] = { { 9, 1, 3, 5 }, { 8, 6, 13, 12}, { 12, 11, 6, 12 }, { 8, 3, 7, 14 }, { 10, 3, 3, 7 } };
     int wallinfo= wall_map[curr_y][curr_x];
    if(abs(curr_y-pos_y)>1 ||abs(curr_x-pos_x)>1|| (abs(curr_y-pos_y)== 1&& abs(curr_x-pos_x)==1)){return false;}


else if (pos_y==curr_y - 1 && pos_x==curr_x&& bitRead(wallinfo,0) == 0) {return true;}
else if (pos_y== curr_y + 1&& pos_x==curr_x && bitRead(wallinfo,1) == 0) {return true;}
else if (pos_y==curr_y  &&pos_x==curr_x + 1&& bitRead(wallinfo,2) == 0) {return true;}
else if (pos_y== curr_y && pos_x==curr_x - 1 && bitRead(wallinfo,3) == 0) {return true;}


else return false;




    
    
    
    }



