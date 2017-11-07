
public class Arduino {

	private int current_xcoord; // current x coordinate of arduino
	
	private int current_ycoord;  // current y coordinate of arduino
	
	private int direction; // current direction  N=1,  S=2 E=4 W=8
	
		
	
public Arduino() {
	
	current_xcoord= 3;
	current_ycoord= 4;
	direction=1;   
		
}



public int getX() {
	return current_xcoord;
}


public int getY() {
	
	return current_ycoord;
	
}

public void setX(int a) {
	current_xcoord=a;
}


public void setY(int a) {
	
	current_ycoord=a;
	
}






public int[] getLocation() {

	int[] coord= {current_xcoord, current_ycoord};
	
return coord;
}



}



