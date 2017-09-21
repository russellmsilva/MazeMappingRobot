##Milestone 1

###Objective

The objective of the milestone was to have the robot follow a line of black tape and traverse a grid in the shape of a figure 8.

####Materials
- 5 QRE-1113 sensors
- 2 Servos 
- A lot of jumper wires

####Line Following

We connected 5 sensors to the robot: 3 in the front, 2 in the back. We tested each of them to determine a threshold value of 840, for which they would detect white or black. Detecting "white" meant that the analogRead values of the sensors would never exceed 840; detecting "black" meant that the sensors would always read above 840.

The three front sensors were meant to detect whether the robot was on a line. In our code, when the front middle sensor and one of the front side sensors is sensing the black line, the robot is considered on the line. When one of the side sensors and the front middle sensor are off the line, the robot is considered off the line and the robot will readjust accordingly. The two back side sensors are used to detect cross sections. When the front sensors are on a black line and the back side sensors both detect a black line, the robot is considered on a cross section. 
  
  void move(){
  
    if (analogRead(M) >= threshold ){
      leftservo.write(103);     
      rightservo.write(85); 
  } 
  //if leftfront and middle sensor is white and rightfront is black, move right, left wheel faster
    else if((analogRead(LF)<=threshold)){
      leftservo.write(98);     
      rightservo.write(94);
    }

  //if rightfront and middle sensor is white and leftfront is black, move left, right wheel faster
    else if(analogRead(RF)<=threshold){
      leftservo.write(94);     
      rightservo.write(89);
    }
  }
  
adadfadfa  
  


