#ifndef CHESSLOGIC_
#define CHESSLOGIC_

#include "MiniMax.h"
#include "FilesLogic.h"

int userTurn(char board[BOARD_SIZE][BOARD_SIZE], char* color, char* next_player,unsigned int game_mode, unsigned int depth);
move checkMoveFormat(char board[BOARD_SIZE][BOARD_SIZE], char* color, char* input_ptr, unsigned int game_mode, unsigned int depth_computer, char* next_player);
int computerTurn(char board[BOARD_SIZE][BOARD_SIZE], char* color, unsigned int depth);

#endif 
CHESSLOGIC_