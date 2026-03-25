#include <stdio.h>
#include "helperFunctions.h"

/*
	Description goes here
*/
void
Update(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	
}

/*
	Description goes here
*/
void
NextPlayerMove(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int temp = grid[row][col]; // value of the tile in the grid
	if(!(*over)&&(*start)&&(*go)){ // Player R's turn
		int tempR = *rSize; // adds the tile to R
		add(temp,R,&tempR);
		*rSize = tempR;
		int tempS = *sSize; // adds the tile to S
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1; // sets good to true
	}else if(!(*over)&&(*start)&&!(*go)){ // Player B's turn
		int tempB = *bSize; // adds the tile to B
		add(temp,B,&tempB);
		*bSize = tempB;
		int tempS = *sSize; // adds the tile to S
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1; // sets good to true
	}
	printf("%d\n",*rSize);
	int inR = Search(temp,R,(*rSize))!=-1; // if true, that means it is an element of the corresponding array
	int inB = Search(temp,B,(*bSize))!=-1;
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
	int good = 0; // boolean value, used in updating the board and game state
	int go = 1; // boolean value, determines player turn (Player R if true, and Player B if false)
	int start = 1; // boolean value, determines if the game has started and keeps it going
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
		do{
			printf("\nx: ");
			scanf("%d",&x);
		}while(x<0||x>2);
		do{
			printf("\ny: ");
			scanf("%d",&y);
		}while(y<0||y>2);
		NextPlayerMove(x,y,&good,&go,&start,&val,&over,R,B,S,T,&rSize,&bSize,&sSize,&tSize,grid);
		DisplayBoard(R,B,grid);
	}
}