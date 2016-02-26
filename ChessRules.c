#include "ChessRules.h"


//------------------This file include Chess Rules-------------------

//return 1 if move is Valid, else return 0
unsigned int checkIfMoveIsValid(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color){
	if ((checkValidPosition(from) == 0) || (checkValidPosition(to) == 0)){
		return 0;
	}
	char type;
	if (((from->x) >= 1) && ((from->y) >= 1)){
		type = board[from->x - 1][from->y - 1];
	}
	char ch = discType(type);
	int xTo = to->x, yTo = to->y, xFrom = from->x, yFrom = from->y;
	unsigned int ok = 0, empty, colorTo;
	empty = checkPositionEmpty(board, to);
	colorTo = checkColorPosition(board, to);
	char Newboard[BOARD_SIZE][BOARD_SIZE];
	copyingBoard(board, Newboard);




	//-----------pawn move-------------
	if (ch == 'm'){
		if ((prefix(color, WHITE) == 1)){
			if ((xTo == xFrom) && (yTo == yFrom + 1)){
				if (empty == 0){

					if (checkIfKingThreatened(board, from, to, color) == 1){
						ok = 1;
					}
				}
			}
			else if (((xTo == xFrom - 1) && (yTo == yFrom + 1)) || ((xTo == xFrom + 1) && (yTo == yFrom + 1))){
				if (colorTo == 1){

					if (checkIfKingThreatened(board, from, to, color) == 1){
						ok = 1;
					}
				}
			}
		}
		else if ((prefix(color, BLACK) == 1)){
			if ((xTo == xFrom) && (yTo == yFrom - 1)){
				if (empty == 0){

					if (checkIfKingThreatened(board, from, to, color) == 1){
						ok = 1;
					}
				}
			}
			else if (((xTo == xFrom - 1) && (yTo == yFrom - 1)) || ((xTo == xFrom + 1) && (yTo == yFrom - 1))){
				if (colorTo == 0){

					if (checkIfKingThreatened(board, from, to, color) == 1){
						ok = 1;
					}
				}
			}


		}
	}
	//-----------bishop move-------------
	else if (ch == 'b'){
		if (checkDiagForBishop(board, from, to, color, 'b') == 1){
			ok = 1;

		}

	}
	//-----------rook move-------------
	else if (ch == 'r'){
		if (checkRowForRook(board, from, to, color) == 1){
			ok = 1;
		}
		

	}
	//-----------knight move-------------
	else if (ch == 'n'){
		if (empty == 0 || ((prefix(color, WHITE) == 1) && (colorTo == 1)) || ((prefix(color, BLACK) == 1) && (colorTo == 0))){
			if ((to->x == from->x - 1) && (to->y == from->y + 2)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
			else if ((to->x == from->x - 2) && (to->y == from->y + 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
			else if ((to->x == from->x - 1) && (to->y == from->y - 2)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
			else if ((to->x == from->x - 2) && (to->y == from->y - 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
			else if ((to->x == from->x + 1) && (to->y == from->y + 2)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
			else if ((to->x == from->x + 2) && (to->y == from->y + 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
			else if ((to->x == from->x + 1) && (to->y == from->y - 2)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
			else if ((to->x == from->x + 2) && (to->y == from->y - 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1)
					ok = 1;
			}
		}
	}
	//-----------queen move-------------
	else if (ch == 'q'){
		if ((checkDiagForBishop(board, from, to, color, 'q') == 1) || (checkRowForRook(board, from, to, color) == 1)){

			ok = 1;
			
		}
	}
	//-----------king move-------------
	else if (ch == 'k'){
		if (empty == 0 || ((prefix(color, WHITE) == 1) && (colorTo == 1)) || ((prefix(color, BLACK) == 1) && (colorTo == 0))){
			if ((to->x == from->x - 1) || (to->x == from->x + 1)){
				if ((to->y == from->y - 1) || (to->y == from->y) || (to->y == from->y + 1)){
					if (checkIfKingThreatened(board, from, to, color) == 1){
						ok = 1;
					}
				}
			}
			else if (to->x == from->x){
				if ((to->y == from->y - 1) || (to->y == from->y + 1)){
					if (checkIfKingThreatened(board, from, to, color) == 1){
						ok = 1;
					}
				}
			}



		}

	}
	return ok;
}
// return 1 if king doesn't threatened by the opponent.
unsigned int checkIfKingThreatened(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color){
	unsigned int ok = 0;
	char Newboard[BOARD_SIZE][BOARD_SIZE];
	copyingBoard(board, Newboard);
	makeMove(Newboard, color, from, to, ' ');

	position* kingPos = myCalloc(sizeof(position));
	kingPos->x = 10;
	findKingPos(board, color, kingPos);
	if (kingPos->x == 10)//the king doesn't exist after the move.
		return 0;

	if ((prefix(color, BLACK) == 1) && (Check(Newboard, WHITE) != 1)){
		ok = 1;
	}
	else if ((prefix(color, WHITE) == 1) && (Check(Newboard, BLACK) != 1)){
		ok = 1;
	}
	freePositon(kingPos);
	return ok;
}

//check if "to" position is on a diag of "from" position and it's a legal move.
//return 1 if it's legal move, else 0.
unsigned int checkDiagForBishop(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color, char type){
	position *p = myCalloc(sizeof(position));
	p->x = to->x; p->y = to->y;
	int x = from->x;
	int y = from->y;
	unsigned int ok = 0, col;



	if ((to->x == x - 1) && (to->y == y + 1)){
		x = x - 1; y = y + 1;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
			col = checkColorPosition(board, p);
			if (legalMoveToPosColor(col, color) == 1){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;

				}
			}
		}
	}
	else if ((to->x == x + 1) && (to->y == y + 1)){
		x = x + 1; y = y + 1;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
			col = checkColorPosition(board, p);
			if (legalMoveToPosColor(col, color) == 1){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;

				}
			}
		}
	}
	else{
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x - 1; y = y + 1;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){
				col = checkColorPosition(board, p);
				if ((legalMoveToPosColor(col, color) == 1) && (to->x == p->x) && (to->y == p->y))
					if (checkIfKingThreatened(board, from, to, color) == 1){
						freePositon(p);
						return 1;
					}
				if (col != 2){
					break;
				}

			}
		}
		x = from->x;
		y = from->y;
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x + 1; y = y + 1;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){
				col = checkColorPosition(board, p);
				if ((legalMoveToPosColor(col, color) == 1) && (to->x == p->x) && (to->y == p->y)){
					if (checkIfKingThreatened(board, from, to, color) == 1){
						freePositon(p);
						return 1;
					}
				}
				if (col != 2){
					break;
				}

			}
		}
	}

	x = from->x;
	y = from->y;

	if ((to->x == x - 1) && (to->y == y - 1)){
		x = x - 1; y = y - 1;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
		col = checkColorPosition(board, p);
		if (legalMoveToPosColor(col, color) == 1){
			if (checkIfKingThreatened(board, from, to, color) == 1){
				freePositon(p);
				return 1;

			}
		}
		}
	}
	else if ((to->x == x + 1) && (to->y == y - 1)){
		x = x + 1; y = y - 1;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
			col = checkColorPosition(board, p);
			if (legalMoveToPosColor(col, color) == 1){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;

				}
			}
		}
	}
	else{
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x - 1; y = y - 1;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){
				col = checkColorPosition(board, p);
				if ((legalMoveToPosColor(col, color) == 1) && (to->x == p->x) && (to->y == p->y))
					if (checkIfKingThreatened(board, from, to, color) == 1){
						freePositon(p);
						return 1;
					}
				if (col != 2){
					break;
				}
			}
		}
		x = from->x;
		y = from->y;
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x + 1; y = y - 1;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){
				col = checkColorPosition(board, p);
				if ((legalMoveToPosColor(col, color) == 1) && (to->x == p->x) && (to->y == p->y))
					if (checkIfKingThreatened(board, from, to, color) == 1){
						freePositon(p);
						return 1;
					}
				if (col != 2){
					break;
				}

			}
		}

	}
	freePositon(p);
	return ok;
}

