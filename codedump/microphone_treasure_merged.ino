#include <Servo.h> 
#include "nRF24L01.h"
#include "RF24.h"
//#include "printf.h"
#include <SoftwareSerial.h>

#define LOG_OUT 1 // use the log output function
#define FFT_N 128

#include <FFT.h> // include the library

RF24 radio(9,10);

const uint64_t pipes[2] = { 0x000000002ELL, 0x000000002FLL };

typedef enum { role_ping_out = 1, role_pong_back } role_e;

const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

role_e role = role_pong_back;

Servo leftservo; 
Servo midservo; //create servo object for left wheel
Servo rightservo;

//create servo object for right wheel
//real speed for servos not moving is 94
//mux connects to left and right line sensors and left and right wall sensors
int A = 0; // mux select values
int B = 0; 
int C = 0;

int LB=A0; // left back sensor pin, directly connected to arduino so don't need to save values 
int RB=A2; // right back sensor pin
int M =A3;

uint16_t front_middle;// LINE sensors, from line_sense()
uint16_t front_left;
uint16_t front_right;

uint16_t wallFront;
uint16_t wallLeft;
uint16_t wallRight;
byte loc = B00000000;
byte wallsarecool = B00000000;

uint8_t totalChannels = 8;
uint8_t addressA = 4; 
uint8_t addressB = 2;
uint8_t addressC = 5;
//int count;

//test for treasure;
//int s0 = 4;
//int s1 = 10;
//int s2 = 6;

// DFS variables
uint8_t curr_x;
uint8_t curr_y;
uint8_t curr_direction;
uint8_t temp_x;
uint8_t temp_y;
uint8_t  x; // throw away variables
uint8_t  y;
uint8_t wallinfo;
uint8_t frontier[60];
uint8_t sp1=0;

uint8_t nodesSearched[60];
uint8_t sp2=0;

uint8_t path[120];
uint8_t sp3=0;

uint8_t next_direction;// used in change_directio
uint8_t wall_map_real[][5] = { { 15, 15, 15, 15 }, { 15, 15, 15, 15}, { 15, 15, 15, 15 }, { 15, 15, 15, 15 }, { 15, 15, 15, 15 } };


//WRITE WALL INFO 

uint16_t front=0;
uint16_t right=0;
uint16_t left=0;
uint8_t walls=15;
uint8_t pushbutton = 0;

//Microphone FFT variables 
int start1 = 0;
int other=0;
long start_time;
//int maximum;
//int index;
boolean start;
int oldADCSRA;

  
void setup() {
  
  Serial.begin(115200);
  
  
  //DIDR0 = 0x01; // turn off the digital input for adc0
  pinMode(7, INPUT); 
  

  //////////////////////
  // Radio Stuff
  //////////////////////

  //printf_begin();
 // printf("\n\rRF24/examples/GettingStarted/\n\r");
 // printf("ROLE: %s\n\r",role_friendly_name[role]);
  //printf("*** PRESS 'T' to begin transmitting to the other node\n\r");
 
  
  
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  
  radio.setRetries(15,15);

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  // Start listening

  radio.startListening();

  radio.printDetails();
  
  //////////////////////////////
  //Servo Stuff
  //////////////////////////////
  
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
  
  treasure_setup();
  //delay(1000);
}

void loop() {

  //turn_right();

  //turn_left();
  
//move_one();
//delay(500);


//line_sense();

//leftservo.write(95);   // TESTING move right (not sharp turn)  
//rightservo.write(92);


//leftservo.write(93);  // TESTING move left  (not sharp turn)   
//rightservo.write(84);

// TESTING GO STRAIGHT
//leftservo.write(96);     
//rightservo.write(88);


//
//move();
//Serial.println("LB"+String(analogRead(LB)));
//Serial.println("RB"+String(analogRead(RB)));


//turn_right();
   // leftservo.write(87);     
    //rightservo.write(85);
 //figure_eight();



  
//delay(1000);
//delay(500);

/*role = role_ping_out;
radio.openWritingPipe(pipes[0]);
radio.openReadingPipe(1,pipes[1]);*/


//microphone();
//Serial.println("Treasure");
byte treasure = treasure_detect(0);
//DFS();  
}


