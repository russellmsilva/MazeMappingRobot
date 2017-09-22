## Lab 2

### Objective

The purpose of this lab was to successfully implement two sensors: one would detect a 660Hz whistle blow, and the other would capture inputs from an IR sensor blinking at 7kHz; both are important components to completing the second milestone of the robot. When successfully integrated onto the robot, the robot would be able to detect the whistle blow to signify the beginning of its maze mapping, and utilize the IR sensor inputs to detect treasures.

### Prelab
We started by adding the Open Music Lab FFT library to our Arduino IDE by putting the directory into the libraries folder of the IDE.

Before doing the FFT analysis on the signal on the Arduino Board, we analyzed the signal by using an oscilloscope. A video that displays the microphone’s output connected directly to the oscilloscope is displayed below

After analyzing the signal with the oscilloscope, we concluded the signal received was strong enough for FFT analysis without external amplification(because of what). Using the built fft_adc_serial code, we were able to see the FFT’s outputs from the default number of bins (FFT_N / 2 = 128). After terminating the program, we copied and pasted a single iteration of values into Excel for 660 Hz, 1320 Hz, and a control group frequency (no sound/room noise). Figure #1 displays what was graphed in Excel from these data points. We found that that the 660Hz peak was at the 4th/5th bin. As we increase the frequency of the tested sound waves, the bin number will also increase. In addition, the other test frequency of 1320Hz occured at about bin 9/10, which is double the bin number of 660Hz. This shows that our FFT analysis is working correctly. When working with the microphone, we used a web application that was recommended by the course staff: [here] (http://www.szynalski.com/tone-generator/)

### Acoustic

The acoustic team used a Microphone connected with an Arduino Board along with FFT analysis programming in order to detect a 660 Hz signal.

An Electret microphone with an attached amplifier was used in this section with the output connected to a pull up resistor with a value of 3 kOhms followed by a polarized capacitor with a value of 1 microFarad.  The capacitor then acts as a high pass filter preventing lower frequencies from passing through the circuit by blocking DC current when charging, and letting through AC current. This works because a capacitor has a varying impedances dependent on the frequency, so lower frequencies have a large resistance when trying to pass. The resistor in parallel is used in this case to create a path of lower resistance that the low frequency signals will take. 
This microphone is a passive sensor device that uses the energy provided by the beating of the membrane to power up an inductor. The amplifier included in the internal microphone circuitry was in the form of a MA4466 chip. 

Since the circuitry and amplifier were already integrated into the Electret Capsule microphone circuitry, we just had to connect the microphone’s three pins to the Arduino. The VCC, GND, and OUT pins on the microphone were connected to the +5 volts, GND, and A0 pins respectively on the Arduino. After we connected the microphone, fast fourier transforms were utilized, specifically in the modified fft_adc_serial program, to distinguish a 660 Hz signal from room noise along with 585 and 735 Hz signals. 