//check if the player with the input "color", can move to the pos with the colOfToPos color:
//0 is white, 1 is black, 2 is empty.
unsigned int legalMoveToPosColor(unsigned int colOfToPos, char* color){
	if (prefix(color, WHITE) == 1){
		if (colOfToPos != 0)
			return 1;
	}
	else {
		if (colOfToPos != 1)
			return 1;
	}
	return 0;
}





//check if "to" position is on a line/column of "from" position and it's a legal move. return 1 if it's ok, else 0.
unsigned int checkRowForRook(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color){
	position *p = (position*)myCalloc(sizeof(position));
	p->x = to->x; p->y = to->y;
	int x = from->x;
	int y = from->y;
	unsigned int col, col2;
	if ((prefix(color, WHITE) == 1)){
		col2 = 0;
	}
	else if ((prefix(color, BLACK) == 1)){
		col2 = 1;
	}

	if ((to->x == x - 1) && (to->y == y)){
		x = x - 1; y = y;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
			col = checkColorPosition(board, p);
			if ((col != 0) && (col2 == 0)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}

			else if ((col != 1) && (col2 == 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}
			else{
				freePositon(p);
				return 0;
			}
		}
	}
	else if ((to->x == x + 1) && (to->y == y)){
		x = x + 1; y = y;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
			col = checkColorPosition(board, p);
			if ((col != 0) && (col2 == 0)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}
			else if ((col != 1) && (col2 == 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}
			else{
				freePositon(p);
				return 0;
			}
		}
	}
	else if ((to->x == x) && (to->y == y + 1)){
		x = x; y = y + 1;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
			col = checkColorPosition(board, p);
			if ((col != 0) && (col2 == 0)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}
			else if ((col != 1) && (col2 == 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}
			else{
				freePositon(p);
				return 0;
			}
		}
	}
	else if ((to->x == x) && (to->y == y - 1)){
		x = x; y = y - 1;
		p->x = x; p->y = y;
		if (checkValidPosition(p) == 1){
			col = checkColorPosition(board, p);
			if ((col != 0) && (col2 == 0)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}
			else if ((col != 1) && (col2 == 1)){
				if (checkIfKingThreatened(board, from, to, color) == 1){
					freePositon(p);
					return 1;
				}
			}
			else{
				freePositon(p);
				return 0;
			}
		}
	}
	else{
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x - 1; y = y;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){
				col = checkColorPosition(board, p);
				if ((x == to->x) && (y == to->y)){
					if (col2 == 0){
						if (col != 0){
							if (checkIfKingThreatened(board, from, to, color) == 1){
								freePositon(p);
								return 1;
							}
						}
						else{
							break;
						}
					}
					if (col2 == 1){
						if (col != 1){
							if (checkIfKingThreatened(board, from, to, color) == 1){
								freePositon(p);
								return 1;
							}
						}
						else{
							break;
						}
					}
				}
				else{
					if (col != 2)
						break;

				}
			}
		}
		x = from->x;
		y = from->y;
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x + 1; y = y;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){

				col = checkColorPosition(board, p);
				if ((x == to->x) && (y == to->y)){
					if (col2 == 0){
						if (col != 0){
							if (checkIfKingThreatened(board, from, to, color) == 1){
								freePositon(p);
								return 1;
							}
						}
						else{
							break;
						}
					}
					if (col2 == 1){
						if (col != 1){
							if (checkIfKingThreatened(board, from, to, color) == 1){
								freePositon(p);
								return 1;
							}
						}
						else{
							break;
						}
					}
				}
				else{
					if (col != 2)
						break;

				}
			}
		}
		x = from->x;
		y = from->y;
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x; y = y - 1;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){
				col = checkColorPosition(board, p);
				if ((x == to->x) && (y == to->y)){
					if (col2 == 0){
						if (col != 0){
							if (checkIfKingThreatened(board, from, to, color) == 1){
								freePositon(p);
								return 1;
							}
						}
						else{
							break;
						}
					}
					if (col2 == 1){
						if (col != 1){
							if (checkIfKingThreatened(board, from, to, color) == 1){
								freePositon(p);
								return 1;
							}
						}
						else{
							break;
						}
					}
				}
				else{
					if (col != 2)
						break;

				}

			}
		}
		x = from->x;
		y = from->y;
		while (((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			x = x; y = y + 1;
			p->x = x; p->y = y;
			if (checkValidPosition(p) == 1){
				col = checkColorPosition(board, p);
				if ((x == to->x) && (y == to->y)){
					if (col2 == 0){
						if (col != 0){
							if (checkIfKingThreatened(board, from, to, color) == 1){
								freePositon(p);
								return 1;
							}
						}
						else{
							break;
						}
					}
					if (col2 == 1){
						if (col != 1){
							freePositon(p);
							return 1;
						}
						else{
							break;
						}
					}
				}
				else{
					if (col != 2)
						break;

				}
			}
		}
	}

	freePositon(p);
	return 0;
}
//the function updates the board with the move that entered
void makeMove(char board[BOARD_SIZE][BOARD_SIZE], char* color, position *from, position *to, char X){
	char type;
	if ((from->x >= 1) && (from->y >= 1)){
		type = board[from->x - 1][from->y - 1];
		unsigned int legalPromotion = 2;
		if ((type == 'm') && (to->y == 8)){
			type = X;
			legalPromotion = checkIfLegalX('m', X);
			if (X == ' ')
				type = 'q';
		}
		else if ((type == 'M') && (to->y == 1)){
			type = X;
			legalPromotion = checkIfLegalX('M', X);
			if (X == ' ')
				type = 'Q';
		}
		if (legalPromotion == 0){//not legal promotion ,TO DO!
			print_message(ILLEGAL_MOVE);
			//userTurn(board, color);

		}
		else{
			capture(board, from, to, color, type);
		}
	}

}


