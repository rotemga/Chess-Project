

#ifndef CHESSRULES_
#define CHESSRULES_

#include "GameFlow.h"



unsigned int checkIfMoveIsValid(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color);
unsigned int checkDiagForBishop(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color, char type);
unsigned int checkRowForRook(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color);
void makeMove(char board[BOARD_SIZE][BOARD_SIZE], char* color, position *from, position *to, char X);
unsigned int checkIfLegalX(char type, char X);
void capture(char board[BOARD_SIZE][BOARD_SIZE], position *from, position *to, char* color, char type);
unsigned int Check(char board[BOARD_SIZE][BOARD_SIZE], char* color);
void findKingPos(char board[BOARD_SIZE][BOARD_SIZE], char* color, position* kingPos);
unsigned int movesFromPos(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate);
void allMoves(char board[BOARD_SIZE][BOARD_SIZE], char* color, listMoves* moves);
unsigned int KnightPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate);
unsigned int PawnPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate);
unsigned int KingPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate);
unsigned int BitshopPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate);
unsigned int RookPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate);
unsigned int QueenPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate);
unsigned int checkIfKingThreatened(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color);
unsigned int legalMoveToPosColor(unsigned int colOfToPos, char* color);
int whileLoopForCheck(int x_Minus_or_plus, int y_Minus_or_plus, int col, int x, int y, position* to, char board[BOARD_SIZE][BOARD_SIZE], char b_or_r, char B_or_R);
int knight_check(position* to, char board[BOARD_SIZE][BOARD_SIZE], int col);
char typePromotion(move* m, char* color);
unsigned int forKnight(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color, listMoves* moves);
unsigned int checkForRook(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color);
unsigned int checkForBishop(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color);
unsigned int isMate(char board[BOARD_SIZE][BOARD_SIZE], char* color);
unsigned int isTie(char board[BOARD_SIZE][BOARD_SIZE], char* color, listMoves* moves);
unsigned int OneMoveIsMate(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, unsigned int col, char* color, unsigned int promotion);
#endif 
CHESSRULES_