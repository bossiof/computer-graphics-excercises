#include <algorithm>
void Assignment08::createMazeMesh(int row, int col, char **maze) {
	// The procedure gets in input the number of rows <row> of the maze, and the number of columns <col>
	// Element <maze[r][c]>, with 0 <= r <= row-1 and 0 <= c <= col-1 contains:
	//		Symbol ' ' if there is an empty space
	//		Symbol '#' if there is a wall
	//
	// Example: The following piece of code executes the instruction in the ... section
	//          if there is a wall in position r=5, c=7
	//
	// int r, c;
	// r = 5; c = 7;
	// if(maze[r][c] == '#') {
	//		...
	// }
	//
	// The example below creates a square, with four vertices and two triangles.
	// It must be deleted and replaced with your code creating the mesh of the maze.
	float n=0.0;
	for(int r=0;r<row;r++){
		for(int c=0;c<col;c++){
			if(maze[r][c]=='#'){
				//n=n+1.0;
				/*vPos.push_back(r);vPos.push_back(0.0); vPos.push_back(c);
				vPos.push_back(r+1);vPos.push_back(0.0); vPos.push_back(c);
				vPos.push_back(r);vPos.push_back(1.0); vPos.push_back(c);
				vPos.push_back(r+1);vPos.push_back(1.0); vPos.push_back(c);				

				vIdx.push_back(n); vIdx.push_back(n+1.0); vIdx.push_back(n+2.0);
				vIdx.push_back(n+1.0); vIdx.push_back(n+2.0); vIdx.push_back(n+3.0);

				vPos.push_back(r);vPos.push_back(0.0); vPos.push_back(c);
				vPos.push_back(r);vPos.push_back(0.0); vPos.push_back(c+1.0);
				vPos.push_back(r);vPos.push_back(1.0); vPos.push_back(c);
				vPos.push_back(r);vPos.push_back(1.0); vPos.push_back(c+1.0);

				n=n+3.0;

				vIdx.push_back(n); vIdx.push_back(n+1.0); vIdx.push_back(n+2.0);
				vIdx.push_back(n+1.0); vIdx.push_back(n+2.0); vIdx.push_back(n+3.0);
				*/


				vPos.push_back(r);vPos.push_back(0.0); vPos.push_back(c);
				vPos.push_back(r);vPos.push_back(0.0); vPos.push_back(c+1.0);
				vPos.push_back(r);vPos.push_back(1.0); vPos.push_back(c+1.0);
				vPos.push_back(r);vPos.push_back(1.0); vPos.push_back(c);
				vPos.push_back(r+1.0);vPos.push_back(0.0); vPos.push_back(c);
				vPos.push_back(r+1.0);vPos.push_back(0.0); vPos.push_back(c+1.0);
				vPos.push_back(r+1.0);vPos.push_back(1.0); vPos.push_back(c+1.0);
				vPos.push_back(r+1.0);vPos.push_back(1.0); vPos.push_back(c);

				vIdx.push_back(n); vIdx.push_back(n+1.0); vIdx.push_back(n+2.0);
				vIdx.push_back(n+3.0); vIdx.push_back(n+4.0); vIdx.push_back(n+5.0);
				vIdx.push_back(n+6.0); vIdx.push_back(n+7.0); vIdx.push_back(-1);
				vIdx.push_back(n); vIdx.push_back(n+2.0); vIdx.push_back(n+4.0);
				vIdx.push_back(n+6.0); vIdx.push_back(-1); vIdx.push_back(n+1.0);
				vIdx.push_back(n+3.0); vIdx.push_back(n+5.0); vIdx.push_back(n+7.0);

				n=n+7.0;
				
			}
			else if(maze[r][c]==' '){
				//n=n+1.0;
			}
		}


	}
	// Fill array vPos with the positions of the vertices of the mesh
	//vPos.push_back(0.0); vPos.push_back(0.0); vPos.push_back(0.0);	// vertex 0
	//vPos.push_back(1.0); vPos.push_back(0.0); vPos.push_back(0.0);	// vertex 1
	//vPos.push_back(0.0); vPos.push_back(1.0); vPos.push_back(0.0);	// vertex 2
	//vPos.push_back(1.0); vPos.push_back(1.0); vPos.push_back(0.0);	// vertex 3

	// Fill the array vIdx with the indices of the vertices of the triangles
	//vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	// First triangle
	//vIdx.push_back(1); vIdx.push_back(2); vIdx.push_back(3);	// Second triangle
	
}