//check if it's legal promotiom. It's return 0 if it isn't legal and 1 if it's legal.
unsigned int checkIfLegalX(char type, char X){
	if (type == 'm' || type == 'M'){

		if ((X == 'b') || (X == 'B') || (X == 'r') || (X == 'R') || (X == 'q') || (X == 'Q') || (X == 'n') || (X == 'N') || (X == ' ')){
			return 1;
		}
	}


	return 0;
}

//the function simulates a capture and updated the board suitably
void capture(char board[BOARD_SIZE][BOARD_SIZE], position *from, position *to, char* color, char type){
	remove_disc(board, from->x, from->y); //remove the disc from place "from"
	remove_disc(board, to->x, to->y);//remove the old disc from place "to"
	set_disc(board, to->x, to->y, color, type, 1); //set the new disc in the "to" place

}


// If it is check return 1. The otherColor player's king is threatened by the color player.
unsigned int Check(char board[BOARD_SIZE][BOARD_SIZE], char* color){
	unsigned int col, ok = 0;
	char* otherColor, type;
	position* to = (position*)myCalloc(sizeof(position));
	position* otherColorkingPos = myCalloc(sizeof(position));
	if (strcmp(color, WHITE) == 0){
		otherColor = BLACK;
		col = 0;
	}
	else{
		otherColor = WHITE;
		col = 1;
	}

	findKingPos(board, otherColor, otherColorkingPos);
	int x = otherColorkingPos->x;
	int y = otherColorkingPos->y;
	int tmp;

	//up row

	tmp = whileLoopForCheck(2, 1, col, x, y, to, board, 'r', 'R');

	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;
	}

	//down row
	tmp = whileLoopForCheck(2, 0, col, x, y, to, board, 'r', 'R');
	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;
	}

	//left row
	tmp = whileLoopForCheck(0, 2, col, x, y, to, board, 'r', 'R');
	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;
	}
	//right row
	tmp = whileLoopForCheck(1, 2, col, x, y, to, board, 'r', 'R');
	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;
	}
	//left up diag
	tmp = whileLoopForCheck(0, 1, col, x, y, to, board, 'b', 'B');
	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;

	}
	//right up diag
	tmp = whileLoopForCheck(1, 1, col, x, y, to, board, 'b', 'B');
	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;

	}
	//left down diag
	tmp = whileLoopForCheck(0, 0, col, x, y, to, board, 'b', 'B');
	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;
	}

	//right down diag
	tmp = whileLoopForCheck(1, 0, col, x, y, to, board, 'b', 'B');
	if (tmp == 1){
		freePositon(to);
		freePositon(otherColorkingPos);
		return 1;
	}

	//#1 knight
	to->x = x - 1; to->y = y + 2;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}

	//#2 knight

	to->x = x - 2; to->y = y + 1;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}
	//#3 knight
	to->x = x - 1; to->y = y - 2;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}
	//#4 knight
	to->x = x - 2; to->y = y - 1;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}
	//#5 knight
	to->x = x + 1; to->y = y + 2;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}
	//#6 knight
	to->x = x + 2; to->y = y + 1;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}
	//#7 knight
	to->x = x + 1; to->y = y - 2;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}
	//#8 knight
	to->x = x + 2; to->y = y - 1;
	if (checkValidPosition(to) == 1){
		tmp = knight_check(to, board, col);
		if (tmp == 1){
			freePositon(to);
			freePositon(otherColorkingPos);
			return 1;
		}
	}
	//pawn case
	if (col == 0){
		to->x = x - 1; to->y = y - 1;
		if (checkValidPosition(to) == 1){
			type = board[to->x - 1][to->y - 1];
			if (type == 'm'){
				freePositon(to);
				freePositon(otherColorkingPos);
				return 1;
			}

		}
		to->x = x + 1; to->y = y - 1;
		if (checkValidPosition(to) == 1){
			type = board[to->x - 1][to->y - 1];
			if (type == 'm'){
				freePositon(to);
				freePositon(otherColorkingPos);
				return 1;
			}
		}
	}

	else if (col == 1){
		to->x = x - 1; to->y = y + 1;
		if (checkValidPosition(to) == 1){
			type = board[to->x - 1][to->y - 1];
			if (type == 'M'){
				freePositon(to);
				freePositon(otherColorkingPos);
				return 1;
			}
		}
		to->x = x + 1; to->y = y + 1;
		if (checkValidPosition(to) == 1){
			type = board[to->x - 1][to->y - 1];
			if (type == 'M'){
				freePositon(to);
				freePositon(otherColorkingPos);
				return 1;
			}
		}
	}




	freePositon(to);
	freePositon(otherColorkingPos);
	return ok;

}
//this function is for the check function, for not repeating on code.
//x_Minus_or_plus==1 is plus , x_Minus_or_plus==0 is minus, x_Minus_or_plus==2 is equal
int whileLoopForCheck(int x_Minus_or_plus, int y_Minus_or_plus, int col, int x, int y, position* to, char board[BOARD_SIZE][BOARD_SIZE], char b_or_r, char B_or_R){
	int toX, toY;
	int otherCol;
	char type;
	if (x_Minus_or_plus == 1){
		to->x = x + 1;
	}
	else if (x_Minus_or_plus == 0) {
		to->x = x - 1;
	}
	else{
		to->x = x;
	}
	if (y_Minus_or_plus == 1){
		to->y = y + 1;
	}
	else if (y_Minus_or_plus == 0){
		to->y = y - 1;
	}
	else{
		to->y = y;
	}

	unsigned int valid = checkValidPosition(to);
	if (valid != 1){
		return 0;
	}

	toX = to->x - 1; toY = to->y - 1;
	if ((toX >= 0) && (toY >= 0)){
		type = board[toX][toY];

		if ((col == 0) && (type == 'k')){
			return 1;
		}
		else if ((col == 1) && (type == 'K')){
			return 1;
		}
	}


	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		if (col == 0){
			otherCol = checkColorPosition(board, to);
			if (otherCol == 1)
				break;
			else if (otherCol == 0){
				type = board[to->x - 1][to->y - 1];
				if (type == b_or_r){
					return 1;
				}
				else if (type == 'q'){
					return 1;
				}

				else{
					break;
				}
			}
		}
		else if (col == 1){
			otherCol = checkColorPosition(board, to);
			if (otherCol == 0)
				break;
			else if (otherCol == 1){
				type = board[to->x - 1][to->y - 1];
				if (type == B_or_R){
					return 1;
				}
				else if (type == 'Q'){
					return 1;
				}

				else{
					break;
				}
			}
		}
		if (x_Minus_or_plus == 1){
			to->x++;
		}
		else if (x_Minus_or_plus == 0){
			to->x--;
		}
		if (y_Minus_or_plus == 1){
			to->y++;
		}
		else if (y_Minus_or_plus == 0){
			to->y--;
		}
	}
	return 0;
}

