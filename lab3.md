## Lab 3

### Objective

### Acoustic Team

### Materials:
  Lab Speaker
  8-bit R2R DAC
  3.5 mm auxiliary jack  

### Square Wave
The initial part of the lab that we implemented was using the FPGA to generate a square wave. We selected a frequency of 440Hz for the square wave and connected this output to GPIO pin 0 because it was not previously in use. The following code was used to implement the square wave along with the addition of the counter and CLKDIVIDER_440 to the initial section of the code with parameter declarations. For the wiring, we used a breadboard and connected the GPIO pin to the two data pins on the phone jack socket. Additionally, we soldered the two side pins together to increase ease of use. The sound generated and the setup is shown in the [here](https://www.youtube.com/watch?v=MgeT1byl4v8&feature=youtu.be). The square wave generated is shown in the picture below.

```
always @ (posedge CLOCK_25) begin
		if(counter == 0) begin
		counter <= CLKDIVIDER_440 - 1;
		square_440 <= ~square_440;
		end
		else begin
			counter <= counter - 1;
			square_440 <= square_440;
			  end
	 End
```
![Square Wave](./images/squarewave.jpg)

### Sin Wave
The next phase we decided to implement was a single sine wave to generate a better clearer sounding tone. To implement this we needed to use an 8-bit R2R DAC because the output from the FPGA to the speaker is not longer one of two values as with the square wave. We wire the inputs from GPIO pins to pins 1-8 of the DAC and then connected pin 16 of the DAC to the speaker input. This wiring setup is depicted in the following picture.
![FPGA Setup](./images/audiosetup.JPG)

Then we wrote the following code to implement the sin wave.
```
reg [7:0] sine[0:255];
reg [10:0] counter1;
   
initial
     	Begin
sine[0] <= 8'd100;
sine[1] <= 8'd102;
	//remaining sin table values
	sine[255] <= 8'd98;

     end

     assign GPIO_1_D[8] = q[7];
     assign GPIO_1_D[10] = q[6];
     assign GPIO_1_D[12] = q[5];
     assign GPIO_1_D[14] = q[4];
     assign GPIO_1_D[16] = q[3];
     assign GPIO_1_D[18] = q[2];
     assign GPIO_1_D[20] = q[1];
     assign GPIO_1_D[22] = q[0];

always @ (posedge CLOCK_25) begin
             if (counter1 == 127 ) begin
                    counter1 <= 0;
                    q  <=  sine[ADDR];
                    if (ADDR == 255)
                            ADDR <= 0;
                    else
                            ADDR <= ADDR + 1;
             end
             else
                    counter1 <= counter1 + 1;    
end
```
The code was set up so that a counter would control the selection of the values in a sin table the output that corresponding value to create a sin graph. We used a counter that  would increment continuously with the clock frequency of 25MHz, and once the counter reached the value of 127 it would restart. This counter was used to determine when to increment the ADDR, specifically when the counter would reach the value of 127. We selected this value as when it included 0 there are 128 total values in order to produce a audible sine wave through the speakers. The incrementation of the counter was implemented with an if statement, and the incrementation of ADDR used an embedded if statement.  To implement the sin table for use we used direct digital synthesis. We decided to create a sin table outside of verilog for convenience. We implemented this in Matlab using the following code then copied and pasted into our project. We chose to create a sin table of one period with 256 plotted values because the number corresponds easily to the values of the 8-bit DAC. To ensure that our table was correct we graphed the values. The 8 separate GPIO pins were set to output corresponding to each input on the DAC. The GPIO pins were selected because they were previously not in use. See the video of the sin wave producing a sound[here](https://www.youtube.com/watch?v=-vzeRQowzgA).

```
total = 255;
for t = 0:total 
 	   value = round(100*sin((6.283*t)/total)+100);
  	  values(t) = value;
  	  fprintf('sine[%d] <= 8''d%d;\n',t, value)
end
```
![Sin Wave](./images/sinwave.jpg)

#Tri Tone
To implement the tri tone, we decided to use three tones given by sin waves with different frequencies to create this. To implement this we used a setup similar to the code for the sin wave and repeated a similar version of the sin code three times. To cycle through these tones we implemented a finite state machine. The transition between each of the states, we wait until one second passes dependent on the clock cycle to move onto the next state. The wiring setup between the FPGA, to the DAC, to the speaker is the same as the setup for the individual sin wave. Our finite state machine is shown below:

```
always @ (posedge CLOCK_25) begin
     next_state = 2'b00;
     case(state)
   	 TONE1: if (tone_length == ONE_SEC) begin
   				 next_state = TONE2;
   				 tone_length = 0;
   		 	end
   			  else begin
   				 next_state = TONE1;
   				 tone_length = tone_length + 1;
   			  end
   	 TONE2: if (tone_length == ONE_SEC) begin
   				 next_state = TONE3;
   				 tone_length = 0;
   			  end
   			  else begin
   				 next_state = TONE2;
   				 tone_length = tone_length + 1;
   			  end
   	 TONE3: if (tone_length == ONE_SEC) begin
   				 next_state = TONE1;
   				 tone_length = 0;
   			  end
   			  else begin
   				 next_state = TONE3;
   				 tone_length = tone_length + 1;
   			  end
   	 default: next_state = TONE1;
     endcase
end

always @ (posedge CLOCK_25) begin
    state <= next_state;
end

always @ (posedge CLOCK_25) begin
    
     ///// TONE 1 //////
     if (state == TONE1) begin
   	  if (counter1 == 127 ) begin
   		 counter1 <= 0;
   		 q  <=  sine[ADDR];
   		 if (ADDR == 255)
   			 ADDR <= 0;
   		 else
   			 ADDR <= ADDR + 1;
   	  end
   	  else
   		 counter1 <= counter1 + 1;
      end
      
      ///// TONE 2 ////
      if (state == TONE2) begin
   	  if (counter1 == 255 ) begin
   		 counter1 <= 0;
   		 q  <=  sine[ADDR];
   		 if (ADDR == 255)
   			 ADDR <= 0;
   		 else
   			 ADDR <= ADDR + 1;
   	  end
   	  else
   		 counter1 <= counter1 + 1;
      end         
      
      ///// TONE 3 /////
      if (state == TONE3) begin
   	  if (counter1 == 511 ) begin
   		 counter1 <= 0;
   		 q  <=  sine[ADDR];
   		 if (ADDR == 255)
   			 ADDR <= 0;
   		 else
   			 ADDR <= ADDR + 1;
   	  end
   	  else
   		 counter1 <= counter1 + 1;
      end    
      
end
```
The video of the implemented tri tone waves can be seen [here](https://www.youtube.com/watch?v=4RYInz8DY74). The video of the tri tone sound can be seen [here](https://www.youtube.com/watch?v=qpzVlRkj_Dc).
