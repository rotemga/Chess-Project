#include "MiniMax.h"


//------------------This file include the minimax algorithm code------------------- 


//the function gives the scord for specific board by counting the num of pawns from each kind and color.
int scoring(char board[BOARD_SIZE][BOARD_SIZE], char *color){
	position* kingPos = myCalloc(sizeof(position));
	kingPos->x = 10; kingPos->y = 10;
	char* otherColor;
	unsigned int res[12];
	if (strcmp(color, WHITE) == 0)
		otherColor = BLACK;
	else
		otherColor = WHITE;
	//*************LOSSING/WINNING/TIE************************//
	listMoves* moves = myCalloc(sizeof(listMoves));
	if (isMate(board, color) == 1){//the color player is winning
		freeList(moves);
		freePositon(kingPos);
		return 200;
	}

	kingPos->x = 10; kingPos->y = 10;
	findKingPos(board, otherColor, kingPos);
	if (kingPos->x == 10){//winning
		freeList(moves);
		freePositon(kingPos);
		return 200;
	}
	if ((isTie(board, WHITE, moves) == 1) || (isTie(board, BLACK, moves) == 1)){
		freeList(moves);
		freePositon(kingPos);
		return -199;
	}
	freeList(moves);


	//************REGULAR****************//
	countDiscs(board, res);
	if (strcmp(color, WHITE) == 0){
		freePositon(kingPos);
		return (scoreWhite(res) - scoreBlack(res));
	}
	else{
		freePositon(kingPos);
		return (scoreBlack(res) - scoreWhite(res));
	}
	freePositon(kingPos);
}

//the function returns the score of the white palyer. 
int scoreBlack(unsigned int res[12]){
	int sum = 0;
	sum += res[11] * 400; //king score
	sum += res[10] * 9; //queen score
	sum += res[9] * 3; //knight score
	sum += res[8] * 5; //rook score
	sum += res[7] * 3; //bishop score
	sum += res[6] * 1; //pawn score
	return sum;
}

//the function returns the score of the black palyer.
int scoreWhite(unsigned int res[12]){
	int sum = 0;
	sum += res[5] * 400; //king score
	sum += res[4] * 9; //queen score
	sum += res[3] * 3; //knight score
	sum += res[2] * 5; //rook score
	sum += res[1] * 3; //bishop score
	sum += res[0] * 1; //pawn score
	return sum;
}




//this function return the best moves.
listMoves* returnBestMoves(char board[BOARD_SIZE][BOARD_SIZE], char* color, unsigned int depth){
	listMoves* res = myCalloc(sizeof(listMoves));
	int bestscore = alphabetaPruning(color, board, depth, -1000000, 1000000, 1);
	PruningMoves(color, board, depth, res, bestscore);
	return res;



}




// return 1 if move is in moves, else 0. 
unsigned int checkIfInMovesList(listMoves* moves, position* from, position* to){
	unsigned int cnt = moves->cnt;
	position* ptrPos;
	listMoves* ptr = moves;

	while (cnt > 0){
		if ((ptr->m.currPos->x == from->x) && (ptr->m.currPos->y == from->y)){
			ptrPos = (position*)ptr->m.currPos->next;
			if ((ptrPos->x == to->x) && (ptrPos->y == to->y)){
				return 1;
			}
		}
		cnt--;
		ptr = (listMoves*)ptr->next;
	}
	return 0;
}


//this function copy the move to "empty".
void copyMove(move* copy, move* empty){
	position* copyPos = copy->currPos;
	position* emptyPos = empty->currPos;
	position* ptrCopy = (position*)copyPos->next;
	position* ptrEmpty = (position*)emptyPos->next;
	emptyPos->x = copyPos->x;
	emptyPos->y = copyPos->y;
	ptrEmpty->x = ptrCopy->x;
	ptrEmpty->y = ptrCopy->y;
	copyingBoard(copy->currBoard, empty->currBoard);
}




//return the score of the input move with the input depth.
int alphabetaForGetScore(char* color, char board[BOARD_SIZE][BOARD_SIZE], unsigned int depth, move* m){
	char Newboard[BOARD_SIZE][BOARD_SIZE];
	int score = 0;
	char* otherColor;
	char type;
	if (strcmp(color, WHITE) == 0)
		otherColor = BLACK;
	else
		otherColor = WHITE;
	copyingBoard(board, Newboard);
	position* p1 = (position*)m->currPos, *p2 = (position*)m->currPos->next;

	type = typePromotion(m, color);
	makeMove(Newboard, color, p1, p2, type);

	if (depth == 1){
		return scoring(Newboard, color);
	}
	else{
		score = alphabetaPruning(otherColor, Newboard, depth - 1, -1000000, 1000000, 0);
		return score;
	}
	return 0;
}