//this function is for the check function, for not repeating on code.
int knight_check(position* to, char board[BOARD_SIZE][BOARD_SIZE], int col){
	char type = board[to->x - 1][to->y - 1];
	if ((type == 'N') && (col == 1))
		return 1;
	else if ((type == 'n') && (col == 0))
		return 1;
	else{
		return 0;
	}
}



//update the position kingPos with the position on the board of the king with the "color" input.
void findKingPos(char board[BOARD_SIZE][BOARD_SIZE], char* color, position* kingPos){
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if ((prefix(color, WHITE) == 1) && (board[i][j] == WHITE_K)){
				kingPos->x = i + 1; kingPos->y = j + 1;
			}
			else if ((prefix(color, BLACK) == 1) && (board[i][j] == BLACK_K)){
				kingPos->x = i + 1; kingPos->y = j + 1;
			}
		}
	}
}




//return 1 if it's mate. else, retrun 0. The color player is winnig.
unsigned int isMate(char board[BOARD_SIZE][BOARD_SIZE], char* color){
	unsigned int col, valid, forCheck;
	char* otherColor;
	listMoves*moves = (listMoves*)myCalloc(sizeof(listMoves));
	position* p = (position*)myCalloc(sizeof(position));
	if (strcmp(color, WHITE) == 0){
		otherColor = BLACK;
	}
	else{
		otherColor = WHITE;

	}

	char Newboard[BOARD_SIZE][BOARD_SIZE];
	copyingBoard(board, Newboard);

	forCheck = Check(Newboard, color);
	if (forCheck == 0){//if it isn't check it isn't mate.
		freeList(moves);
		free(p);

		return 0;
	}

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			p->x = i + 1; p->y = j + 1;
			col = checkColorPosition(board, p);
			valid = checkValidPosition(p);
			if ((col == 1) && (prefix(color, WHITE) == 1) && (valid == 1)){
				if (movesFromPos(board, p, otherColor, moves, 0, 1) == 1){//there is possible move for the white player.


					freeList(moves);
					free(p);
					return 0;
				}
			}
			else if ((col == 0) && (prefix(color, BLACK) == 1) && (valid == 1)){
				if (movesFromPos(board, p, otherColor, moves, 0, 1) == 1){//there is possible move for the black player.

					freeList(moves);
					free(p);
					return 0;

				}
			}
		}
	}




	freeList(moves);
	free(p);
	return 1;


}