//move is the line follow
void move(){
    line_sense(); 
  
  //if rightfront and middle sensor is white and leftfront is black, move left, right wheel faster
  if(front_right<=760){
    leftservo.write(93);     
    rightservo.write(84);
    //Serial.println("third if");
   
  }

  //if leftfront and middle sensor is white and rightfront is black, move right, left wheel faster
   else if(front_left<=760){
   leftservo.write(95);     
   rightservo.write(92);
   //Serial.println("second if");
  }


    else if (analogRead(A3)>650){ //if at least two sensors are black, move forward
    leftservo.write(96);     
    rightservo.write(88);
    
    //Serial.println("first if");
    } 
  

}


void move_one(){ //move forward until it's at a cross sectionn
  
leftservo.write(95);  // default move straight    
rightservo.write(88);
delay(100);
  while((((analogRead(LB)+analogRead(RB))/2) >=840)!=true){
    //Serial.println("middle line: " + String(analogRead(M), DEC));
    //Serial.println("right back: "+ String(analogRead(RB), DEC));
    //Serial.println("left back: "+ String(analogRead(LB), DEC));
     //Serial.println("LB"+String(analogRead(LB)));
     //Serial.println("RB"+String(analogRead(RB)));
    move();
    } 

leftservo.write(90);  // STOP     
rightservo.write(94);
delay(100);
     
  }


 void turn_right(){
 leftservo.write(96);      
 rightservo.write(99); // can try making higher for sharper turn
 delay(200);

 while(analogRead(A3)<=850){
   leftservo.write(97);     
   rightservo.write(98);
   }
  
  }
 
 void turn_left(){
  leftservo.write(86);  // can try making lower for tighter turn   
  rightservo.write(86);
    delay(200);
  while(analogRead(A3)<=850){
    leftservo.write(86);     
    rightservo.write(85); }
  
  }

  void line_sense() {
    //Analog pin for front sensor
    front_middle = analogRead(M); //middle line sensor
    //Serial.println("Middle Front: " + String(front_middle, DEC));
    
    //Analog pin for left sensor
    A = 1;
    B = 0;
    C = 0;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(20);
    front_left = analogRead(A4);//left line sensor
    //Serial.println("Left Front: " + String(front_left, DEC));
    //Analog pin for right sensor
    A = 0;
    B = 1;
    C = 0;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(20);
    front_right = analogRead(A4); //right line sensor
    //Serial.println("Right Front: " + String(front_right, DEC));
    //Serial.println("Sensor Direct: " + String(analogRead(A5), DEC));
   // Serial.println(" ");
  }

void wall_sense() {
    //Serial.println("GOING INTO FUNCTION");
    // Serial.println("Front Wall Direct: " + String(analogRead(A5), DEC));
    wallFront=analogRead(A5);
    delay(20);
    //Serial.println("Front Wall Direct: " + String(analogRead(A5), DEC));
    
    //Analog pin for left wall sensor
    C = 1;
    A = 0;
    B = 0;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(50);
    wallLeft = analogRead(A4);//left wall sensor
    //Serial.println("Left Wall Direct: " + String(analogRead(A4), DEC));
    
    //Analog pin for right  wall sensor
    C = 1;
    A = 0;
    B = 1;
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    delay(50);
    wallRight = analogRead(A4);
    //right wall sensor
   // Serial.println("Right Wall: " + String(front_right, DEC));
    //Serial.println("Right Sensor Direct: " + String(analogRead(A4), DEC));
    //Serial.println(" ");
  }

