#ifndef MINIMAX_
#define MINIMAX_


#include "ChessRules.h"


int scoring(char board[BOARD_SIZE][BOARD_SIZE], char *color);
int scoreWhite(unsigned int res[12]);
int scoreBlack(unsigned int res[12]);
int alphabetaPruning(char* color, char board[BOARD_SIZE][BOARD_SIZE], unsigned int depth, int alpha, int beta, int max_or_min);
void addScoredMoveToList(scoredMove* new, listScoredMoves* list);
listMoves* returnBestMoves(char board[BOARD_SIZE][BOARD_SIZE], char* color, unsigned int depth);
unsigned int checkIfInMovesList(listMoves* moves, position* from, position* to);
void copyMove(move* copy, move* empty);
int bestDepth(char board[BOARD_SIZE][BOARD_SIZE], char *color);
int power(int a, int b);
int Min(int x, int y);
int Max(int x, int y);
int alphabetaForGetScore(char* color, char board[BOARD_SIZE][BOARD_SIZE], unsigned int depth, move* m);
int alphabetaPruningMoves(char* color, char board[BOARD_SIZE][BOARD_SIZE], unsigned int depth, unsigned int originDepth, unsigned int max_depth, int alpha, int beta, int max_or_min, listMoves* res, listMoves* movesOrigin, int bestScore);
void PruningMoves(char* color, char board[BOARD_SIZE][BOARD_SIZE], unsigned int depth, listMoves* res, int bestScore);
#endif 
MINIMAX_