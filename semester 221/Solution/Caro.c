/* See my explaination at: https://youtu.be/exvqEIiBk2c */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_SIZE 15

const char HORZ = 196;           
const char VERT = 179; 			
const char TL   = 218;
const char TM   = 194;
const char TR   = 191; 			 
const char BL   = 192;
const char BM   = 193;
const char BR   = 217;
const int numW  = 3;             
const int charW = 1;            
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const char* inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const char* endOfHistory = "This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* startOfGame = "This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* invalidInput = "Illegal input, please try again: ";

enum Stone {NA, X, O};

struct Move {
    int row;
    int col;
    int Row[225];
    int Col[225];
} move;

//store coordinate of every moves - for displayHistory function
void createArr(char *S){
	int i;
	int length = strlen(S);
    int count = 0; //to count how many moves
    for(i = 0; i < length; i++){
        if((S[i] < 97 && S[i+1] < 97)){
            move.Row[count] = 15 - (10*(S[i] - '0') + (S[i+1]-'0'));
   	 		move.Col[count] = S[i+2] - 'a';
            i += 2;
        }
        else{
            move.Row[count] = 15 - (S[i] - '0');
   	 		move.Col[count] = S[i+1] - 'a';
            ++i;
        }
    	++count;
    }
}

static char* lineString( char left, char mid, char right, char horz, int wcell, int ncell ) {
    int i;
	static char result[100];
    strcpy(result, "");
    char cell[10];
    for(i = 0; i < wcell; i++){
        cell[i] = horz;
    }
    cell[wcell] = '\0';
    strncat(result,&left,1);
    char cellMid[20];
    strcpy(cellMid, cell);
    strncat(cellMid, &mid,1);
    for ( i = 0; i < ncell - 1; i++ )
        strcat(result, cellMid);
    char cellRight[20];
    strcpy(cellRight, cell);
    strncat(cellRight, &right,1);
    strcat(result, cellRight);
    return result;
}

void displayBoard(enum Stone arr[][15], int size) {
	int i,j;
    //UPPERLINE
    printf("   ");
    for(i = 0; i < size; i++) {
        printf("  %c ", (char)(i + 'a'));
    }
    printf("\n");
    printf("   %s\n", lineString( TL, TM, TR, HORZ, 3, numPerLine ));

    //MIDDLE
    for(i = 0; i < size; i++) {
        printf("%2d %c", size - i, VERT);
        for(j = 0; j < size; j++) {
            if(arr[i][j] == NA) printf("   %c", VERT);
            if(arr[i][j] == X) printf(" X %c", VERT);
            if(arr[i][j] == O) printf(" O %c", VERT);
        }
        printf("\n");
        if(i != size - 1) printf("   %s\n", lineString( VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine ));
    }

    //UNDERLINE
    printf("   %s\n", lineString( BL, BM, BR, HORZ, 3, numPerLine ));
}

void displayBoardSimple(enum Stone arr[][15], int size) {
	int i,j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++) {
            printf("%d", arr[i][j]);
        }
    }
    printf("\n");
}

int getRow(char *S){
    int i = 0;
    int num = 0;
    for(i = 0; i < strlen(S)-1; i++)
        num = num*10 + (S[i] - '0'); //convert number type string into type int
    return 15-num; //SIZE = 15
}

int getCol(char *S){
    int num = S[strlen(S)-1] - 'a';
    return num;
}


bool makeMove(enum Stone board[15][15], int size, char* playerMove, bool isFirstPlayerTurn){
    int i,j;
    //check invalid or valid move
    //if valid, add to board, else do nothing
    int length = strlen(playerMove);
        //check the last element of playerMove is a char or not - mean col,
        //valid or not
    int row,col; //like i,j in array arr[i][j]
    if(length > 3) return false;
    else{
        if(playerMove[length-1] < 97) return false;
        else if(playerMove[length-1] > 111) return false;
        else col = getCol(playerMove);
        //check row is valid or not
        row = getRow(playerMove);
        if(row < 0 || row > 14) return false;
        else{ 
        	//using struct to save address
        	move.row = row;
            move.col = col;
            //check value at playMove is NA or not
            if(board[move.row][move.col] != NA) return false;
            else{
                if(isFirstPlayerTurn) 
                    board[move.row][move.col] = X;
                else board[move.row][move.col] = O;
				return true;
            }
        }
    }
}