void transmitter(byte loc, byte loc2){
    // First, stop listening so we can talk.
    radio.stopListening();
    
    // Take the time, and send it.  This will block until complete
    //5 bits for current position: first 3 are y, next 2 are x
    //bits are arranged from most significant bit to least significant bit
    //4 bits for wall data: west, east, south, north respectivelly

    byte value = loc;
    byte value2 = loc2;
    //Serial.print("Inside Transmit");
    //Serial.print(bitRead(loc, 4));
    //Serial.print(bitRead(loc, 3));
    //Serial.print(bitRead(loc, 2));
    //Serial.print(bitRead(loc, 1));
    //Serial.println(bitRead(loc, 0));
    //Serial.print(bitRead(loc2, 3));
    //Serial.print(bitRead(loc2, 2));
    //Serial.print(bitRead(loc2, 1));
    //Serial.println(bitRead(loc2, 0));
    //printf("Now sending %lu...",value2);
    bool ok = radio.write( &value, sizeof(unsigned long) );
    bool ok2 = radio.write( &value2, sizeof(unsigned long) );
    
    //if (ok)
     // printf("ok...");
    //else
      //printf("failed.\n\r");

    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 800 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      //printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      byte got_time;
      radio.read( &got_time, sizeof(unsigned long) );

      // Spew it
      //printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }

    // Try again 1s later
}
  
  void DFS(){

    // to stores path travelled 
   //Serial.println("starting x location:" + String(curr_x));
   //Serial.println("starting y location:" + String(curr_y));
   //Serial.println("...");

   
    writeWallInfo();
    
    
    nodesSearched[sp2++]=curr_y;
    nodesSearched[sp2++]=curr_x;
    path[sp3++]=curr_y;
    path[sp3++]=curr_x;
    
   
    
    // save current state to frontier
    //String wallinfo = Integer.toBinaryString(wall_map[curr_x][curr_y]);
    wallinfo= wall_map_real[curr_y][curr_x];
   
    //Serial.println("Reading in wall info as"+String(wallinfo));
    

    // append adjacent nodes to frontier

    for (int i = 3; i >=0; i--) {

     // Serial.println("first for loop");
      //Serial.println(bitRead(wallinfo,i));

      if (bitRead(wallinfo,i)==0) {
       
        if (i == 3&&frontier_contains(curr_y, curr_x - 1)!=true && nodesSearched_contains(curr_y, curr_x - 1) !=true) {
          //Serial.println("west");

     
            frontier[sp1++]=curr_y;
            frontier[sp1++]=curr_x - 1;
           // Serial.print("added something");
            
        
          // append coordinates for the "west" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 2 &&frontier_contains(curr_y, curr_x + 1)!=true && nodesSearched_contains(curr_y, curr_x + 1) !=true) {
         // Serial.println("east");

         
            frontier[sp1++]=curr_y;
             frontier[sp1++]=curr_x + 1;
            //Serial.print("added something");
           

          // append coordinates for the "east" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 1&&frontier_contains(curr_y - 1, curr_x)!=true && nodesSearched_contains(curr_y - 1, curr_x) !=true) {
         // Serial.println("south");
          
            frontier[sp1++]=curr_y - 1;
            frontier[sp1++]=curr_x;
           // Serial.print("added something");
           

          // append coordinates for the "south" square onto frontier, if it is not already
          // in frontier or searched
        }

        else if (i == 0 &&frontier_contains(curr_y + 1, curr_x)!=true && nodesSearched_contains(curr_y + 1, curr_x) !=true) {
         //Serial.println("north");
          
         
          
            frontier[sp1++]=curr_y + 1;
            frontier[sp1++]=curr_x;
            //Serial.print("added something");
            
          

          // append coordinates for the "north" square onto frontier, if it is not already
          // in frontier or searched
        }
      }
    }

    //System.out.println("empty" + frontier.isEmpty());
    while (sp1>0) {
     /*Serial.println("while loop");
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
        }*/

        
       
     temp_x = frontier[--sp1];
     temp_y = frontier[--sp1];


      if((movePossible(curr_y, curr_x,temp_y,temp_x)!=true)){// if next one next location is not attainable. 
       sp3=sp3-2;
        
     // Serial.println("TEST:"+String((movePossible(path[sp3-2], path[sp3-1],temp_y,temp_x)!=true)));
      while((movePossible(path[sp3-2], path[sp3-1],temp_y,temp_x)!=true)){
        
         x=path[--sp3];
         y=path[--sp3];
         move_to(y,x);
           
          // curr_x=path[--sp3]; // NEED TO PHYSICALLY MOVE ROBOT
           //curr_y=path[--sp3];//
          // Serial.println("new x location:" + String(curr_x));
           //Serial.println("new y location:" + String(curr_y));
          // Serial.println("...");

        }
        // once more so you don't skip a spot
         x=path[--sp3];
         y=path[--sp3];
         move_to(y,x);


           
           //curr_x=path[--sp3]; // NEED TO PHYSICALLY MOVE ROBOT
           //curr_y=path[--sp3];//
           path[sp3++]=curr_y;
           path[sp3++]=curr_x;
           //Serial.println("new x location:" + String(curr_x));
          // Serial.println("new y location:" + String(curr_y));
          // Serial.println("...");

      }

      move_to(temp_y,temp_x);
      //curr_x=temp_x; // NEED TO PHYSICALLY MOVE ROBOT
      //curr_y=temp_y;//
      
      path[sp3++]=temp_y;
      path[sp3++]=temp_x;
      nodesSearched[sp2++]=temp_y;
      nodesSearched[sp2++]=temp_x;
      

     // Serial.println("x location:" + String(curr_x));
      //Serial.println("y location:" + String(curr_y));

      
     
      wallinfo = wall_map_real[curr_y][curr_x];

      
     // Serial.println("Reading in wall info as"+String(wallinfo));
      

      for (int b = 3; b >=0; b--) {
        //Serial.println("embedded for loop" + " substring is:" + bitRead(wallinfo,b));
        
        if (bitRead(wallinfo,b) == 0) {
          if (b == 3&&frontier_contains(curr_y, curr_x - 1)!=true && nodesSearched_contains(curr_y, curr_x - 1) !=true) {
            //System.out.println("check 1 :" + nodesSearched.contains(west));
              frontier[sp1++]=curr_y;
              frontier[sp1++]=curr_x - 1;
              //Serial.println("added west:" + String(west[0]) + String(west[1]));
          
            // append coordinates for the "west" square onto frontier, if it is not already
            // in frontier or searched
          }

          else if (b == 2&&frontier_contains(curr_y, curr_x + 1)!=true && nodesSearched_contains(curr_y, curr_x + 1) !=true) {
            
          
              frontier[sp1++]=curr_y;
               frontier[sp1++]=curr_x + 1;
              //System.out.println("added east" + east[0] + east[1]);
            

            // append coordinates for the "east" square onto frontier, if it is not already
            // in frontier or searched
          }

          else if (b == 1 && frontier_contains(curr_y + 1, curr_x )==false && nodesSearched_contains(curr_y + 1, curr_x )==false) {
         
              frontier[sp1++]=curr_y + 1;
              frontier[sp1++]=curr_x ;
              //System.out.print("added south");
            

            // append coordinates for the "south" square onto frontier, if it is not already
            // in frontier or searched
          }

          else if (b == 0 &&frontier_contains(curr_y-1, curr_x )==false && nodesSearched_contains(curr_y-1, curr_x ) ==false) {

              frontier[sp1++]=curr_y-1;
              frontier[sp1++]=curr_x ;
              
              
             // Serial.println("added"+String(north[0])+ String(north[1]));
            
            // append coordinates for the "north" square onto frontier, if it is not already
            // in frontier or searched

          }
        }
      }

    }

    //Serial.print("all searched" );  // NEED TO OUTPUT "ALL DONE SIGNAL"
    byte loc = B00000000;

    byte ybyte = curr_y;
    ybyte = ybyte << 2;
    byte xbyte = curr_x;
    loc = ybyte | xbyte;
    delay(50);
    
    wallsarecool = B00110000; //Sends impossible scenario: treasures with no walls
    transmitter(loc, wallsarecool);

    
    
    }


