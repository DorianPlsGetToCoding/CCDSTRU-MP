/*
	Anika Lumbania
	Prinz Lim
	Magus Bautista
	
*/
#include <stdio.h>
#include "helperFunctions.h"

void Expand(int row,int col,int go,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]); // forward declaration of Expand()

/*
	Deletes a value from multiple arrays
	
	pos - the tile
	go - determines the player turns
	R[] - the array of tiles claimed by Player R
	B[] - the array of tiles claimed by Player B
	S[] - the array of tiles claimed by any player
	T[] - an array that holds tiles for the cascading spread effect
	*rSize - the number of elements in R[]
	*bSize - the number of elements in B[]
	*sSize - the number of elements in S[]
	*tSize - the number of elements in T[]
	grid[][3] - the board
*/
void
Remove(int pos,int go,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize){
	if(go){ // if it is Player R's turn, remove pos from R[]
		int tempR = *rSize;
		del(pos,R,&tempR);
		*rSize = tempR;
	}else{ // if it is Player B's turn, remove pos from B[]
		int tempB = *bSize;
		del(pos,B,&tempB);
		*bSize = tempB;
	}
	int tempS = *sSize; // remove pos from S[]
	del(pos,S,&tempS);
	*sSize = tempS;
	
	int tempT = *tSize; // remove pos from T[]
	del(pos,T,&tempT);
	*tSize = tempT;
}

/*
	This function replaces unclaimed tiles with claimed tiles or spreads tiles if the touched tile is claimed not sure how to say it yet
	
	row - the row value inputted by a player
	col - the column value inputted by a player
	*go - determines the player turns
	R[] - the array of tiles claimed by Player R
	B[] - the array of tiles claimed by Player B
	S[] - the array of tiles claimed by any player
	T[] - an array that holds tiles for the cascading spread effect
	*rSize - the number of elements in R[]
	*bSize - the number of elements in B[]
	*sSize - the number of elements in S[]
	*tSize - the number of elements in T[]
	grid[][3] - the board
*/
void
Replace(int row,int col,int go,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int found = 0; // if this is true, then the current tile is primed (meaning that it will 'expand' and spread to 3 adjacent tiles)
	int temp = grid[row][col]; // temporary variable that holds the tile
	int inR = (Search(temp,R,(*rSize))!=-1); // if true, then pos exists in R[]
	int inB = (Search(temp,B,(*bSize))!=-1); // if true, then pos exists in B[]
	int inS = (Search(temp,S,(*sSize))!=-1); // if true, then pos exists in S[]
	int inT = (Search(temp,T,(*tSize))!=-1); // if true, then pos exists in T[]
	
	if(go&&inB){ // if it is Player R's turn and the tile given hits a tile claimed by Player B, then it is removed and primed for expanding
		int tempB = *bSize;
		del(temp,B,&tempB);
		*bSize = tempB;
		found = 1;
	}
	if(go&&inR){ // if it is Player R's turn and the given tile hits their own tile it is primed for expanding
		found = 1;
	}else if(go&&!inR){ // if it is Player R's turn and the tile hits an unclaimed tile, claim that tile and do nothing else
		int tempR = *rSize;
		add(temp,R,&tempR);
		*rSize = tempR;
	}
	
	if(!go&&inR){ // if it is Player B's turn and the given tile hits a tile claimed by Player R, then it is removed and primed for expanding
		int tempR = *rSize;
		del(temp,R,&tempR);
		*rSize = tempR;
		found = 1;
	}
	if(!go&&inB){ // if it is Player B's turn and the given tile hits their own tile it is primed for expanding
		found = 1;
	}else if(!go&&!inB){ // if it is Player B's turn and the given tile hits an unclaimed tile, claim that tile and do nothing else
		int tempB = *bSize;
		add(temp,B,&tempB);
		*bSize = tempB;
	}
	
	if(found&&!inS){ // if the given tile is primed, but not in S[], then it is added to S[] and unprimed (it will not explode)
		int tempS = *sSize;
		add(temp,S,&tempS);
		*sSize = tempS;
		found = 0;
	}
	if(found&&inS&&!inT){ // if the given tile if primed and in S[] then it expands to 3 adjacent tiles for the current player
		int tempT = *tSize;
		add(temp,T,&tempT);
		*tSize = tempT;
		int tempR = *rSize;
		int tempB = *bSize;
		int tempS = *sSize;
		int tempT1 = *tSize;
		Expand(row,col,go,R,B,S,T,&tempR,&tempB,&tempS,&tempT1,grid);
		*rSize = tempR;
		*bSize = tempB;
		*sSize = tempS;
		*tSize = tempT;
	}
	
}
	