bool checkDiagonalRight(enum Stone board[15][15],int size, enum Stone play, int x, int y){
	int rowD, colD;
	int rowU, colU;
	int count = 1;
	int temp;
		//down
	for(rowD = x+1, colD = y-1; rowD <= x+5, colD >= y-5; rowD++,colD--){
		if(board[rowD][colD] == play){
			count++;
			if(count > 5) return false; //rule bonus 1
		} 
		else break;
	}
	if(count == 5){
		if(play == O){
			if((board[x+5][y-5] == X && board[x-1][y+1] == X) || board[x+5][y-5] == O || board[x-1][y+1] == O) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}
		else{
			if((board[x+5][y-5] == O && board[x-1][y+1] == O) || board[x+5][y-5] == X || board[x-1][y+1] == X) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}	
	}
	else{
		//up
		temp = count;
		for(rowU = x-1, colU = y+1; rowU >= x - (6-temp), colU <= y + (6-temp); rowU--, colU++){
			if(board[rowU][colU] == play){
				count++;
				if(count > 5) return false; //rule bonus 1
			}
			else break;	
		}
		if(count == 5){
			if(temp == 1){
				if(play == O){
					if((board[x+1][y-1] == X && board[x-5][y+5] == X) || board[x+1][y-1] == O || board[x-5][y+5] == O) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[x+1][y-1] == O && board[x-5][y+5] == O) || board[x+1][y-1] == X || board[x-5][y+5] == X) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
			else{
				if(play == O){
					if((board[rowD][colD] == X && board[rowU][colU] == X) || board[rowD][colD] == O || board[rowU][colU] == O) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[rowD][colD] == O && board[rowU][colU] == O) || board[rowD][colD] == X || board[rowU][colU] == X) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
		}
		else return false;
	}	
}

bool checkDiagonalLeft(enum Stone board[15][15],int size, enum Stone play, int x, int y){
	int rowD, colD;
	int rowU, colU;
	int count = 1;
	int temp;
		//down
	for(rowD = x+1, colD = y+1; rowD <= x+5, colD <= y+5; rowD++,colD++){
		if(board[rowD][colD] == play){
			count++;
			if(count > 5) return false; //rule bonus 1;
		} 
		else break;
	}
	if(count == 5){
		if(play == O){
			if((board[x+5][y+5] == X && board[x-1][y-1] == X) || board[x+5][y+5] == O || board[x-1][y-1] == O) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}
		else{
			if((board[x+5][y+5] == O && board[x-1][y-1] == O) || board[x+5][y+5] == X || board[x-1][y-1] == X) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}	
	}
	else{
		//up
		temp = count;
		for(rowU = x-1, colU = y-1; rowU >= x - (6-temp), colU >= y - (6-temp); rowU--, colU--){
			if(board[rowU][colU] == play){
				count++;
				if(count > 5) return false; //rule bonus 1
			} 	
			else break;	
		}
		if(count == 5){
			if(temp == 1){
				if(play == O){
					if((board[x+1][y+1] == X && board[x-5][y-5] == X) || board[x+1][y+1] == O || board[x-5][y-5] == O) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[x+1][y+1] == O && board[x-5][y-5] == O) || board[x+1][y+1] == X || board[x-5][y-5] == X) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
			else{
				if(play == O){
					if((board[rowD][colD] == X  && board[rowU][colU] == X) || board[rowD][colD] == O || board[rowU][colU] == O) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[rowD][colD] == O  && board[rowU][colU] == O) || board[rowD][colD] == X || board[rowU][colU] == X) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
		}
		else return false;
	}	
}

bool checkVer(enum Stone board[15][15],int size, enum Stone play, int x, int y){
	int rowD, colD = y;
	int rowU, colU = y;
	int count = 1;
	int temp;
		//down
	for(rowD = x+1; rowD <= x+5; rowD++){
		if(board[rowD][colD] == play){
			count++;
			if(count > 5) return false; //rule bonus 1
		}
		else break;
	}
	if(count == 5){
		if(play == O){
			if((board[x+5][y] == X && board[x-1][y] == X) || board[x+5][y] == O || board[x-1][y] == O) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}
		else{
			if((board[x+5][y] == O && board[x-1][y] == O) || board[x+5][y] == X || board[x-1][y] == X) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}	
	}
	else{
		//up
		temp = count;
		for(rowU = x-1; rowU >= x - (6-temp); rowU--){
			if(board[rowU][colU] == play){
				count++;
				if(count > 5) return false; //rule bonus 1
			}
			else break;	
		}
		if(count == 5){
			if(temp == 1){
				if(play == O){
					if((board[x+1][y] == X && board[x-5][y] == X) || board[x+1][y] == O || board[x-5][y] == O) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[x+1][y] == O && board[x-5][y] == O) || board[x+1][y] == X || board[x-5][y] == X) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
			else{
				if(play == O){
					if((board[rowD][colD] == X && board[rowU][colU] == X) || board[rowD][colD] == O || board[rowU][colU] == O) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[rowD][colD] == O && board[rowU][colU] == O) || board[rowD][colD] == X || board[rowU][colU] == X) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
		}
		else return false;
	}	
}

