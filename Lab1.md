# ECE3400 Fall 2017
## Lab 1: Microcontroller

### Objective

In this introductory lab, you will learn how to use the various functionalities of the Arduino Uno and the Arduino IDE. Your team will brainstorm and construct a simple functional Arduino program using multiple external components and the Arduino Uno. Once you have this basic understanding, you should put together your robot and have it perform a simple autonomous task. If you are already familiar with the Arduino, feel free to let those less familiar focus on the lab, and engage in some of the other tasks mentioned at the end of this page.

### I: Introduction to [Arduino](https://www.arduino.cc/en/Main/arduinoBoardUno/) 

Testing example code: 
This code is copied directly from File >> Examples >> 1.Basics  >> Blink. The Arduino board includes a built-in LED light that is wired to pin 13. In the code, setup() initializes pin 13 as an output, and in loop(), the pin is repeatedly turned on (HIGH) for a second and off (LOW) for a second, thereby creating the blink effect.

![Arduino Blink](./images/arduinoblink.png)

We were instructed to modify “Blink” code to work on an external LED light. We connected the LED to pin 11 and added a 300 ohm resistor in to prevent burning out the LED, and modified the code accordingly.

![Arduino LED](./images/arduinoled.png)

### II: The Serial Monitor and the Analog Pins

This section provided an introduction to the six available analog pins on the Arduino Uno. First, the variable resistance of a potentiometer had to be digitally outputted on the serial monitor provided by the Arduino IDE. Second, the integer resistance values from the potentiometer had to be mapped to the LED utilizing the analogwrite() function. Third, the oscilloscope was used to analyze the PWM signal given off from the Arduino. Figure (2) shows how the potentiometer was powered as well as where a pull down resistor was placed in relevance to the rest of the circuitry. Figure (3) displays how the pull down resistor was used in reference to the LED, and the connection through digital pin 11. This connection was used as a data output from the Arduino Uno to the LED.

![figure1](./images/IMG_4585.JPG) 
Figure (1): This picture displays the overall connection interface for this section of the lab. This includes the potentiometer, Arduino Uno, pull down resistors, and wires.

![figure2](./images/serialmonitorhook.png)
Figure (2): Here is a helpful diagram for serial monitor hookup.

![figure3](./images/connectingled.png)
Figure (3): This diagram goes with the code in a) of this section.

Analog Output

a) The following code was used to map the potentiometer resistance values onto the LED for variable brightness settings. This code was adopted from the previous task of displaying the potentiometer’s resistance values on the Serial Monitor. The analogRead function inputted data from the A0 pin on the potentiometer, and stored the data as integer values into the variable brightness. The information stored in the variable brightness was outputted to the LED through pin 11 (see Figure 2) utilizing the analogWrite function.

Insert image here

In addition, the integer resistance values were outputted onto the serial monitor using the Serial.println function. Another part of the code to note was that the Serial monitor was initialized by “Serial.begin(9600).” 

Insert image here

b) We analyzed the PWM signal outputted by the Arduino on an oscilloscope. By utilizing the oscilloscope’s functionality such as the trig level and scope, the frequency of the signal was found to be 50 Hz.  Video of the PWM signal width (determined by on-off times) changing when turning the knob on the potentiometer: 

[Video of pwm signal](https://www.youtube.com/watch?v=k9b29WAHjoY)

### III. Parallax Servos

Another aspect of this lab was to connect and control parallax servos using the arduinos. There was two stages to this process: an initial step of controlling the servo by writing specific values to it, and a second stage of modifying the servo based on the potentiometer.

a) The circuitry setup between the arduino and the parallax servo. The servo is receiving power from the arduino  because in this case the noise would not be significant enough to affect the servo. The servo is connected directly to the arduino with the black wire connecting to GND, the red wire connecting to 5V, and the white wire connecting to A3. The pin A3 is selected due to its PWM capability, which is used to control the servo. The video (cannot be added to google doc will be added to website) depicts the servo running. Additional tests run on the servo were running it at 90 and a large set of values between 0 and 180. The signal of A3 was measured with the oscilloscope and the result is depicted in Figure 4. To create this capability, we used the #servo library and the code titled pwm_servo.ino. The frequency of this was 50 Hz, with the minimum duty cycle of 7.5 and a maximum duty cycle of 12.

![Oscilloscope](./images/IMG_4587.JPG) 
Figure (5): PWM measured by oscilloscope when parallax is PWM controlled by hard coded values.

b) The second setup of the servo mimicked the first setup, however the PWM control was receiving data from the potentiometer rather than written values within the code. The setup was modified so that the potentiometer would output its values to A0, which would be written to ~3. Pin ~3 would be controlling the servo speed using PWM. The wiring follows figure 4. The code that controls this is pwm_servo.ino. The end result of the varying speeds dependent on the potentiometer is depicted in the following video. (video will be attached to site. I cannot put it on google doc but it is on the github).

Video here

Figure (6): Connection between the arduino and the servo

Figure (7): Image of wiring shown in figure 4.