/*
	This function handles tilespreading
	
	row - the row value inputted by a player
	col - the column value inputted by a player
	*go - determines the player turns
	R[] - the array of tiles claimed by Player R
	B[] - the array of tiles claimed by Player B
	S[] - the array of tiles claimed by any player
	T[] - an array that holds tiles for the cascading spread effect
	*rSize - the number of elements in R[]
	*bSize - the number of elements in B[]
	*sSize - the number of elements in S[]
	*tSize - the number of elements in T[]
	grid[][3] - the board
*/
void
Expand(int row,int col,int go,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int u = -1;
	int leftCol = col-1;
	if(leftCol<3&&leftCol>=0) u = 1; // checks if the left of pos is within bounds
	int d = -1;
	int rightCol = col+1;
	if(rightCol<3&&rightCol>=0) d = 1; // checks if the right of pos is within bounds
	int k = -1;
	int downRow = row-1;
	if(downRow<3&&downRow>=0) k = 1; // checks if the blow of pos is within bounds
	int r = -1;
	int upRow = row+1;
	if(upRow<3&&upRow>=0) r = 1; // checks if the above of pos is within bounds
	
	int tempR = *rSize;
	int tempB = *bSize;
	int tempS = *sSize;
	int tempT = *tSize;
	Remove(grid[row][col],go,R,B,S,T,&tempR,&tempB,&tempS,&tempT); // removes the given tile
	*rSize = tempR;
	*bSize = tempB;
	*sSize = tempS;
	*tSize = tempT;
	
	if(go&&u!=-1){
		// Replace left if it is Player R's turn
		Replace(row,leftCol,go,R,B,S,T,&tempR,&tempB,&tempS,&tempT,grid);
	}
	if(!go&&d!=-1){
		// Replace right if it is Player B's turn
		Replace(row,rightCol,go,R,B,S,T,&tempR,&tempB,&tempS,&tempT,grid);
	}
	if(k!=-1){
		// Replace down
		Replace(downRow,col,go,R,B,S,T,&tempR,&tempB,&tempS,&tempT,grid);
	}
	if(r!=-1){
		// Replace up
		Replace(upRow,col,go,R,B,S,T,&tempR,&tempB,&tempS,&tempT,grid);
	}
	
	*rSize = tempR;
	*bSize = tempB;
	*sSize = tempS;
	*tSize = tempT;
}

/*
	This function updates the game state and handles the tilespread
	Precondition: grid[row][col] should be an element of either R[] or B[]
	
	row - the row value inputted by a player
	col - the column value inputted by a player
	*good - determines if player inputs are valid
	*go - determines the player turns
	*start - determines whether players have placed their initial tiles
	*val - the number of turns that have passed
	R[] - the array of tiles claimed by Player R
	B[] - the array of tiles claimed by Player B
	S[] - the array of tiles claimed by any player
	T[] - an array that holds tiles for the cascading spread effect
	*rSize - the number of elements in R[]
	*bSize - the number of elements in B[]
	*sSize - the number of elements in S[]
	*tSize - the number of elements in T[]
	grid[][3] - the board
*/
void
Update(int row,int col,int *good,int go,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int temp = grid[row][col]; // temporary variable that holds pos
	*good = 0;
	if(Search(temp,S,(*sSize))==-1){ // if the tile isn't in S[], this will add it to S[] so Expand() can function as intended
		int tempS = *sSize;
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1;
	}else{
		*good = 1;
	}
	if((*good)&&(Search(temp,S,(*sSize))!=-1)&&(Search(temp,T,(*tSize))==-1)){ // now that the conditions above are met, check if the tile isn't in T[] to proceed with Expand()
		int tempT = *tSize;
		add(temp,T,&tempT);
		*tSize = tempT;
		int tempR = *rSize;
		int tempB = *bSize;
		int tempS = *sSize;
		int tempT1 = *tSize;
		Expand(row,col,go,R,B,S,T,&tempR,&tempB,&tempS,&tempT1,grid);
		*rSize = tempR;
		*bSize = tempB;
		*sSize = tempS;
		*tSize = tempT;
	}
}

