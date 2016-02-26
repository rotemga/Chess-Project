#ifndef CHESS_
#define CHESS_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <time.h>




#define WHITE "white"
#define BLACK "black"

#define WHITE_P 'm'
#define WHITE_B 'b'
#define WHITE_N 'n'
#define WHITE_R 'r'
#define WHITE_Q 'q'
#define WHITE_K 'k'

#define BLACK_P 'M'
#define BLACK_B 'B'
#define BLACK_N 'N'
#define BLACK_R 'R'
#define BLACK_Q 'Q'
#define BLACK_K 'K'


#define EMPTY ' '

#define BOARD_SIZE 8

// board initialization
#define ENTER_SETTINGS "Enter game settings:\n" 
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"  
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"

#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"

#define WRONG_ROOK_POSITION "Wrong position for a rook\n" 
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"  

#define TIE "The game ends in a tie\n"
#define NO_DISC "The specified position does not contain your piece\n"

#define perror_message(func_name) (perror("Error: standard function %s has failed", func_name));
#define print_message(message) (printf("%s", message));



typedef struct
{
	unsigned int x;
	unsigned int y;
	struct position *next;
	unsigned int cnt;

}position;

typedef struct
{
	position* currPos;
	char currBoard[BOARD_SIZE][BOARD_SIZE];
	struct move* next;
	unsigned int cnt;
}move;

typedef struct
{
	move m;
	struct listMoves *next;
	unsigned int cnt;

}listMoves;

typedef struct
{
	move m;
	int score;
}scoredMove;

typedef struct
{
	scoredMove sm;
	struct listScoredMoves *next;
	unsigned int cnt;

}listScoredMoves;

typedef struct Game {
	// board game
	char board[BOARD_SIZE][BOARD_SIZE];
	char* nextPlayer; // white(1) or black(2)
	int mode; // playerVSplayer(1) or playerVScomputer(2)
	int minimaxDepth; //5 means best
	// when we want to move a disc we save the types and the coordinates. 
	char fromType;
	int Xfrom;
	int Yfrom;
	int Xto;
	int Yto;
	char* userColor; // white or black
	char* computerColor; // white or black
} Game;

typedef struct Game* GameRef;






#endif 
CHESS_

