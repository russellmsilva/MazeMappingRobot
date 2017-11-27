void wall_locate(){ //move forward until it's at a cross section
  while((analogRead(LB) >= threshold_l &&analogRead(RB) >=threshold_r)!=true){
	move();
    
	if (iterations < 8)
	{
  	//Analog pin for front sensor
  	past_front = analogRead(A5);
  	//Analog pin for left sensor
  	past_left = analogRead(A6);
  	//Analog pin for right sensor
  	past_right = analogRead(A7);

  	//Sums past values
  	past_sum_front = past_sum_front + past_front;
  	past_sum_left = past_sum_left + past_left;
  	past_sum_right = past_sum_right + past_right;
  	iterations++;
  	delay(10);
	}

	else
	{
  	//Analog pin for front sensor
  	current_front = analogRead(A5);
  	//Analog pin for left sensor
  	current_left = analogRead(A6);
  	//Analog pin for right sensor
  	current_right = analogRead(A7);

  	//Sums current values
  	current_sum_front = current_sum_front + current_front;
  	current_sum_left = current_sum_left + current_left;
  	current_sum_right = current_sum_right + current_right;
  	iterations++;
  	delay(10);
	}

	if (iterations = 7)
	{
  	past_average_front = past_sum_front / double(iterations);
  	past_sum_front = 0;
  	past_average_left = past_sum_left / double(iterations);
  	past_sum_left = 0;
  	past_average_right = past_sum_right / double(iterations);
  	past_sum_right = 0;
	}

	if (iterations = 14)
	{
  	curr_average_front = curr_sum_front / double(iterations - 7);
  	curr_sum_front = 0;
  	curr_average_left = curr_sum_left / double(iterations - 7);
  	curr_sum_left = 0;
  	curr_average_right = curr_sum_right / double(iterations - 7);
  	curr_sum_right = 0;
  	iterations = 0;
	 

  	if(curr_average_front+4<past_average_front)
  	{
    	//Wall in front
  	}  

  	if(curr_average_left+4<past_average_left)
  	{
    	//Wall left
  	}  

  	if(curr_average_right+4<past_average_right)
  	{
    	//Wall right
  	}  
	}
    
	}
    
	//zSerial.print(analogRead(LB));
	/*Serial.println(analogRead(RB));*/
  //leftservo.write(94);	 
  //rightservo.write(94);   
  //delay(1000);// just for testing  
	// just for testing
  }