/*
	This function handles and validates player input and updates the board accordingly with various functions
	
	row - the row value inputted by a player
	col - the column value inputted by a player
	*good - determines if player inputs are valid
	*go - determines the player turns
	*start - determines whether players have placed their initial tiles
	*val - the number of turns that have passed
	R[] - the array of tiles claimed by Player R
	B[] - the array of tiles claimed by Player B
	S[] - the array of tiles claimed by any player
	T[] - an array that holds tiles for the cascading spread effect
	*rSize - the number of elements in R[]
	*bSize - the number of elements in B[]
	*sSize - the number of elements in S[]
	*tSize - the number of elements in T[]
	grid[][3] - the board
*/
void
NextPlayerMove(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int temp = grid[row][col]; // temporary variable that holds the value of the tile at pos
	if(!(*over)&&(*go)&&(*start)){ // handles Player R's initial turn
		int tempR = *rSize; // adds the tile to R
		add(temp,R,&tempR);
		*rSize = tempR;
		int tempS = *sSize; // adds the tile to S
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1; // good being true means that the other player can proceed with their turn
	}else if(!(*over)&&!(*go)&&(*start)){ // handles Player B's initial turn
		int tempB = *bSize; // adds the tile to B
		add(temp,B,&tempB);
		*bSize = tempB;
		int tempS = *sSize; // adds the tile to S
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1; // good being true means that the other player can proceed with their turn
	}
	int validR = (*go)&&(Search(temp,R,(*rSize))!=-1); // for this to be true, it must be Player R's turn and the tile from the given position is theirs
	int validB = !(*go)&&(Search(temp,B,(*bSize))!=-1); // for this to be true, it must be Player B's turn and the tile from the given position is theirs
	if(!(*over)&&!(*start)&&(validR||validB)){ // this part will only run once both players have placed down their first tiles and the given input is valid
		int tempGood = *good;
		int tempR = *rSize;
		int tempB = *bSize;
		int tempS = *sSize;
		int tempT = *tSize;
		Update(row,col,&tempGood,(*go),R,B,S,T,&tempR,&tempB,&tempS,&tempT,grid);
		*good = tempGood;
		*rSize = tempR;
		*bSize = tempB;
		*sSize = tempS;
		*tSize = tempT;
		*good = 1;
	}
	if((*start)&&(*rSize)==1&&(*bSize)==1){ // this checks if both players have already placed their initial tiles
		*start = 0; // this being false means that the game can actually start
	}
	if(!(*over)&&(*good)){ // if the game isn't over and inputs are valid (denoted by good being true), then the next player may take their turn
		*good = 0; // makes good false again for the next turn
		*go = !(*go); // switches the player turns
		*val = *val + 1; // increments the amount of (valid) turns that have been made
	}
}

/*
	This function displays the board state
	
	R[] - the array of tiles claimed by Player R
	B[] - the array of tiles claimed by Player B
	rSize - the number of elements in R[]
	bSize - the number of elements in B[]
	grid[][3] - the board
*/
void
DisplayBoard(int R[],int B[],int rSize,int bSize,int grid[][3]){
	for(int i=0;i<3;i++){ // rows of the board
		for(int j=0;j<3;j++){ // columns of the board
			int inR = Search(grid[i][j],R,rSize)!=-1; // if this is true, then the value on the grid exists in R[]
			int inB = Search(grid[i][j],B,bSize)!=-1; // if this is true, then the value on the grid exists in B[]
			if(inR&&inB){
				printf("@ "); // is displayed if the tile is claimed by both R[] and B[]
			}else if(inR){
				printf("R "); // is displayed if the tile is claimed by R[]
			}else if(inB){
				printf("B "); // is displayed if the tile is claimed by B[]
			}else{
				printf("- "); // is displayed if the tile is unclaimed
			}
		}
		printf("\n");
	}
}

/*
	This function checks if the game should end based on set conditions
	
	rSize - the number of elements in R[]
	bSize - the number of elements in B[]
	val - the number of turns that have passed
	start - is only true at the start of the game when both players have not placed down any tiles
	*over - determines the end of the game
*/
void
GameState(int rSize,int bSize,int val,int start,int *over){
	int F = (9-(rSize+bSize))==3; // checks if there are only 3 unclaimed tiles left on the board
	int domination = (rSize>0&&bSize==0)||(rSize==0&&bSize>0); // checks if there are only R[] tiles or B[] tiles on the board
	/*
		The game ends if:
			1. there are only 3 unclaimed tiles left on the board
			2. 20 or more turns have passed
			3. the game is ongoing and only R[] or B[] tiles remain
	*/
	if(F||val>=20||!start&&domination) *over = 1;	
}

/*
	This function displays the winner of a game
	
	rSize - the number of elements in R[]
	bSize - the number of elements in B[]
	over - determines if the game is over
*/
void
GameOver(int rSize,int bSize,int over){
	if(over){ // if the game has ended, this is true
		printf("\n----------------------------------------\n");
		if(rSize>bSize){
			printf("Player R wins!\n"); // if there are more elements in R[] than B[] then Player R wins
		}else if(rSize<bSize){
			printf("Player B wins!\n"); // if there are more elements in B[] than R[] then Player B wins
		}else if(rSize==bSize){
			printf("Draw!\n"); // if there are an equal amount of elements in both R[] and B[], then it is a tie
		}
		printf("----------------------------------------\n");
	}
}