boolean frontier_contains(int y, int x){

     for(int i=0; i<sp1; i=i+2){

       if (frontier[i]==y && frontier[i+1]==x){

        //Serial.println("this is is found in frontier"+ String(y)+String(x));
        return true;
        
        }
     }
  return false;
  }



  boolean nodesSearched_contains(int y, int x){

     for(int i=0; i<sp2; i=i+2){

       if (nodesSearched[i]==y && nodesSearched[i+1]==x){
        // Serial.println("this is is found in nodesSearched"+ String(y)+String(x));
        return true;
        
        }
     }
  return false;
  
  }


  boolean movePossible(int curr_y, int curr_x, int pos_y, int pos_x){

    wallinfo= wall_map_real[curr_y][curr_x];
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

  front=0;
  right=0;
  left=0;
  wall_sense();
  
 // Serial.println("front sensor "+ String(wallFront));
 // Serial.println("right sensor   "+ String(wallRight));
  //Serial.println("left sensor   "+ String(wallLeft));
  //Serial.println("current direction"+ String(curr_direction));
  
  if (wallFront> 400){ front=1;}  

  if (wallRight> 380){ right=1;}

  if (wallLeft> 380)  {left=1;}

  // if direction= 1 north , then front = north , right equals east, left equals west, south equals 0
  // if direction= 2 east , then front= east
  // if direction= 3 south  then front = south
  // if direction= 4 west , then front= west

  walls=15;  
  
  if(curr_direction==1){   
    walls= (front*1)+(left*8)+(right*4); //+2
    }

  else if (curr_direction==2){walls= (front*4)+(left*1)+(right*2);}//+8 

  else if(curr_direction==3){ walls= (front*2)+(left*4)+(right*8);} //+1 

  else if(curr_direction==4){ walls= (front*8)+(left*2)+(right*1);} //+4

  wall_map_real[curr_y][curr_x]=walls;
  if(curr_y==4 && curr_x==3&& curr_direction==1){
  wall_map_real[curr_y][curr_x]= wall_map_real[curr_y][curr_x]+2;}
  //Serial.println("the wall value at this location is :" + String(wall_map_real[curr_y][curr_x]));

  /// SEND CURRENT LOCATION curr_y && curr_x


  
  /// SEND WALL INFORMATION walls
   byte loc = B00000000;
     byte wallsarecool = B00000000;

    byte ybyte = curr_y;
    ybyte = ybyte << 2;
    byte xbyte = curr_x;
    loc = ybyte | xbyte;
    delay(50);

    //Serial.print("Outside Transmit2");
    //Serial.print(bitRead(loc, 4));
    //Serial.print(bitRead(loc, 3));
    //Serial.print(bitRead(loc, 2));
    //Serial.print(bitRead(loc, 1));
    //Serial.println(bitRead(loc, 0));
    wallsarecool = wall_map_real[curr_y][curr_x];

    byte lefttreasure = treasure_detect(0);
    lefttreasure = lefttreasure << 4;
    wallsarecool = wallsarecool | lefttreasure;
    
    byte righttreasure = treasure_detect(1);
    righttreasure = righttreasure << 4;
    wallsarecool = wallsarecool | righttreasure;
    
    byte fronttreasure = treasure_detect(2);
    fronttreasure = fronttreasure << 4;
    wallsarecool = wallsarecool | fronttreasure;
    
    delay(200);
    transmitter(loc, wallsarecool);
    delay(200);

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
    
    else if(direction_difference == 3){
      turn_right();}

      
    else if(direction_difference == 2) {
      turn_right();
      turn_right();
    }
   
    else if(direction_difference == 1) {
      turn_left();
    }
  }

