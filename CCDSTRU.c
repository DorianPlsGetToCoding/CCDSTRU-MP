#include <stdio.h>
#include "helperFunctions.h"

void
NextPlayerMove(){
	
}

int
main(){
	int grid[3][3] = { // this is the playing field that will be displayed for reference, this does not change
		{1,2,3},
		{4,5,6},
		{7,8,9},
	};
	/*
		NOTES:
		1. the found variable (boolean) is only used in the Replace function, no need to define it here
		2. the game ends if and only if:
			- Only 3 free tiles remain on the board
			- 20 or more turns have passed
			- if start is false and the board ONLY contains Player R/Player B tiles
	*/
	int good = 0; // boolean value, used in updating the board and game state
	int go = 1; // boolean value, determines player turn (Player R if true, and Player B if false)
	int start = 1; // boolean value, determines if the game has started and keeps it going
	int val = 0; // determines how many turns have passed with a maximum of 20 turns before the game automatically ends
	
	int R[9]; // an array that represents the tiles claimed by Player R
	int rSize = 0; // the current number of elements in R[]
	int B[9]; // an array that represents the tiles claimed by Player B
	int bSize = 0; // the current number of elements in B[]
	int S[9]; // an array that represents currently occupied tiles by all players
	int sSize = 0; // the current number of elements in S[]
	int T[9]; // an array that is responsible for handling cascading tilespread
	int tSize = 0; // the current number of elements in T[]
	
	int test = 1;
	int x=0,y=0;
	while(test){
		printf("x: ");
		do{
			scanf("%d",&x);
		}while(x<0||x>2);
		printf("y: ");
		do{
			scanf("%d",&y);
		}while(y<0||y>2);
		NextPlayerMove
	}
}