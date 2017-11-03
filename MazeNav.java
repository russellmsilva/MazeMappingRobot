import java.util.LinkedList;

public class MazeNav{
	public static Arduino robot= new Arduino();
	

	
	public int[][] visited_map= {
               {1, 1, 1 ,1},
	           {1 ,1, 1 ,1},
	           {1 ,1 ,1 ,1},
	           {1, 1, 1, 1},
	           {1 ,1 ,1 ,0}
};

	public static int [][] wall_map=
			
		{
				{9 ,1, 3, 5},
				{ 8 ,6 , 13 ,2},
	    	        {12 , 11 , 6  ,12},
	    	        {8 ,3 , 7 , 14},
	    	        {10 , 3 ,3 , 7}};

			
			
	
	
	//Initialize current location maze array
	//1 means unvisited
     // 0.5 means visited
    //0 is the robot's current location

	
	
	public static void main(String[] args) {
		
		DFS();
		
		
	
		
		
	}
	
    public MazeNav() {
	

    }
    
    
    
    public void TurnRight() {}
    
    
    public void TurnLeft() {}
    
    
    public void Move() {
    	
    	
 
    }
    
    
    public int returnWall() {
    
    	return 0;
    }
    
    
   
    
    public static void DFS(){
    	
    	LinkedList<int[]> nodesSearched = new LinkedList<int[]>();
    	
    	LinkedList<int[]>frontier = new LinkedList<int[]>();
    	
   frontier.add(robot.getLocation());
       // save current state to frontier 
   String wallinfo=Integer.toBinaryString(wall_map[robot.getX()][robot.getY()]);
   
   
    	
    	// append adjacent nodes to frontier
   
   for(int i=0; i<wallinfo.length()-1; i++) {
	   
	   
			if (wallinfo.substring(i) == "0") {

				if (i == 0) {
					int[] west = { robot.getX() - 1, robot.getY() };

					if (frontier.contains(west) != true && nodesSearched.contains(west) != true) {
						frontier.add(west);
					}
					// append coordinates for the "west" square onto frontier, if it is not already
					// in frontier or searched
				}

				else if (i == 1) {
					int[] east = { robot.getX() + 1, robot.getY() };

					if (frontier.contains(east) != true && nodesSearched.contains(east) != true) {
						frontier.add(east);
					}

					// append coordinates for the "east" square onto frontier, if it is not already
					// in frontier or searched
				}

				else if (i == 2) {

					int[] south = { robot.getX(), robot.getY() - 1 };
					if (frontier.contains(south) != true && nodesSearched.contains(south) != true) {
						frontier.add(south);
					}

					// append coordinates for the "south" square onto frontier, if it is not already
					// in frontier or searched
				}

				else if (i == 3) {

					int[] north = { robot.getX(), robot.getY() + 1 };

					if (frontier.contains(north) != true && nodesSearched.contains(north) != true) {
						frontier.add(north);
					}

					// append coordinates for the "north" square onto frontier, if it is not already
					// in frontier or searched
				}
	   
				while (frontier.isEmpty() != true) {

					int[] current = frontier.removeLast();
					robot.setX(current[0]);
					robot.setY(current[1]);
					
					nodesSearched.add(current);

					wallinfo = Integer.toBinaryString(wall_map[robot.getX()][robot.getY()]);

					// append adjacent nodes to frontier

					for (int b = 0; b < wallinfo.length() - 1; b++) {

						if (wallinfo.substring(b) == "0") {

							if (b == 0) {
								int[] west = { robot.getX() - 1, robot.getY() };

								if (frontier.contains(west) != true && nodesSearched.contains(west) != true) {
									frontier.add(west);
								}
								// append coordinates for the "west" square onto frontier, if it is not already
								// in frontier or searched
							}

							else if (b == 1) {
								int[] east = { robot.getX() + 1, robot.getY() };

								if (frontier.contains(east) != true && nodesSearched.contains(east) != true) {
									frontier.add(east);
								}

								// append coordinates for the "east" square onto frontier, if it is not already
								// in frontier or searched
							}

							else if (b == 2) {

								int[] south = { robot.getX(), robot.getY() - 1 };
								if (frontier.contains(south) != true && nodesSearched.contains(south) != true) {
									frontier.add(south);
								}

								// append coordinates for the "south" square onto frontier, if it is not already
								// in frontier or searched
							}

							else if (b == 3) {

								int[] north = { robot.getX(), robot.getY() + 1 };

								if (frontier.contains(north) != true && nodesSearched.contains(north) != true) {
									frontier.add(north);
								}

								// append coordinates for the "north" square onto frontier, if it is not already
								// in frontier or searched
							}
						}
					}
					
					
				System.out.print(frontier.toString());	
					
					
					
					
				}
			}
		}
	}
}
		   
		   
		   
		   
		   
		   
	   
	   
   
  
    	
    	
    	
   
   
    	
    
    	
    	
   
    	
    	// move to top of frontier location
   
    	
    	// append adjacent nodes to frontier if not already in searched nodes 
    	// 

    		
    	
    		
    		
    	// once frontier is empty, return true or false if all grids were explored
    	
    	
    	
    	
    	///
    	
    	
    	
    	///
    	
    	
    	
    	
    	//  
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    
    
    
    
    
    
    
    
    
    
    

	
	
	