/*
	This function resets all values back to their default state and clears all arrays
	
	*good - determines if player inputs are valid
	*go - determines the player turns
	*start - determines whether players have placed their initial tiles
	*val - the number of turns that have passed
	R[] - the array of tiles claimed by Player R
	B[] - the array of tiles claimed by Player B
	S[] - the array of tiles claimed by any player
	T[] - an array that holds tiles for the cascading spread effect
	*rSize - the number of elements in R[]
	*bSize - the number of elements in B[]
	*sSize - the number of elements in S[]
	*tSize - the number of elements in T[]
*/
void
ResetValues(int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize){
	*good = 0;
	*go = 1;
	*start = 1;
	*val = 0;
	*over = 1;
	int tempR = *rSize;
	int tempB = *bSize;
	int tempS = *sSize;
	int tempT = *tSize;
	EmptyArray(R,&tempR);
	EmptyArray(B,&tempB);
	EmptyArray(S,&tempS);
	EmptyArray(T,&tempT);
	*rSize = tempR;
	*bSize = tempB;
	*sSize = tempS;
	*tSize = tempT;
}

/*
	This function displays a main menu that asks users if they would like to start a new game or exit the program
	
	*exitProgram - determines whether a new game is played or the program is exited
	*over - determines whether a new game will be played
*/
void
MenuDisplay(int *exitProgram,int *over){
	int temp = 0; // temporary value that holds input
	printf("--- THE AMAZING DIGITAL INFECTION GAME ---\n");
	printf("Hi there its me TEST CAINE. I will probably be replaced by an actual description, so yeah.\n");
	printf("[1] - Play Game\n");
	printf("[2] - Exit Program\n");
	do{
		printf("\nInput: ");
		scanf("%d",&temp);
	}while(temp!=1&&temp!=2); // makes sure player input is a valid choice
	if(temp==1){
		*over = 0; // starts the main game's loop
	}else if(temp==2){
		*exitProgram = 1; // exits the program
	}
}

/*
	This function displays how many turns have passed, which player's turn it is, and handles player input
	
	go - determines the player turn
	val - the number of turns that have passed
	*row - the row input by the player
	*col - the column input by the player
*/
void
DisplayStats(int go,int val,int *row,int *col){
	printf("\n----------------------------------------\n"); // just a separator to make things look cleaner
	printf("Turn %d\n",val); // displays how many turns have passed
	if(go){
		printf("Player R's turn\n"); // if go is true, then it is Player R's turn
	}else{
		printf("Player B's turn\n"); // if go is false, then it is Player B's turn
	}
	int x=0,y=0; // temporary values to hold input
	do{
		printf("\nRow: ");
		scanf("%d",&x);
	}while(x<0||x>2); // handles input for the row and makes sure it is within bounds
	do{
		printf("\nCol: ");
		scanf("%d",&y);
	}while(y<0||y>2); // handles input for the column and makes sure it is within bounds
	*row = x; // return the row value
	*col = y; // return the column value
}

int
main(){
	int good = 0; // boolean value that determines the validity of a player's turn
	int go = 1; // boolean value that determines the player turns
	int start = 1; // boolean value that is only true until both players have placed their first tiles
	int val = 0; // boolean value that determines how many turns have passed, maximum 20 turns
	int over = 1; // boolean value that determines the end of the game
	
	int R[9]; // an array that represents the tiles claimed by Player R
	int rSize = 0; // the current number of elements in R[]
	int B[9]; // an array that represents the tiles claimed by Player B
	int bSize = 0; // the current number of elements in B[]
	int S[9]; // an array that represents currently occupied tiles by all players
	int sSize = 0; // the current number of elements in S[]
	int T[9]; // an array that is responsible for handling cascading tilespread
	int tSize = 0; // the current number of elements in T[]
	
	int grid[3][3] = { // a read-only array that represents the playing field
		1,2,3,
		4,5,6,
		7,8,9,
	};
	
	int x=0,y=0; // integer values that hold player inputs
	int exitProgram = 0; // boolean value that determines if the user wants to play again or exit the program
	while(!exitProgram){ // the main menu loop
		MenuDisplay(&exitProgram,&over); // displays a menu that allows users to either start a new game or exit the program
		while(!over){ // the main gameplay loop
			DisplayStats(go,val,&x,&y); // displays how many turns have passed, which player's turn it is, and gets player input
			NextPlayerMove(x,y,&good,&go,&start,&val,&over,R,B,S,T,&rSize,&bSize,&sSize,&tSize,grid); // processes player input and contains main game logic
			DisplayBoard(R,B,rSize,bSize,grid); // displays the board state after inputs have been processed
			GameState(rSize,bSize,val,start,&over); // checks if the game should end or not
			GameOver(rSize,bSize,over); // shows the winner if the game is over
		}
		ResetValues(&good,&go,&start,&val,&over,R,B,S,T,&rSize,&bSize,&sSize,&tSize); // resets all values back to their initial state and clears all arrays for the next game
	}
}