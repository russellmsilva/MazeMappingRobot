import java.util.LinkedList;

public class MazeNav {
	public static Arduino robot = new Arduino();

	public int[][] visited_map = { { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 0 } };

	public static int[][] wall_map =

			{ { 9, 1, 3, 5 }, { 8, 6, 13, 12}, { 12, 11, 6, 12 }, { 8, 3, 7, 14 }, { 10, 3, 3, 7 } };

	// Initialize current location maze array
	// 1 means unvisited
	// 0.5 means visited
	// 0 is the robot's current location

	public static void main(String[] args) {

		DFS();

	}

	public MazeNav() {

	}

	public void TurnRight() {
	}

	public void TurnLeft() {
	}

	public void Move() {

	}

	public int returnWall() {

		return 0;
	}

	public static boolean contains(LinkedList<int[]> a, int[] b) {

		boolean boo = false;

		for (int i = 0; i < a.size(); i++) {
			if (b[0] == a.get(i)[0] && b[1] == a.get(i)[1]) {
				return true;
			}
		}

		return boo;
	}

	public static void DFS() {

		LinkedList<int[]> nodesSearched = new LinkedList<int[]>();

		LinkedList<int[]> frontier = new LinkedList<int[]>();

		int[] temp = { robot.getY(), robot.getX() };
		frontier.addLast(temp);
		System.out.println("x location:" + robot.getX());
		System.out.println("y location:" + robot.getY());
		System.out.println("...");

		// save current state to frontier
		String wallinfo = Integer.toBinaryString(wall_map[robot.getY()][robot.getX()]);

		while (wallinfo.length() < 4) {
			wallinfo = "0" + wallinfo;
		}
		//System.out.println(wallinfo);
		//System.out.println(wallinfo.length());

		// append adjacent nodes to frontier

		for (int i = 0; i < wallinfo.length() - 1; i++) {

			//System.out.println("first for loop");
			//System.out.println(wallinfo.charAt(i));

			if (wallinfo.charAt(i) == '0') {
				//System.out.println("west");
				if (i == 0) {
					int[] west = { robot.getY(), robot.getX() - 1 };
					//System.out.println(west[0]);
					//System.out.println(west[1]);

					if (contains(frontier, west) != true && contains(nodesSearched, west) != true) {
						frontier.addLast(west);
						//System.out.print("added something");
					}
					// append coordinates for the "west" square onto frontier, if it is not already
					// in frontier or searched
				}

				else if (i == 1) {
					//System.out.println("east");
					int[] east = { robot.getY(), robot.getX() + 1 };

					if (contains(frontier, east) != true && contains(nodesSearched, east) != true) {
						frontier.addLast(east);
						//System.out.print("added something");

					}

					// append coordinates for the "east" square onto frontier, if it is not already
					// in frontier or searched
				}

				else if (i == 2) {
					//System.out.println("south");
					int[] south = { robot.getY() - 1, robot.getX() };
					if (contains(frontier, south) != true && contains(nodesSearched, south) != true) {
						frontier.addLast(south);
						//System.out.print("added something");
					}

					// append coordinates for the "south" square onto frontier, if it is not already
					// in frontier or searched
				}

				else if (i == 3) {
					//System.out.println("north");
					int[] north = { robot.getY() + 1, robot.getX() };

					if (contains(frontier, north) != true && contains(nodesSearched, north) != true) {
						frontier.addLast(north);
						//System.out.print("added something");
					}

					// append coordinates for the "north" square onto frontier, if it is not already
					// in frontier or searched
				}
			}
		}

		//System.out.println("empty" + frontier.isEmpty());
		while (frontier.isEmpty() != true) {
			//System.out.println("while loop");

			int[] current = frontier.removeLast();
			robot.setX(current[1]);
			robot.setY(current[0]);

			System.out.println("x location:" + robot.getX());
			System.out.println("y location:" + robot.getY());
			System.out.println("...");
			nodesSearched.addLast(current);
			//System.out.println("check:" + nodesSearched.contains(current));

			// System.out.println(wall_map[4][3]);
			// System.out.println(wall_map.length);

			//System.out.println("out of bounds error x check:" + robot.getX());
			//System.out.println("out of bounds error y check:" + robot.getY());

			wallinfo = Integer.toBinaryString(wall_map[robot.getY()][robot.getX()]);
			while (wallinfo.length() < 4) {
				wallinfo = "0" + wallinfo;
			}
			//System.out.println("wall info is: " + wallinfo);
			// append adjacent nodes to frontier

			for (int b = 0; b <= wallinfo.length() - 1; b++) {
				//System.out.println("embedded for loop" + " substring is:" + wallinfo.charAt(b));
				
				if (wallinfo.charAt(b) == '0') {

					if (b == 0) {
						int[] west = { robot.getY(), robot.getX() - 1 };
						//System.out.println("check 1 :" + nodesSearched.contains(west));
						if (contains(frontier, west) != true && contains(nodesSearched, west) != true) {
							frontier.addLast(west);
							//System.out.println("added west:" + west[0] + west[1]);
						}
						// append coordinates for the "west" square onto frontier, if it is not already
						// in frontier or searched
					}

					else if (b == 1) {
						int[] east = { robot.getY(), robot.getX() + 1 };

						if (contains(frontier, east) != true && contains(nodesSearched, east) != true) {
							frontier.addLast(east);
							//System.out.println("added east" + east[0] + east[1]);
						}

						// append coordinates for the "east" square onto frontier, if it is not already
						// in frontier or searched
					}

					else if (b == 2) {

						int[] south = { robot.getY() + 1, robot.getX() };
						if (contains(frontier, south) != true && contains(nodesSearched, south) != true) {
							frontier.addLast(south);
							//System.out.print("added south");
						}

						// append coordinates for the "south" square onto frontier, if it is not already
						// in frontier or searched
					}

					else if (b == 3) {

						int[] north = { robot.getY() - 1, robot.getX() };

						if (contains(frontier, north) != true && contains(nodesSearched, north) != true) {
							frontier.addLast(north);
							//System.out.print("added north");
						}

						// append coordinates for the "north" square onto frontier, if it is not already
						// in frontier or searched

					}
				}
			}

		}

		System.out.print("all searched" + nodesSearched.toString());

	}
}
		   
		   
		   
		   
		   
		   
	   
	   
   
  
    	
    	
    	
   
   
    	
    
    	
    	
   
    	
    	// move to top of frontier location
   
    	
    	// append adjacent nodes to frontier if not already in searched nodes 
    	// 

    		
    	
    		
    		
    	// once frontier is empty, return true or false if all grids were explored
    	
    	
    	
    	
    	///
    	
    	
    	
    	///
    	
    	
    	
    	
    	//  