## Lab 2

### Objective

The purpose of this lab was to successfully implement two sensors: one would detect a 660Hz whistle blow, and the other would capture inputs from an IR sensor blinking at 7kHz; both are important components to completing the second milestone of the robot. When successfully integrated onto the robot, the robot would be able to detect the whistle blow to signify the beginning of its maze mapping, and utilize the IR sensor inputs to detect treasures.

### Prelab

### Acoustic

The acoustic team used a Microphone connected with an Arduino Board along with FFT analysis programming in order to detect a 660 Hz signal.

An Electret microphone with an attached amplifier was used in this section with the output connected to a pull up resistor with a value of 3 kOhms followed by a polarized capacitor with a value of 1 microFarad.  The capacitor then acts as a high pass filter preventing lower frequencies from passing through the circuit by blocking DC current when charging, and letting through AC current. This works because a capacitor has a varying impedances dependent on the frequency, so lower frequencies have a large resistance when trying to pass. The resistor in parallel is used in this case to create a path of lower resistance that the low frequency signals will take. 
This microphone is a passive sensor device that uses the energy provided by the beating of the membrane to power up an inductor. The amplifier included in the internal microphone circuitry was in the form of a MA4466 chip. 

Since the circuitry and amplifier were already integrated into the Electret Capsule microphone circuitry, we just had to connect the microphone’s three pins to the Arduino. The VCC, GND, and OUT pins on the microphone were connected to the +5 volts, GND, and A0 pins respectively on the Arduino. After we connected the microphone, fast fourier transforms were utilized, specifically in the modified fft_adc_serial program, to distinguish a 660 Hz signal from room noise along with 585 and 735 Hz signals. 

Based on our previous FFT_anaylsis with the oscilloscope, we concluded that bins 4 and 5 represented maximum bin values in a 660 Hz signal. Therefore, we monitored the succession of bins 4 and 5 occurring as maximums in the program. From keeping track of the indices of the FFT maximums, we blinked an LED every time a balance of bins 4 and 5 were received from the FFT analysis.

A demo was performed in which a LED shined only when 660 Hz was detected. A video showing the effects on the LED with 585 Hz vs 660 Hz vs 735 Hz is shown [here](https://www.youtube.com/watch?v=yrrrwozsazk).

Here is our modified fft_adc_serial (from the examples) code for 660Hz Detection:

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


### Optical