void microphone(){
    int maximum = 0;
    int index = 0;
    oldADCSRA = ADCSRA;
    ADCSRA = 0xe5;
    ADMUX = 0x40; // use adc0
    while(start != 1) { // reduces jitter
    start = digitalRead(7);
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 256 ; i += 2) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei();
    for (byte i = 0 ; i < FFT_N/2 ; i++) {

      if (fft_log_out[i] > maximum) {
        maximum = fft_log_out[i];
        index = i;
      }

      if (i == 63) {  //Checks what the maximum bin number was at the last bin  
                       //(FFT_N/2 - 1)
        Serial.println("start_time"+String(index));
        if (index == 3) {      //Increment start1
          start1++;
        }
        Serial.println("times " + String(start1));

        if (index != 3) {      //Increment start2
          other++;
        }
        
        if (start1 > 10 && other < 5)    //A balance of bin 4's and 5's indicate a 660 Hz Signal. Shine the LED.
        {
          Serial.println("working");
          start = 1;
        }

        if (index != 3 && other > 10) {   //Resets both incrementers
          start_time = 0;
          start1 = 0;
        }
        maximum = 0; //resets maximum checking at the end of the loop
        index = 0; //resets the index at which a maximum occurs at the end of 
                   //the loop
      }
    }
  }
  ADCSRA = oldADCSRA; 
  }

