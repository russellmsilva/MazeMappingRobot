int next_direction;
  void move_to() {
    //looks at current location (curr_x and curr_y) and looks towards location that should be moved to (next_x and next_y) taking into account curr_direction
    
    //to figure out the next direction find the difference between the current y locations and x location
    if((next_y-curr_y) < 0)
      next_direction = 1;
    else if ((next_y-curr_y) > 0)
      next_direction = 3;
    else if ((next_x-curr_x) > 0)
      next_direction = 2;
    else if ((next_x-curr_x) < 0)
      next_direction = 4;

    change_direction();
    move_one();
  }

  void change_direction() {
    int direction_difference = abs(curr_direction - next_direction);
    if(direction_difference == 3)
      turn_left();
    else if(direction_difference == 2) {
      turn_right();
      turn_right();
    }
    else if(direction_difference == 1) {
      turn_right();
    }
  }
