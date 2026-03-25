#include <stdio.h>
#include "helperFunctions.h"

/*
	Description goes here
*/
void
Update(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	
}

/*
	This function handles the input given by a player and validates whether it is a valid input and functions accordingly
*/
void
NextPlayerMove(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int temp = grid[row][col]; // value of the tile in the grid using pos
	if(!(*over)&&(*go)&&Search(temp,B,(*bSize))==-1){ // Player R's initial turn, with additional check to make sure they don't place same tile as B
		printf("R's turn\n");
		int tempR = *rSize; // adds the tile to R
		add(temp,R,&tempR);
		*rSize = tempR;
		int tempS = *sSize; // adds the tile to S
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1; // good being true means that the other player can proceed with their turn
	}else if(!(*over)&&!(*go)&&Search(temp,R,(*rSize))==-1){ // Player B's initial turn, with additional check to make sure they don't place same tile as R
		printf("B's turn\n");
		int tempB = *bSize; // adds the tile to B
		add(temp,B,&tempB);
		*bSize = tempB;
		int tempS = *sSize; // adds the tile to S
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1;
	}
	int validR = (*go)&&(Search(temp,R,(*rSize))!=-1); // for this to be true, it must be player R's turn and the tile from the given position is theirs
	int validB = !(*go)&&(Search(temp,B,(*bSize))!=-1);
	if(!(*over)&&!(*start)&&(validR||validB)){ // this checks if the tile in the given position is actually owned by the player and if it is said player's turn
		// this is where update will go
		*good = 1;
	}
	if((*start)&&(*rSize)==1&&(*bSize)==1){ // this checks for if both players have already placed their initial tiles
		*start = 0; // this being false means that the game can actually start
	}
	if(!(*over)&&(*good)){ // if the game isn't over and inputs are valid (denoted by good being true), then the next player may take their turn
		*good = 0; // makes good false again for the next turn
		*go = !(*go); // switches the player turns
		*val = *val + 1; // increments the amount of (valid) turns that have been made
	}
}

/*
	Description goes here
	
*/
void
DisplayBoard(int R[],int B[],int grid[][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d ",grid[i][j]);
		}
		printf("\n");
	}
}


int
main(){
	/*
		NOTES:
		1. the found variable (boolean) is only used in the Replace function, no need to define it here
		2. the game ends if and only if:
			- Only 3 free tiles remain on the board
			- 20 or more turns have passed
			- if start is false and the board ONLY contains Player R/Player B tiles
	*/
	int good = 0; // boolean value, used in determining whether it is okay to proceed to the next player's turn and repeat a turn if criteria isn't met
	int go = 1; // boolean value, determines player turn (Player R if true, and Player B if false)
	int start = 1; // boolean value, true only at the start of the game and is false when both players place down their first tiles
	int val = 0; // determines how many turns have passed with a maximum of 20 turns before the game automatically ends
	int over = 0; // determines if the game is over or not
	
	int R[9]; // an array that represents the tiles claimed by Player R
	int rSize = 0; // the current number of elements in R[]
	int B[9]; // an array that represents the tiles claimed by Player B
	int bSize = 0; // the current number of elements in B[]
	int S[9]; // an array that represents currently occupied tiles by all players
	int sSize = 0; // the current number of elements in S[]
	int T[9]; // an array that is responsible for handling cascading tilespread
	int tSize = 0; // the current number of elements in T[]
	
	int grid[3][3] = { // the playing field, read only
		1,2,3,
		4,5,6,
		7,8,9,
	};
	
	int x=0,y=0;
	while(!over){
		printf("%d\n",go);
		do{
			printf("\nx: ");
			scanf("%d",&x);
		}while(x<0||x>2);
		do{
			printf("\ny: ");
			scanf("%d",&y);
		}while(y<0||y>2);
		NextPlayerMove(x,y,&good,&go,&start,&val,&over,R,B,S,T,&rSize,&bSize,&sSize,&tSize,grid);
		//DisplayBoard(R,B,grid);
	}
}