void treasure_setup(){
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  ADCSRA |= bit (ADPS0) | bit (ADPS2);
  ADMUX = 0x44; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  Serial.println("Treasure Setup");
}

byte treasure_detect(int test ){
  int maxi = 0;
  int idx = 0;
  byte i = 0;
  
  char TIMSK0_temp = TIMSK0;
  char ADCSRA_temp = ADCSRA;
  char ADMUX_temp = ADMUX;
  char DIDR0_temp = DIDR0;

  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  ADCSRA |= bit (ADPS0) | bit (ADPS2);
  ADMUX = 0x44; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  
  byte treasure = B00000000;

  if ( test == 0 ){ // 0
    digitalWrite(C, LOW);
    digitalWrite(B, LOW);
    digitalWrite(A, LOW);
    Serial.println("This is pin 0");
    delay(50000);
  }
  if ( test == 1 ){ // 3
    digitalWrite(C, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(A, HIGH);
    Serial.println("This is pin 1");
    delay(50000);
  }
  if ( test == 2 ){ // 5
    digitalWrite(C, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(A, HIGH);
    Serial.println("This is pin 2");
    delay(50000);
  }
  
  
  while(1) { // reduces jitter
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 256 ; i += 2) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei();
    
    for ( i = 0; i < FFT_N/2 ; i++) { 
      if (fft_log_out[i] > maxi ) {
        if (i > 5)
        {
          maxi = fft_log_out[i];
          Serial.print("This is i: ");
          Serial.println(String(i));
          Serial.println(String(maxi));
          idx = i;
        }
      }
     
      if (i == 63) {  //last bin
        //Serial.println(String(index)); // send out the data
        if (idx == 22 || idx == 23 || idx == 24) {      //7K
        //  start1++;
        //  if (start1 > 3) {
            treasure = B00000001;
            Serial.println("7k detected");
        //  }
        }

        //else {
        //  start1 = 0;
        //}

        if (idx == 39 || idx == 40 || idx == 41) {      //12K
          //start2++;
          //if (start2 > 3) {
            Serial.println("12k detected");
            treasure = B00000010;
          //}
        }

        //else {
        //  start2 = 0;
        //}

        if (idx == 55 || idx == 56 || idx == 57) {      //17K
          //start3++;
          //if (start3 >= 2) {
            Serial.println("17k detected");
            treasure = B00000011;        
          //}
        }

        //else {
        //  start3 = 0;
        //}
        
        maxi = 0; //resets maximum checking at the end of the loop
        idx = 0; 
        //Serial.println(index);
      }
    }
    
  TIMSK0 = TIMSK0_temp;
  ADCSRA = ADCSRA_temp;
  ADMUX = ADMUX_temp;
  DIDR0 = DIDR0_temp;
  return treasure;
  }
//}
}

