#include <stdio.h>

void Expand(int x,int y,int grid[][3],int go,int R[],int B[],int S[],int T[]){
	// not sure how to add an array to an array, I'll stop here
}

void Update(int x,int y,int grid[][3],int go,int *good,int R[],int B[],int S[],int T[]){
	*good = 0;
	if(pos not in S){ // change
		// add pos to S
		*good = !*good;
	}
	if(*good&&pos in S&&pos not in T){ // change
		// add pos to T
		Expand(x,y,grid,go,R,B,S,T);
	}
}

void NextPlayerMove(int grid[][3],int x,int y,int *go,int *start,int *over,int *val,int *good,int R[],int B[],int S[],int T[]){
	if(!*over){ // if game is not over
		if(*start){ // if start is true
			if(*go){ // player R turn
				// add grid[x][y] to R
				// add grid[x][y] to S
				good = 1;
			}else{ // player B turn
				// add grid[x][y] to B
				// add grid[x][y] to S
				good = 1;
			}
			if((*go&&pos in R)||(!*go&&pos in B){ // replace this
				int tempGo = *go;
				int tempGood = *good;
				Update(x,y,grid,tempGo,&tempGood,R,B,S,T);
				*good = tempGood;
			}
		}
	}
	if(*start&&#elements in R is 1&&#elements in B is 1){ // this too
		*start = 0;
	}
	if(!*over&&good){
		*good = !*good;
		*go = !*go;
		*val = *val+1;
	}
}

/*
	TO-DO:
	try creating a manual check that makes the grid act like a strict grid
	e.g. grid[0][3] should theoretically be out of bounds, but it goes to the next row and returns 4
*/
int main(){
	int good,go,start,over,found,val;
	int grid[3][3] = { // this is the playing field that will be displayed for reference, this does not change
		{1,2,3},
		{4,5,6},
		{7,8,9},
	};
	int R[9]; // this represents the tiles claimed by R
	int B[9]; // this represents the tiles claimed by R
	int S[9]; // this represents occupied tiles
	int T[9]; // if a tile is placed here, it will undergo splitting into 3 directions
	
	// initializing values
	good = 0;
	go = 1;
	start = 1;
	found = 0;
	val = 0;
	over = 0;
	printf("%d\n",R[0]);
	NextPlayerMove(grid,0,0,&go,&start,&over,&val,&good,R,B,S,T);
	printf("%d\n",R[0]);
	
}