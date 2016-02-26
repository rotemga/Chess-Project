#ifndef GAMEFLOW_
#define GAMEFLOW_

#include "Chess.h"


void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
int num_cordinate(char x);
char* next_argument(char *input_ptr);
void print_line();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
unsigned int depth_update(unsigned int x, unsigned int depth);
char* color_update(char *setcolor, char *color);
void clear(char board[BOARD_SIZE][BOARD_SIZE]);
void remove_disc(char board[BOARD_SIZE][BOARD_SIZE], unsigned int x, unsigned int y);
void set_disc(char board[BOARD_SIZE][BOARD_SIZE], unsigned int x, unsigned int y, char *color, char type, unsigned int game);
int valid_board(char board[BOARD_SIZE][BOARD_SIZE]);
char* getInput();
void * myRealloc(void * ptr, size_t size);
void * myMalloc(size_t size);
void * myCalloc(size_t size);
void myFree(void * ptr);
void freeList(listMoves* current_head);
void freeMove(move* current_head);
void freePositon(position* current_head);
int prefix(char *pre, char *str);
void increaseListMoves(listMoves* moves);
listMoves* initMoves(listMoves *moves);
void addMove(listMoves* moves, position* from, position* to, unsigned int depth);
unsigned int checkEmptyBoard(unsigned int arr[]);
char promotionPawn(char* type, char* color);
void countDiscs(char board[BOARD_SIZE][BOARD_SIZE], unsigned int res[12]);
char discType(char type);
unsigned int checkValidSetType(char board[BOARD_SIZE][BOARD_SIZE], char type, char* color);
void printMoves(listMoves* moves, char board[BOARD_SIZE][BOARD_SIZE]);
void printComputerMove(move m, char board[BOARD_SIZE][BOARD_SIZE]);
char discChar(char* type);
void copyingBoard(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]);
unsigned int checkValidPosition(position *p);
unsigned int checkColorPosition(char board[BOARD_SIZE][BOARD_SIZE], position* p);
unsigned int checkPositionEmpty(char board[BOARD_SIZE][BOARD_SIZE], position* p);
GameRef newGame();

#endif 
GAMEFLOW_