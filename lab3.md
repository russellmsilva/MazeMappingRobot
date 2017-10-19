## Lab 3

### Objective

### Acoustic Team

### Materials:
  Lab Speaker
  8-bit R2R DAC
  3.5 mm auxiliary jack  

### Square Wave
The initial part of the lab that we implemented was using the FPGA to generate a square wave. We selected a frequency of 440Hz for the square wave and connected this output to GPIO pin 0 because it was not previously in use. The following code was used to implement the square wave along with the addition of the counter and CLKDIVIDER_440 to the initial section of the code with parameter declarations. For the wiring, we used a breadboard and connected the GPIO pin to the two data pins on the phone jack socket. Additionally, we soldered the two side pins together to increase ease of use. The sound generated and the setup is shown in the [here]() The square wave generated is shown in the picture below.

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
![FPGA Setup](./images/audiosetup.jpg)
