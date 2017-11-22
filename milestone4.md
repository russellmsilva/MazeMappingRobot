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
![Table 1](./images/table.jpg)
We plan on connecting the microphone to the empty Y7 slot.

To incorporate the treasure detection in our main code, we will only need minor changes from the previous labs, since our Lab 2 code is already working. This will likely require two functions in our main code: treasure_detect and treasure_display. Treasure_detect will iterate through the analog pins 4-7 to detect if there was a treasure available and output 00 (no treasure), 01 (7 kHz), 10 (12 kHz), and 11 (17 kHz) depending on treasure availability and frequency. Treasure_display will light the appropriate LEDs as dictated by treasure_detect output .The fft bin number will also have to be changed, since it takes up a large amount of Arduino memory and we’re utilizing three treasure detectors instead of just one.  

### Wall Display on the FPGA

Our DFS code already handles the wall detection and converts the wall sensor data into something which can be sent to the FPGA in 4 bits where each bit represents the presence and absence of a wall. Additionally, at each “move_to” function, we are able to output the location of the robot in five bits.   

We improved our Lab 4 FPGA Display by adding walls to each grid space in the 5 x 4 grid array. We took in wall data from the receiving side of the radio transmission on the Arduino through four additional GPIO pins on the FPGA. 

We added memory array registers for the walls which were wall1, wall2, wall3, and wall4 for the top wall, bottom wall, left wall, and right wall respectively.
This was the beginning and end of our memory array initialization:
```
wall1[0][0] = 8'b000_000_00;
wall1[0][1] = 8'b000_000_00;
wall1[0][2] = 8'b000_000_00;
…
wall4[3][2] = 8'b000_000_00;
wall4[3][3] = 8'b000_000_00;
wall4[3][4] = 8'b000_000_00;
```
Based on the binary values received from the four additional GPIO pins, we set the walls at each grid space utilizing the memory array above. We change the color from our screen background (black: 8’b000_000_00) to white (8’b111_111_11). 
Wall Determination at a Grid Point:
```
if (val == 1'b1) begin
    if (wallFront) begin 
          	wall1[grid_coord_x][grid_coord_y] = 8'b111_111_11; 
    end
   	 
    if (wallBottom) begin
        	wall2[grid_coord_x][grid_coord_y] = 8'b111_111_11;
    end

    if (wallLeft) begin	 
          	wall3[grid_coord_x][grid_coord_y] = 8'b111_111_11;	 
    end
   	 
    if (wallRight) begin
        	wall4[grid_coord_x][grid_coord_y] = 8'b111_111_11;
    end
end
```
Once we set the walls at a certain grid space, we displayed the updated representation of the maze by iterating over memory array within the double for loop we implemented in Lab 3:
```
//Upper Walls
if(((j * PIXEL_WIDTH + 10'd0 < PIXEL_COORD_X) && (PIXEL_COORD_X < (j + 10'd1) * PIXEL_WIDTH - 10'd5)) && ((i * PIXEL_HEIGHT < PIXEL_COORD_Y) && (PIXEL_COORD_Y < (i + 10'd1) * PIXEL_HEIGHT - 10'd5))) begin
PIXEL_COLOR = wall1[j][i];
end
```
The video [here](https://www.youtube.com/watch?v=h1z6HrVaSnU) displays how our wall data is displayed on the screen.

### Done Signal

Our above implementation does not currently include a “done” message; however, we plan to include this into our final design by adding another connection between the receiving arduino and fpga that will send a high value when the dfs() reaches the “all nodes searched” state which is included in our original dfs() function. The DFS already displays “all nodes searched” on the serial monitor screen when the algorithm is complete.

While we did not have the chance to implement the done signal using FPGA, we have determined our plan for implementation. The done signal will be displayed once the DFS algorithm has finished. To indicate that this being done, the robot’s current location square will turn purple which will signify that it has finished its search. This signal will be sent from the arduino on the robot that is running the DFS.

### Done Sound
While we did not have the chance to implement the done sound, we have determined our plan for implementation. We will implement the same setup as used in lab 3, this includes an 8-bit DAC with the digital side wired to an FPGA and the analog side connected to the auxiliary jack. We will use the tri tone signal created in the lab to signify done. Please refer to [lab 3 on our website](https://kristinanemeth.github.io/group14/lab3.html) for more information on the setup and code. The FPGA in use will be the same FPGA that is receiving the transmitted information from the robot and is used to display the map. This sound will be triggered by the same signal which will display the done signal.

