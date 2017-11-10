
## Milestone 3

### Objectives

The goal of this milestone is to implement algorithm to facilitate maze exploration on a 5x4 grid of this layout: 

![Figure 1. Maze grid](./images/IMG_5137.jpg)

Ultimately, we want working algorithm that facilitates maze exploration and indication that all that can be explored has been explored- in simulation and in real life. 


### Storing the Maze

Our first step was to decide on how to “translate” a maze into code. We followed the advice of [team alpha] (https://cei-lab.github.io/ECE3400-2017-teamAlpha/milestone3.html) and chose to save information about the maze in two 5x4 matrices. One 5x4 matrix contains data on whether or not each location on the maze has or has not been explored (1 being unexplored and 0 being explored). Each index of the matrix corresponds to the respective coordinate on the real maze grid. The other matrix contains information about the walls in the maze. Each corresponding index of the matrix contains a decimal number (0 to 15). Each decimal number can be converted to a 4-bit binary number, where each bit will represent the presence (or absence) of a wall. A 1 indicates the absence of a wall and a 0 represents the presence of a wall. Please see Figure I for how we specified directions (“north,” “south” etc.) The bits are organized as follows:
                                              [West] [East] [South] [North]
Ex. 0011 would mean there is a wall to the west and east of the robot. 


