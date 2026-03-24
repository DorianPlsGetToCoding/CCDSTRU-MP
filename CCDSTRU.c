#include <stdio.h>

void NextPlayerMove(int grid[][3]){
	printf("%d",grid[0][0]);
}

/*
	good doesn't do anything, just a flag that's there I guess
	if go is TRUE, it is R turn, if go is FALSE, it is B turn
	start basically means if the game has started already
	over controls if the game ends or not
	val determines the number of turns players may do
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
	NextPlayerMove(grid);
	
}