Based on our previous FFT_anaylsis (see Figure #1), we concluded that bins 4 and 5 represented maximum bin values in a 660 Hz signal. Therefore, we monitored the succession of bins 4 and 5 occurring as maximums in the program. From keeping track of the indices of the FFT maximums, we blinked an LED every time a balance of bins 4 and 5 were received from the FFT analysis.

A demo was performed in which a LED shined only when 660 Hz was detected. A video showing the effects on the LED with 585 Hz vs 660 Hz vs 735 Hz is shown below.

A demo was performed in which a LED shined only when 660 Hz was detected. A video showing the effects on the LED with 585 Hz vs 660 Hz vs 735 Hz is shown [here](https://www.youtube.com/watch?v=yrrrwozsazk).

Here is our modified fft_adc_serial (from the examples) code for 660Hz Detection:
```
    for (byte i = 0 ; i < FFT_N/2 ; i++) {
       //If the value of this bin number is greater than the current maximum,     
       //store the value in maximum and the bin number in index.
       if (fft_log_out[i] > maximum) {
        	maximum = fft_log_out[i];
        	index = i;
       }
    
       if (i == 127) {  //Checks what the maximum bin number was at the last bin  
                      	//(FFT_N/2 - 1)

       if (index == 4) {  	//Increment start1
               start1++;
            }

       if (index == 5) {  	//Increment start2
          start2++;}

       if (start1 == 20){  //Too many bin 4's indicate a 585 Hz Signal. Reset  
                       //Start2.
          start2 = 0;
       }
    
       if (start2 == 20) {	//Too many bin 5's indicate a 735 Hz Signal. Reset
                        //Start1.
          start1 = 0;     	 
        }
     	 
        if (start1 > 3 && start2 > 2)	//A balance of bin 4's and 5's indicate a 
                                    //660 Hz Signal. Shine the LED.
        {
            digitalWrite(10, HIGH);
            delay (1000);
            digitalWrite(10, LOW);
            }

        if (index != 4 && index != 5) {   //Resets both incrementers
          start_time = 0;
          start1 = 0;
          start2 = 0;
        }
        maximum = 0; //resets maximum checking at the end of the loop
        index = 0; //resets the index at which a maximum occurs at the end of
                   	//the loop
        }
        }
```

### Optical

Our IR system for light frequency detection consisted of an Arduino with a specialized program (see code below), a LM358 op amp for amplification, and our Phototransistor circuit.

Our op-amp was designed according to Figure #2. By selecting R1 to be a 20K resistor and R2 to be a 10K resistor we were able to achieve a voltage gain of 3x.
 
 ![Op Amp PinOut](./images/Op Amp.png)
 ![Inverting Amplifier Schematic](./images/inverting op amp.gif)
    
In order to test our IR system’s ability to detect the three different treasure frequencies, we connected three different leds to our Arduino. One LED shined when 7kHz was detected, another LED shined when 12 kHz was detected, and a third LED shined when 17 kHz was detected. Only one LED shined at a time and the detection range was about half of a foot.

A demo with the LED configuration described above is shown in the following video:

https://www.youtube.com/watch?v=DN9lzJqB21Q 

The light frequency outputted from the treasure was manipulated by hooking up the positive and negative headers below the potentiometer to an oscilloscope. The oscilloscope monitored the frequency and amplitude of the signal as we turned the potentiometer with a screw driver. This configuration is shown below in Figure 3.

Insert picture here

Below is our modified fft_adc_serial code for Treasure Signal Detection:
```
    for (byte i = 0 ; i < FFT_N/2 ; i++) {
    //If the value of this bin number is greater than the current maximum, store //the value in maximum and the bin number in index.
       if (fft_log_out[i] > maximum - 5) {
          if (i > 5)  //Bin numbers less than five tend to be maximums for  
                  //treasure signals. Therefore we cut them out for easier
                  //signal detection.
        	{
             maximum = fft_log_out[i];
        	   index = i;
          }
       }

       if (i == 127) { //Checks what the maximum bin number was at the last bin  
                   //(FFT_N/2 - 1)
         if (index == 45 || index == 46 || index == 47) {  	//7K
         	start1++;
         	//Shine LED from Digital Pin 8 if the bin numbers for 7K are       
            //detected for at least 5 iterations.
         	if (start1 > 5) {
           	   digitalWrite(8, HIGH);
        	   delay (1000);
        	   digitalWrite(8, LOW);
      	}
    	}

    	//If the maximum didn't occur at the above indices, reset the increment  
      //variable start1 to 0
    	else {
      	start1 = 0;
    	}

    	if (index == 79 || index == 80 || index == 81) {  	//12K
      	start2++;
      	//Shine LED from Digital Pin 9 if the bin numbers for 12K are 
            //detected for at least 5 iterations.
      	if (start2 > 5) {
        	   digitalWrite(9, HIGH);
        	   delay (1000);
        	   digitalWrite(9, LOW);
      	}
    	}

    	//If the maximum didn't occur at the above indices, reset the increment 
      //variable start2 to 0
    	else {
      	start2 = 0;
    	}

    	if (index == 113 || index == 114 || index == 115) {  	//17K
      	start3++;
      	//Shine LED from Digital Pin 10 if the bin numbers for 17K are 
            //detected for at least 5 iterations.
      	if (start3 > 5) {                                 	 
        	   digitalWrite(10, HIGH);
        	   delay (1000);
        	   digitalWrite(10, LOW);        	 
      	}
    	}
   	 
    	//If the maximum didn't occur at the above indices, reset the increment 
      //variable start3 to 0
    	else {
      	start3 = 0;
    	}
    	
      maximum = 0; //resets maximum checking at the end of the loop
    	index = 0; //resets the index at which a maximum occurs at the end of 
                 //the loop
       }
    }
```