//if it's tie return 1, else return 0
unsigned int isTie(char board[BOARD_SIZE][BOARD_SIZE], char* color, listMoves* moves){
	unsigned int col, valid;
	//char type;
	position* p = (position*)myCalloc(sizeof(position));
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			p->x = i + 1; p->y = j + 1;
			col = checkColorPosition(board, p);
			valid = checkValidPosition(p);
			if ((col == 0) && (prefix(color, WHITE) == 1) && (valid == 1)){
				if (movesFromPos(board, p, color, moves, 1, 0) == 1){//there is possible move for the white player, so it's not a tie
					freePositon(p);
					return 0;
				}
			}
			else if ((col == 1) && (prefix(color, BLACK) == 1) && (valid == 1)){
				if (movesFromPos(board, p, color, moves, 1, 0) == 1){//there is possible move for the black player, so it's not a tie
					freePositon(p);
					return 0;
				}
			}
		}
	}
	freePositon(p);
	return 1;//it's a tie




}


//return 1 if exist a possible move to the player (that has the input color).
unsigned int movesFromPos(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate){
	int x = from->x - 1;
	int y = from->y - 1;
	char type=' ';
	if ((x >= 0) && (y >= 0) && (x<=7) &&(y<=7)){
		type = board[from->x - 1][from->y - 1];
		char disc = discType(type);
		if (disc == 'm'){
			if (PawnPossibleMoves(board, from, color, moves, isTie, isMate) == 1)
				return 1;
		}
		else if (disc == 'b'){
			if (BitshopPossibleMoves(board, from, color, moves, isTie, isMate) == 1)
				return 1;
		}
		else if (disc == 'r'){
			if (RookPossibleMoves(board, from, color, moves, isTie, isMate) == 1)
				return 1;
		}
		else if (disc == 'n'){
			if (KnightPossibleMoves(board, from, color, moves, isTie, isMate) == 1)
				return 1;
		}
		else if (disc == 'q'){
			if (QueenPossibleMoves(board, from, color, moves, isTie, isMate) == 1)
				return 1;
		}
		else if (disc == 'k'){
			if (KingPossibleMoves(board, from, color, moves, isTie, isMate) == 1)
				return 1;
		}
	}
	return 0;
}

