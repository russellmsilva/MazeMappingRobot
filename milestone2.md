# Milestone 2

## Objective

One of the objectives of the milestone was to be able to detect and classify between different treasures (frequencies will be 7kHz, 12kHz, and 17kHz). In addition we had to implement wall detection to the robot.

## Treasure Detection
### Materials
- [Infrared Proximity Sensor Short Range - Sharp GP2Y0A41SK0F](http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a41sk_e.pdf)
- IR treasure
- Oscilliscope
- A line-following robot
- [TI LM358 Op-Amp](http://www.ti.com/lit/ds/symlink/lm158-n.pdf) 
- Phototransistor
- Some wires

### Methods
We used the oscilliscope connected to the outputs of the treasure (which is shown in the image below) in order to set the frequency at 7kHz, 12kHz, and 17kHz. We do this to ensure that the values measured by the phototransistor circuit will be as accurate as possible. 

![treasure](./images/treasure_pot.JPG) 

This video (as shown in Lab 2) reiterates our IR system’s ability to detect and distinguish tones of 7 kHz, 12 kHz, and 17 kHz: [here](https://www.youtube.com/watch?v=DN9lzJqB21Q)

In this demonstartion, we show our detection for each frequency with a 3 LED setup. The program on the arduino detects the bins that contain the peak of the FFT. Then we output to a certain pin to light the correct LED. We also have an inverting Op-Amp inorder to get a more accurate bin read on the FFT.

Red LED = 7kHz (bins 46 and 47)

Blue LED = 12 kHz (bin 80)

Green LED = 17kHz (bin 114)

![treasure FFT graph](./images/treasure_bin_detection.png) 

## Wall Detection

We attached a [distance sensor]( http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a41sk_e.pdf) to the front of our robot so that it could detect walls and stop accordingly.  We added to our previous move_one function (see Milestone 1) because we wanted our robot to not only detect a wall but also stop at the cross section in front of the wall. It was determined that the values outputted by the distance sensor to the Arduino would start decreasing as it approached the wall. By sampling the output of the sensor at every 50 ms, we were able to check if the robot was approaching (and a short distance from) the wall at every cross section. 

 
Below is our code: 

    void move_one(){   
    
        //move forward until it's at a cross section
        while((analogRead(LB) >= threshold_l &&analogRead(RB) >=threshold_r)!=true){
            move();//  line following function from milestone 1
            past= analogRead(A5); // read and save output 
            delay(50);
            current=analogRead(A5); // read and save output 50ms later
             }
             
       // once at intersection, check to see if robot is approaching
       if(current+15<past){ 
        // included a "buffer" of 15 so that minor disturbances would not cause robot to stop prematurely/unpredictabily
        leftservo.write(94);      
        rightservo.write(94);
        delay(10000);  
       }  

  }
    
        
See our robot detect and stop at walls [here](https://www.youtube.com/watch?v=PIjEVcrbemY) and [here](https://www.youtube.com/watch?v=ub0Cnr-BQ_A).







