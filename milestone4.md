## Milestone 3

### Updates

#### Robot Update:
To improve the consistency of our robot, we worked to fix a majority of our wiring to make it significantly neater. We switched the breadboard to a (through hole) board with soldered on resistors for the pins which connected directly to the arduino and headers for the power and ground. We additionally switched the male to female wiring on all the line sensors from individual wires to a grouped male to female wire in a set of three for the power, ground and sensor output lines. These changes made our robot easier to debug and created less disconnection of wires.

#### Milestone 3 update:  
We switched to storing our locations for DFS in an int array instead of using the QList because we were worried about memory. Now, we only have to save an integer array and an additional integer which serves as our “pointer” in the array. Every time we “pop”  a location, we decrease the pointer value and every time we add to the “stack,” we write into the array and then increment the pointer. 

[Here](https://www.youtube.com/watch?v=uH1z1_MfQ2Y) is a video of our maze mapping.

### Objectives
For this milestone, we needed a system that could display the walls and treasure in a maze as the robot found them. We also needed our system to display a “done” signal on the screen, and play a “done” signal on the speaker when the maze was successfully mapped. 

### Treasure Detection and Display
To do the treasure detection, we simply have to integrate the code and hardware from lab 2 into the DFS code. We copied the circuit from Lab 2 three times over (1 for each treasure detector implemented - left, front, and right) and connected three LEDs to the remaining digital outputs of the Arduino. We will have to reorganize our current mux to wire the additional treasure detectors, since we ran out of analog pins. Below are our new select signals and their corresponding outputs:
