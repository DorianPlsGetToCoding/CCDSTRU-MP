#include <stdio.h>

<<<<<<< Updated upstream
void Remove(int pos){ // parameters not final, can change
=======
/*
	Description goes here
*/
/*
void
Remove(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int temp = grid[row][col]; // value of the coordinate to be updated
	if(*go){
		del(temp,R,(*rSize));
	}
	else if(!(*go)){
		del(temp,B,(*bSize));
	}
>>>>>>> Stashed changes
	
}
*/

<<<<<<< Updated upstream
void Replace(int pos){
=======
/*
	Description goes here
*/

/*
void
Replace(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int found = 0;
	int x = row, y = col;
	int temp = grid[row][col]; // value of the coordinate to be updated
	if(*go&&Search(temp,B,(*bSize))!=-1){
		del(temp,B,(*bSize));
		found = 1;
	}
	else if(*go&&Search(temp,R,(*rSize))!=-1){
		found = 1;
	}
	else if(*go&&Search(temp,R,(*rSize))==-1){
		int tempR = *rSize; // adds the tile to R
		add(temp,R,&tempR);
		*rSize = tempR;
	}
>>>>>>> Stashed changes
	
}
*/

<<<<<<< Updated upstream
void Expand(int pos){
	
}

void Update(int pos){
	
=======
/*
	Description goes here
*/
void
Expand(int row,int col,int go,int R[],int B[],int S[],int T[]){
	int u = -1;
	int d = -1;
	int k = -1;
	int r = -1;
}

/*
	Description goes here
	Precondition: grid[row][col] should be an element of either R[] or B[]
*/
void
Update(int row,int col,int *good,int go,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int temp = grid[row][col];
	*good = 0;
	if(Search(temp,S,(*sSize))==-1){ // if the tile isn't in S[], this will add it to S[] so Expand() can function as intended
		int tempS = *sSize;
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1;
	}else{ // if the tile is already in S[], then Expand() can proceed as intended
		*good = 1;
	}
	if((*good)&&(Search(temp,S,(*sSize))!=-1)&&(Search(temp,T,(*tSize))==-1)){ // now that the conditions above are met, check if the tile isn't in T[] to proceed with Expand()
		printf("\nIM EXPANDING\n");
		int tempT = *tSize;
		add(temp,T,&tempT);
		*tSize = tempT;
		//Expand();
	}
}

/*
	This function handles the input given by a player and validates whether it is a valid input and functions accordingly
*/
void
NextPlayerMove(int row,int col,int *good,int *go,int *start,int *val,int *over,int R[],int B[],int S[],int T[],int *rSize,int *bSize,int *sSize,int *tSize,int grid[][3]){
	int temp = grid[row][col]; // value of the tile in the grid using pos
	if(!(*over)&&(*go)&&Search(temp,B,(*bSize))==-1&&(*start)){ // Player R's initial turn, with additional check to make sure they don't place same tile as B
		int tempR = *rSize; // adds the tile to R
		add(temp,R,&tempR);
		*rSize = tempR;
		int tempS = *sSize; // adds the tile to S
		add(temp,S,&tempS);
		*sSize = tempS;
		*good = 1; // good being true means that the other player can proceed with their turn
	}else if(!(*over)&&!(*go)&&Search(temp,R,(*rSize))==-1&&(*start)){ // Player B's initial turn, with additional check to make sure they don't place same tile as R
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
	if((*start)&&(*rSize)==1&&(*bSize)==1){ // this checks for if both players have already placed their initial tiles
		*start = 0; // this being false means that the game can actually start
	}
	if(!(*over)&&(*good)){ // if the game isn't over and inputs are valid (denoted by good being true), then the next player may take their turn
		*good = 0; // makes good false again for the next turn
		*go = !(*go); // switches the player turns
		*val = *val + 1; // increments the amount of (valid) turns that have been made
	}
>>>>>>> Stashed changes
}

void NextPlayerMove(){
	
}

void GameOver(){
	
}

<<<<<<< Updated upstream
int main(){
	int good,go,start,over,found,val; // boolean values & val, which is a positive integer including 0
	int 
	// i dunno how to initialize the arrays pls help
	// System Initialization
	good = 0;
	go = 1;
	start = 1;
	found = 0;
	val = 0;
=======
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
		printf("Current Player Turn: %d\n",go);
		printf("Start: %d\n",start);
		printf("R: ");
		PrintArray(R,rSize);
		printf("B: ");
		PrintArray(B,bSize);
		printf("S: ");
		PrintArray(S,sSize);
		printf("T: ");
		PrintArray(T,tSize);
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
	//GameOver();
>>>>>>> Stashed changes
}