//this function is using alpha - beta pruning algorithm to return the best score.
int alphabetaPruning(char* color, char board[BOARD_SIZE][BOARD_SIZE], unsigned int depth, int alpha, int beta, int max_or_min) {

	char Newboard[BOARD_SIZE][BOARD_SIZE];
	int cnt, score = 0;
	int next_min_max = 0;
	char* otherColor;
	char type = ' ';

	int val;


	move m;
	position* from = myCalloc(sizeof(position));
	position* to = myCalloc(sizeof(position));
	position* ptr;
	listMoves* moves = myCalloc(sizeof(listMoves));

	allMoves(board, color, moves);
	listMoves* ptr_moves = moves;
	cnt = moves->cnt;
	copyingBoard(board, Newboard);
	if (strcmp(color, WHITE) == 0)
		otherColor = BLACK;
	else
		otherColor = WHITE;
	if (max_or_min == 0)
		next_min_max = 1;
	else
		next_min_max = 0;

	if (depth == 0){
		if (max_or_min == 1)
			score = scoring(board, color);
		else
			score = scoring(board, otherColor);
		freeList(moves);
		freePositon(from);
		freePositon(to);
		return score;
	}

	//if there are no possible moves to the opponent, calculate the score of the current board. this is a terminal node.
	if ((ptr_moves == NULL) || (ptr_moves->m.currPos == NULL) || (cnt == 0)){
		freeList(moves);
		if (max_or_min == 1)
			score = scoring(board, color);
		else
			score = scoring(board, otherColor);
		freePositon(from);
		freePositon(to);
		return score;
	}
	if (max_or_min == 1) {
		score = -1000000;
		while (cnt>0){
			m = ptr_moves->m;
			from->x = m.currPos->x; from->y = m.currPos->y;
			ptr = (position*)m.currPos->next;
			to->x = ptr->x; to->y = ptr->y;

			type = typePromotion(&m, color);

			copyingBoard(board, Newboard);
			makeMove(Newboard, color, from, to, type);

			val = alphabetaPruning(otherColor, Newboard, depth - 1, alpha, beta, next_min_max);
			score = Max(score, val);

			alpha = Max(alpha, score);
			if (beta <= alpha){
				break;
			}
			ptr_moves = (listMoves*)ptr_moves->next;
			cnt--;
		}

		freeList(moves);
		freePositon(from);
		freePositon(to);
		return alpha;
	}
	else if (max_or_min == 0){
		score = 1000000;
		while (cnt>0){
			m = ptr_moves->m;
			from->x = m.currPos->x; from->y = m.currPos->y;
			ptr = (position*)m.currPos->next;
			to->x = ptr->x; to->y = ptr->y;

			type = typePromotion(&m, color);


			copyingBoard(board, Newboard);
			makeMove(Newboard, color, from, to, type);

			val = alphabetaPruning(otherColor, Newboard, depth - 1, alpha, beta, next_min_max);
			score = Min(score, val);

			beta = Min(beta, score);
			if (beta <= alpha){
				break;
			}

			ptr_moves = (listMoves*)ptr_moves->next;
			cnt--;
		}
		freeList(moves);
		freePositon(from);
		freePositon(to);
		return beta;
	}
	freeList(moves);
	freePositon(from);
	freePositon(to);
	return 0;
}


//this function gets the best score that calculated in the "alphabetaPruning" function.
//it's update "res" with the moves that have the best score.
void PruningMoves(char* color, char board[BOARD_SIZE][BOARD_SIZE], unsigned int depth, listMoves* res, int bestScore){
	listMoves* moves = myCalloc(sizeof(listMoves));

	allMoves(board, color, moves);
	int cnt = moves->cnt;
	listMoves* ptr_moves = moves;
	move m;
	int score;
	position* p1, *p2;

	while (cnt > 0){
		m = ptr_moves->m;
		score = alphabetaForGetScore(color, board, depth, &m);
		if (score == bestScore){
			p1 = (position*)m.currPos;
			p2 = (position*)m.currPos->next;
			addMove(res, p1, p2, m.currPos->cnt);
		}
		cnt--;
		ptr_moves = (listMoves*)ptr_moves->next;

	}
	freeList(moves);
}




int Max(int x, int y){
	if (x >= y)
		return x;
	else
		return y;
}

int Min(int x, int y){
	if (x <= y)
		return x;
	else
		return y;
}
//this function calculate the "best" depth.
int bestDepth(char board[BOARD_SIZE][BOARD_SIZE], char *color){
	unsigned int res[12];
	countDiscs(board, res);
	int maxPossibleMoves = 0;
	//res[0] = p; res[1] = b; res[2] = r; res[3] = n; res[4] = q; res[5] = k;
	//res[6] = P; res[7] = B; res[8] = R; res[9] = N; res[10] = Q; res[11] = K;
	maxPossibleMoves = (res[0] + res[6]) * 6 + (res[1] + res[7]) * 13 + (res[2] + res[8]) * 14 + (res[3] + res[9]) * 8 + (res[4] + res[10]) * 27 + (res[5] + res[11]) * 8;
	int depth = 2;
	while (1){
		if (power(maxPossibleMoves, depth)>power(10, 6)){
			break;
		}
		depth++;
	}

	return depth - 1;


}

int power(int a, int b){
	int res = 1;
	for (int i = 0; i < b; i++){
		res *= a;
	}
	return res;
}