// this function update all the possible moves of white player or black player in the input "moves".
void allMoves(char board[BOARD_SIZE][BOARD_SIZE], char* color, listMoves* moves){

	position* from = myCalloc(sizeof(position));
	unsigned int tmp, valid;
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			from->x = i + 1; from->y = j + 1;
			valid = checkValidPosition(from);
			if ((prefix(color, WHITE) == 1) && (checkColorPosition(board, from) == 0) && (valid == 1)){

				tmp = movesFromPos(board, from, WHITE, moves, 0, 0);
			}

			else if ((prefix(color, BLACK) == 1) && (checkColorPosition(board, from) == 1) && (valid == 1)){
				tmp = movesFromPos(board, from, BLACK, moves, 0, 0);

			}
		}

	}
	if (tmp == 0){
		//do nothing
	}
	freePositon(from);
}







//check if the knight in position "from" has possible moves. return 1 if at least one move exist.
unsigned int KnightPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate){
	position* to = (position*)myCalloc(sizeof(position));
	unsigned int ok = 0, ok2 = 0, col2;
	listMoves* currMove = moves;
	unsigned int cnt = moves->cnt;
	char Newboard[BOARD_SIZE][BOARD_SIZE];
	copyingBoard(board, Newboard);
	if ((prefix(color, WHITE) == 1)){
		col2 = 0;
	}
	else if ((prefix(color, BLACK) == 1)){
		col2 = 1;
	}


	while (cnt > 0){
		currMove = (listMoves*)currMove->next;
		cnt--;
	}


	//case #1



	to->x = from->x - 1;
	to->y = from->y + 2;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	//case #2

	to->x = from->x - 2; to->y = from->y + 1;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	//case #3

	to->x = from->x - 1; to->y = from->y - 2;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	//case #4

	to->x = from->x - 2; to->y = from->y - 1;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	//case #5

	to->x = from->x + 1; to->y = from->y + 2;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	//case #6

	to->x = from->x + 2; to->y = from->y + 1;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	//case #7

	to->x = from->x + 1; to->y = from->y - 2;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	//case #8

	to->x = from->x + 2; to->y = from->y - 1;

	ok = forKnight(board, from, to, color, moves);
	if (ok == 1){
		ok2 = 1;
		if (isTie == 1){
			free(to);
			return 1;
		}
		if (isMate == 1){
			if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
				free(to);
				return 1;
			}
		}
	}

	freePositon(to);
	return ok2;
}


//this function is for the KnightPossibleMoves function.
unsigned int forKnight(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color, listMoves* moves){
	unsigned int empty, colorTo, ok = 0;
	if (checkValidPosition(to) == 1){
		empty = checkPositionEmpty(board, to);
		colorTo = checkColorPosition(board, to);
		if (empty == 0 || ((prefix(color, WHITE) == 1) && (colorTo == 1)) || ((prefix(color, BLACK) == 1) && (colorTo == 0))){
			if (checkIfKingThreatened(board, from, to, color) == 1){
				addMove(moves, from, to, 10);
				ok = 1;
			}

		}
	}
	return ok;
}