bool checkHorz(enum Stone board[15][15],int size, enum Stone play, int x, int y){
	int rowL = x, colL;
	int rowR = x, colR;
	int count = 1;
	int temp;
		//left
	for(colL = y-1; colL >= y-5; colL--){
		if(board[rowL][colL] == play){
			count++;
			if(count > 5) return false; //rule bonus 1
		}
		else break;
	}
	if(count == 5){
		if(play == O){
			if((board[x][y-5] == X && board[x][y+1] == X) || board[x][y-5] == O || board[x][y+1] == O) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}
		else{
			if((board[x][y-5] == O && board[x][y+1] == O) || board[x][y-5] == X || board[x][y+1] == X) return false; //rule bonus 2 + rule bonus 1
			else return true;
		}	
	}
	else{
		//right
		temp = count;
		for(colR = y+1; colR <= y + (6-temp); colR++){
			if(board[rowR][colR] == play){
				count++;
				if(count > 5) return false; //rule bonus 1
			}
			else break;	
		}
		if(count == 5){
			if(temp == 1){
				if(play == O){
					if((board[x][y-1] == X && board[x][y+5] == X) || board[x][y-1] == O || board[x][y+5] == O) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[x][y-1] == O && board[x][y+5] == O) || board[x][y-1] == X || board[x][y+5] == X) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
			else{
				if(play == O){
					if((board[rowL][colL] == X && board[rowR][colR] == X) || board[rowL][colL] == O || board[rowR][colR] == O) return false; // rule bonus 2 + rule bonus 1
					else return true;
				}
				else{
					if((board[rowL][colL] == O && board[rowR][colR] == O) || board[rowL][colL] == X || board[rowR][colR] == X) return false; //rule bonus 2 + rule bonus 1
					else return true;
				}	
			}
		}
		else return false;
	}	
}


bool hasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn) {
	int x = move.row;
	int y = move.col;
	enum Stone play;
	if(isFirstPlayerTurn) play = X;
	else play = O;
	if(checkDiagonalRight(board,MAX_SIZE,play,x,y) == true || checkDiagonalLeft(board,MAX_SIZE,play,x,y) == true || 
	   checkHorz(board,MAX_SIZE,play,x,y) == true || checkVer(board,MAX_SIZE,play,x,y) == true)
	   return true;
	else return false;	
}

void displayHistory(char* history, int numOfMoves) {
    int i,j;
    enum Stone game[15][15];
    for(i = 0; i < MAX_SIZE; i++) {
        for(j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoardSimple(game, MAX_SIZE);
    createArr(history);
	int count = -1;  //to know how many moves has gone, the first move is 0, so before that it is 0 - 1 = -1
	printf("%s",inputCommand); 
	while(true){ 
		char input;
    	scanf("%s",&input); //if left "&" from input like normal, it would lead to TLE error, why?
    	if(input == 'n'){
    		count++;
    		if(count >= numOfMoves) {
    			printf("%s",endOfHistory);
    			count = numOfMoves-1;
			}
    		else{
				if(count%2 == 0) game[move.Row[count]][move.Col[count]] = X;
    			else game[move.Row[count]][move.Col[count]] = O;
				displayBoardSimple(game,MAX_SIZE);
				printf("%s",inputCommand); 
			}
		}else if(input == 'p'){
			count--;
			if(count < -1) {
				printf("%s",startOfGame);
				count = -1;
			}
			else{
    			game[move.Row[count+1]][move.Col[count+1]] = NA;
				displayBoardSimple(game,MAX_SIZE);
				printf("%s",inputCommand); 
			}
		}else if(input == 's') {
			return;
		}else {
			printf("%s",invalidInput);
		}
	}
}

void startGame() {
	int i,j;
    enum Stone game[15][15];
    for(i = 0; i < MAX_SIZE; i++) {
        for(j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoardSimple(game, MAX_SIZE);
    char playerMove[50];
    bool player1Turn = true;
    printf("Player 1 turn: ");
    while(true) {
        scanf("%s", playerMove);
        if(strcmp(playerMove,"ff") == 0) {
            printf("%s", ((player1Turn) ? "Player 2 won " : "Player 1 won "));
            break;
        }
        else if(makeMove(game, MAX_SIZE, playerMove, player1Turn)){
            if(hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoardSimple(game, MAX_SIZE);
                printf("%s", ((player1Turn) ? "Player 1 won " : "Player 2 won "));
                return;
            }
            player1Turn = !player1Turn;
            displayBoardSimple(game, MAX_SIZE);
            printf("%s", ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: "));
        } else printf("Illegal move, please try again: ");
    }
}

int main(){
    printf("Welcome to Gomoku!\n");
    printf("1. Play game\n");
    printf("2. History\n");
    printf("3. Exit\n");
    printf("Please select mode [1/2/3]: ");
    int mode;
    while(true){
        scanf("%d", &mode);
        if(mode == 1) {
            startGame();
            return 0;
        } else if (mode == 2) {
            int numOfMoves;
            printf("Please enter number of moves: ");
            scanf("%d", &numOfMoves);
            char history[700];
            printf("Please enter history: ");
            scanf("%s", history);
            displayHistory(history, numOfMoves);
            return 0;
        } else if (mode == 3) {
            return 0;
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid mode, please try again: ");
        }
    }
    return 0;
}