//check if the pawn in position "from" has possible moves. return 1 if at least one move exist.
unsigned int PawnPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate){
	position* to = (position*)myCalloc(sizeof(position));
	char Newboard[BOARD_SIZE][BOARD_SIZE];
	copyingBoard(board, Newboard);

	unsigned int col, ok = 0, needReturn = 0;
	if (prefix(color, WHITE) == 1){
		col = 0;
	}
	else{
		col = 1;
	}



	//case #1
	if (col == 0){
		to->x = from->x; to->y = from->y + 1;
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){

				needReturn = 1;
			}

			else if (from->y == 7){
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 1) == 0){

						needReturn = 1;

					}

				}

				addMove(moves, from, to, 1);//promotion to queen
				addMove(moves, from, to, 2);//promotion to rook
				addMove(moves, from, to, 3);//promotion to knight
				addMove(moves, from, to, 4);//promotion to bishop
			}
			else{

				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 0) == 0){

						needReturn = 1;

					}

				}

				addMove(moves, from, to, 10);
			}
			ok = 1;
		}

	}

	else if (col == 1){
		to->x = from->x; to->y = from->y - 1;
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){

				needReturn = 1;
			}

			else if (from->y == 2){
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 1) == 0){

						needReturn = 1;

					}

				}

				addMove(moves, from, to, 1);//promotion to queen
				addMove(moves, from, to, 2);//promotion to rook
				addMove(moves, from, to, 3);//promotion to knight
				addMove(moves, from, to, 4);//promotion to bishop
			}
			else{
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 0) == 0){

						needReturn = 1;
					}

				}
				addMove(moves, from, to, 10);
			}
			ok = 1;
		}

	}


	if ((col == 0) && (needReturn == 0)){
		//case #2
		to->x = from->x - 1; to->y = from->y + 1;
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){

				needReturn = 1;
			}

			else if (from->y == 7){
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 1) == 0){

						needReturn = 1;
					}

				}
				addMove(moves, from, to, 1);//promotion to queen
				addMove(moves, from, to, 2);//promotion to rook
				addMove(moves, from, to, 3);//promotion to knight
				addMove(moves, from, to, 4);//promotion to bishop
			}
			else{
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 0) == 0){
	
						needReturn = 1;
					}

				}
				addMove(moves, from, to, 10);
			}
			ok = 1;
			
		}

		//case #3
		if (needReturn == 0){
			to->x = from->x + 1; to->y = from->y + 1;
			if (checkIfMoveIsValid(board, from, to, color) == 1){
				if (isTie == 1){
	
					needReturn = 1;
				}

				else if (from->y == 7){
					if (isMate == 1){
						if (OneMoveIsMate(board, from, to, col, color, 1) == 0){
							needReturn = 1;
						}

					}
					addMove(moves, from, to, 1);//promotion to queen
					addMove(moves, from, to, 2);//promotion to rook
					addMove(moves, from, to, 3);//promotion to knight
					addMove(moves, from, to, 4);//promotion to bishop
				}
				else{
					if (isMate == 1){
						if (OneMoveIsMate(board, from, to, col, color, 0) == 0){
							needReturn = 1;
						}

					}
					addMove(moves, from, to, 10);
				}
				ok = 1;
			}
		}


	}
	else if ((col == 1) && (needReturn == 0)){
		//case #4
		to->x = from->x + 1; to->y = from->y - 1;
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				needReturn = 1;
			}

			else if (from->y == 2){
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 1) == 0){
						needReturn = 1;
					}

				}
				addMove(moves, from, to, 1);//promotion to queen
				addMove(moves, from, to, 2);//promotion to rook
				addMove(moves, from, to, 3);//promotion to knight
				addMove(moves, from, to, 4);//promotion to bishop
			}
			else{
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col, color, 0) == 0){
						needReturn = 1;
					}

				}
				addMove(moves, from, to, 10);
			}
			ok = 1;
	
		}
		//case #5
		if (needReturn == 0){
			to->x = from->x - 1; to->y = from->y - 1;
			if (checkIfMoveIsValid(board, from, to, color) == 1){
				if (isTie == 1){
					needReturn = 1;
				}

				else if (from->y == 2){
					if (isMate == 1){
						if (OneMoveIsMate(board, from, to, col, color, 1) == 0){
							//free(to);
							//return 1;
							needReturn = 1;
						}

					}
					addMove(moves, from, to, 1);//promotion to queen
					addMove(moves, from, to, 2);//promotion to rook
					addMove(moves, from, to, 3);//promotion to knight
					addMove(moves, from, to, 4);//promotion to bishop
				}
				else{
					if (isMate == 1){
						if (OneMoveIsMate(board, from, to, col, color, 0) == 0){
							needReturn = 1;
						}

					}
					addMove(moves, from, to, 10);
				}
				ok = 1;

			}
		}


	}
	freePositon(to);
	return ok;
}

//return 0 if it isn't mate.
unsigned int OneMoveIsMate(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, unsigned int col, char* color, unsigned int promotion){
	char Newboard[BOARD_SIZE][BOARD_SIZE];
	copyingBoard(board, Newboard);
	char type = ' ', *otherCol;
	otherCol = (col == 0) ? BLACK : WHITE;

	if (promotion == 1){
		type = (col == 0) ? 'q' : 'Q';
		makeMove(Newboard, color, from, to, type);
		if (Check(Newboard, otherCol) == 0){//not check
			return 0;

		}
		type = (col == 0) ? 'r' : 'R';
		copyingBoard(board, Newboard);
		makeMove(Newboard, color, from, to, type);
		if (Check(Newboard, otherCol) == 0){//not check
			return 0;

		}
		type = (col == 0) ? 'n' : 'N';
		copyingBoard(board, Newboard);
		makeMove(Newboard, color, from, to, type);
		if (Check(Newboard, otherCol) == 0){//not check
			return 0;

		}
		type = (col == 0) ? 'b' : 'B';
		copyingBoard(board, Newboard);
		makeMove(Newboard, color, from, to, type);
		if (Check(Newboard, otherCol) == 0){//not check
			return 0;

		}
	}
	else{
		makeMove(Newboard, color, from, to, type);
		if (Check(Newboard, otherCol) == 0){//not check
			return 0;

		}
	}

	return 1;



}




//check if the king in position "from" has possible moves. return 1 if at least one move exist.
unsigned int KingPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate){
	position* to = (position*)myCalloc(sizeof(position));
	unsigned int col2, ok = 0;
	if ((prefix(color, WHITE) == 1)){
		col2 = 0;
	}
	else if ((prefix(color, BLACK) == 1)){
		col2 = 1;
	}


	to->x = from->x - 1;
	//case #1
	to->y = from->y + 1;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}
	//case #2
	to->y = from->y;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}

	//case #3
	to->y = from->y - 1;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}
	to->x = from->x;

	//case #4
	to->y = from->y + 1;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}

	//case #5
	to->y = from->y - 1;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}

	to->x = from->x + 1;

	//case #6
	to->y = from->y + 1;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}
	//case #7
	to->y = from->y;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}

	//case #8
	to->y = from->y - 1;
	if (checkValidPosition(to) == 1){
		if (checkIfMoveIsValid(board, from, to, color) == 1){
			if (isTie == 1){
				free(to);
				return 1;
			}
			if (isMate == 1){
				if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
					free(to);
					return 1;
				}
			}
			addMove(moves, from, to, 10);
			ok = 1;
		}
	}
	freePositon(to);
	return ok;
}

//check if the bitshop in position "from" has possible moves. return 1 if at least one move exist.
unsigned int BitshopPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate){
	unsigned int col, col2;
	if ((prefix(color, WHITE) == 1)){
		col2 = 0;
	}
	else if ((prefix(color, BLACK) == 1)){
		col2 = 1;
	}
	if (col2 == 0){
		//do nothig
	}
	position* to = (position*)myCalloc(sizeof(position));
	unsigned int ok = 0;
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->x--; to->y++;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForBishop(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}

				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
			}
			if (col != 2)
				break;
			
		}
	}
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->x--; to->y--;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForBishop(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}

	
				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
				
			}
			if (col != 2)
				break;
		}
	}
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->x++; to->y++;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForBishop(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}


				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
			}
			if (col != 2)
				break;
		}
	}
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->x++; to->y--;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForBishop(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}

				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
				
			}
			if (col != 2)
				break;
		}
	}
	freePositon(to);
	return ok;
}


//this function is for BitshopPossibleMoves function.
unsigned int checkForBishop(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color){
	position *p = myCalloc(sizeof(position));
	p->x = to->x; p->y = to->y;

	unsigned int col;

	col = checkColorPosition(board, p);
	if (legalMoveToPosColor(col, color) == 1){
		if (checkIfKingThreatened(board, from, to, color) == 1){
			freePositon(p);
			return 1;

		}
	}
	freePositon(p);
	return 0;

}

//check if the rook in position "from" has possible moves. return 1 if at least one move exist.
unsigned int RookPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate){
	position* to = (position*)myCalloc(sizeof(position));
	unsigned int col, col2;
	if ((prefix(color, WHITE) == 1)){
		col2 = 0;
	}
	else if ((prefix(color, BLACK) == 1)){
		col2 = 1;
	}
	if (col2 == 0){

	}
	unsigned int ok = 0;
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->x--;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForRook(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}
	
				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
			}
			if (col != 2)
				break;
		}
	}
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->x++;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForRook(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}
				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
				
			}
			if (col != 2)
				break;
		}
	}
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->y++;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForRook(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}
				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
			}
			if (col != 2)
				break;
		}
	}
	to->x = from->x; to->y = from->y;
	while (((to->x >= 1) && (to->x <= 8) && (to->y >= 1) && (to->y <= 8))){
		to->y--;
		if (checkValidPosition(to) == 1){
			col = checkColorPosition(board, to);
			if (checkForRook(board, from, to, color) == 1){
				if (isTie == 1){
					free(to);
					return 1;
				}
				if (isMate == 1){
					if (OneMoveIsMate(board, from, to, col2, color, 0) == 0){
						free(to);
						return 1;
					}
				}
				addMove(moves, from, to, 10);
				ok = 1;
				if (col != 2)
					break;
			}
			if (col != 2)
				break;
		}
	}
	freePositon(to);
	return ok;
}

//this function is for the "RookPossibleMoves" function.
unsigned int checkForRook(char board[BOARD_SIZE][BOARD_SIZE], position* from, position* to, char* color){
	position *p = (position*)myCalloc(sizeof(position));
	p->x = to->x; p->y = to->y;
	unsigned int col, col2;
	if ((prefix(color, WHITE) == 1)){
		col2 = 0;
	}
	else if ((prefix(color, BLACK) == 1)){
		col2 = 1;
	}


	col = checkColorPosition(board, p);
	if ((col != 0) && (col2 == 0)){
		if (checkIfKingThreatened(board, from, to, color) == 1){
			freePositon(p);
			return 1;
		}
	}
	else if ((col != 1) && (col2 == 1)){
		if (checkIfKingThreatened(board, from, to, color) == 1){
			freePositon(p);
			return 1;
		}
	}
	else{
		freePositon(p);
		return 0;
	}
	freePositon(p);
	return 0;
}



//check if the queen in position "from" has possible moves. return 1 if at least one move exist.
unsigned int QueenPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], position* from, char* color, listMoves* moves, unsigned int isTie, unsigned int isMate){
	unsigned int diag = BitshopPossibleMoves(board, from, color, moves, isTie, isMate);
	if (isTie == 1){
		return 1;
	}
	if (isMate == 1){
		if (diag == 1)
			return 1;
	}

	unsigned int row = RookPossibleMoves(board, from, color, moves, isTie, isMate);
	if (isMate == 1){
		if (row == 1)
			return 1;
	}

	if ((diag == 1) || (row == 1)){
		return 1;
	}
	return 0;




}

//this function return the right promotion of a pawn.
char typePromotion(move* m, char* color){
	char type = ' ';
	if (m->currPos->cnt == 1)
		type = ' ';
	else if (m->currPos->cnt == 2)
	{
		if (prefix(color, WHITE) == 1)
			type = 'r';
		else
			type = 'R';
	}
	else if (m->currPos->cnt == 3)
	{
		if (prefix(color, WHITE) == 1)
			type = 'n';
		else
			type = 'N';
	}
	else if (m->currPos->cnt == 4)
	{
		if (prefix(color, WHITE) == 1)
			type = 'b';
		else
			type = 'B';
	}
	return type;
}

