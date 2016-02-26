#include "GameFlow.h"


//------------------This file include settings and game states------------------- 




// the function convets char from a-j to number from 1-10
int num_cordinate(char x){
	switch (x){
	case 'a':{
		return 1;
		break;
	}
	case 'b':{
		return 2;
		break;
	}
	case 'c':{
		return 3;
		break;
	}
	case 'd':{
		return 4;
		break;
	}
	case 'e':{
		return 5;
		break;
	}
	case 'f':{
		return 6;
		break;
	}
	case 'g':{
		return 7;
		break;
	}
	case 'h':{
		return 8;
		break;
	}

	}
	return -1;
}

// the function convets number from 1-10 to char from a-j
char char_cordinate(int x){
	switch (x){
	case 1:{
		return 'a';
		break;
	}
	case 2:{
		return 'b';
		break;
	}
	case 3:{
		return 'c';
		break;
	}
	case 4:{
		return 'd';
		break;
	}
	case 5:{
		return 'e';
		break;
	}
	case 6:{
		return 'f';
		break;
	}
	case 7:{
		return 'g';
		break;
	}
	case 8:{
		return 'h';
		break;
	}

	}
	return -1;
}
//this function input is type of disc in char*, it's return the char that present the disc type.
char discChar(char* type){
	if (prefix(type, "king") == 1)
		return 'k';
	else if (prefix(type, "queen") == 1)
		return 'q';
	else if (prefix(type, "rook") == 1)
		return 'r';
	else if (prefix(type, "knight") == 1)
		return 'n';
	else if (prefix(type, "bishop") == 1)
		return 'b';
	else if (prefix(type, "pawn") == 1)
		return 'm';
	return ' ';

}

// remove spaces until we get to the next argument
char* next_argument(char *input_ptr){
	char c = input_ptr[0];
	while (isspace(c)){
		input_ptr++;
		c = input_ptr[0];
	}
	return input_ptr;
}

//help function for print board that prints line.
void print_line(){
	int i;
	printf("  |");
	for (i = 1; i < BOARD_SIZE * 4; i++){
		printf("-");
	}
	printf("|\n");
}

// the function prints the current board.
void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i, j;
	print_line();
	for (j = BOARD_SIZE - 1; j >= 0; j--)
	{
		printf((j < 8 ? " %d" : "%d"), j + 1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		print_line();
	}
	printf("   ");
	for (j = 0; j < BOARD_SIZE; j++){
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
}

//the function initialize the board.
void init_board(char board[BOARD_SIZE][BOARD_SIZE]){
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if (j == 7){ //BLACK DISCS
				if ((i == 0) || (i == 7)){
					board[i][j] = BLACK_R;
				}
				else if ((i == 1) || (i == 6)){
					board[i][j] = BLACK_N;

				}
				else if ((i == 2) || (i == 5)){
					board[i][j] = BLACK_B;

				}
				else if ((i == 3)){
					board[i][j] = BLACK_Q;

				}
				else if ((i == 4)){
					board[i][j] = BLACK_K;

				}

			}
			else if (j == 6){
				board[i][j] = BLACK_P;

			}

			else if (j == 0){ //WHITE DISCS
				if ((i == 0) || (i == 7)){
					board[i][j] = WHITE_R;
				}
				else if ((i == 1) || (i == 6)){
					board[i][j] = WHITE_N;

				}
				else if ((i == 2) || (i == 5)){
					board[i][j] = WHITE_B;

				}
				else if ((i == 3)){
					board[i][j] = WHITE_Q;

				}
				else if ((i == 4)){
					board[i][j] = WHITE_K;

				}
			}
			else if (j == 1){
				board[i][j] = WHITE_P;

			}

			else{
				board[i][j] = EMPTY;
			}
		}
	}
}

// the function updates the depth of the minimax in the upcoming game. 1 by default.
unsigned int depth_update(unsigned int x, unsigned int depth){ //we convert the char to int before we send it to the function
	if ((x < 1) || (x > 4)){
		print_message(WRONG_MINIMAX_DEPTH);
		return depth;
	}
	else{
		depth = x;
		return x;
	}
}

// the function updates the color of the user in the upcoming game. white by default.
char* color_update(char *setcolor, char *color){
	if (strcmp(WHITE, setcolor) == 0)
		color = WHITE;
	else if (strcmp(BLACK, setcolor) == 0)
		color = BLACK;
	return color;
}

// function removes all the discs from the board.
void clear(char board[BOARD_SIZE][BOARD_SIZE]){
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			board[i][j] = EMPTY;
}

//the function removes one specific disc from the board.
void remove_disc(char board[BOARD_SIZE][BOARD_SIZE], unsigned int x, unsigned int y){ //we convert the char to int before we send it to the function
	if ((x < 1) || (x > 8) || (y < 1) || (y > 8)){
		print_message(WRONG_POSITION);
	}
	else
		board[x - 1][y - 1] = EMPTY;
}

//the function puts a disc in the board in aspecific place, color and type. *** if it's setting game = 0, if it's game, game=1 ***
void set_disc(char board[BOARD_SIZE][BOARD_SIZE], unsigned int x, unsigned int y, char *color, char type, unsigned int game){ //we convert the char to int before we send it to the function
	char disc_type = discType(type);
	unsigned int check = checkValidSetType(board, type, color);

	if ((x < 1) || (x > 8) || (y < 1) || (y > 8)){
		print_message(WRONG_POSITION);
	}
	else if ((check == 2) && (game == 0)){
		print_message(NO_PIECE);
	}

	else{
		if (strcmp(color, WHITE) == 0){
			if (disc_type == 'm')
				board[x - 1][y - 1] = WHITE_P;
			else if (disc_type == 'b')
				board[x - 1][y - 1] = WHITE_B;
			else if (disc_type == 'r')
				board[x - 1][y - 1] = WHITE_R;
			else if (disc_type == 'n')
				board[x - 1][y - 1] = WHITE_N;
			else if (disc_type == 'q')
				board[x - 1][y - 1] = WHITE_Q;
			else if (disc_type == 'k')
				board[x - 1][y - 1] = WHITE_K;
		}
		else{
			if (disc_type == 'm')
				board[x - 1][y - 1] = BLACK_P;
			else if (disc_type == 'b')
				board[x - 1][y - 1] = BLACK_B;
			else if (disc_type == 'r')
				board[x - 1][y - 1] = BLACK_R;
			else if (disc_type == 'n')
				board[x - 1][y - 1] = BLACK_N;
			else if (disc_type == 'q')
				board[x - 1][y - 1] = BLACK_Q;
			else if (disc_type == 'k')
				board[x - 1][y - 1] = BLACK_K;
		}
	}
}


//the function checks if the board is valid before the start of the game.
int valid_board(char board[BOARD_SIZE][BOARD_SIZE]){
	int valid = 1;// we assume that the board is not valid
	unsigned int* countdiscs = myCalloc(sizeof(int) * 12);
	countDiscs(board, countdiscs);
	unsigned int checkEmpty = checkEmptyBoard(countdiscs);
	if (checkEmpty == 1){ // the board is empty
		print_message(WROND_BOARD_INITIALIZATION);
	}
	else if (checkEmpty == 2){ // there are discs of only one color
		print_message(WROND_BOARD_INITIALIZATION);
	}

	else
		valid = 0;//the board is valid.
	free(countdiscs);
	return valid;
}

//check if the board is empty. if empty return 1, else if just one color return 2, else return 0;
unsigned int checkEmptyBoard(unsigned int arr[]){
	unsigned int checkWhite = 0, checkBlack = 0;
	unsigned int p = arr[0], b = arr[1], r = arr[2], n = arr[3], q = arr[4], k = arr[5];
	unsigned int P = arr[6], B = arr[7], R = arr[8], N = arr[9], Q = arr[10], K = arr[11];
	if ((p == 0) && (b == 0) && (r == 0) && (n == 0) && (q == 0) && (k == 0))//check if there are no white discs 
		checkWhite = 1;
	if ((P == 0) && (B == 0) && (R == 0) && (N == 0) && (Q == 0) && (K == 0))//check if there are no black discs 
		checkBlack = 1;
	if ((checkBlack == 1) && (checkWhite == 1)){//the board is empty
		return 1;
	}
	else if ((checkBlack == 1) || (checkWhite == 1)){//there is just one color on the board
		return 2;
	}
	else{ //there are white and black discs on the board
		return 0;
	}
}

//check the disc type and return it.
char discType(char type){
	char disc_type = ' ';
	if ((type == 'm') || (type == 'M'))
		disc_type = 'm';
	else if ((type == 'b') || (type == 'B'))
		disc_type = 'b';
	else if ((type == 'r') || (type == 'R'))
		disc_type = 'r';
	else if ((type == 'n') || (type == 'N'))
		disc_type = 'n';
	else if ((type == 'q') || (type == 'Q'))
		disc_type = 'q';
	else if ((type == 'k') || (type == 'K'))
		disc_type = 'k';
	return disc_type;
}
//this function is for the case of promotion a pawn, return the right char.
char promotionPawn(char* type, char* color){
	if (prefix(type, "queen") == 1)
		if (prefix(color, WHITE) == 1)
			return 'q';
		else
			return 'Q';
	else if (prefix(type, "bishop") == 1)
		if (prefix(color, WHITE) == 1)
			return 'b';
		else
			return 'B';
	else if (prefix(type, "rook") == 1)
		if (prefix(color, WHITE) == 1)
			return 'r';
		else
			return 'R';
	else if (prefix(type, "knight") == 1)
		if (prefix(color, WHITE) == 1)
			return 'n';
		else
			return 'N';
	else
		return '0';
}

//this function counts the number of discs from each type.
void countDiscs(char board[BOARD_SIZE][BOARD_SIZE], unsigned int res[12]){
	int i, j;
	int  P = 0, B = 0, R = 0, N = 0, Q = 0, K = 0, p = 0, b = 0, r = 0, n = 0, q = 0, k = 0;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++){
			switch (board[i][j]){
			case BLACK_P:{
				P++;
				break;
			}
			case BLACK_B:{
				B++;
				break;
			}
			case BLACK_R:{
				R++;
				break;
			}
			case BLACK_N:{
				N++;
				break;
			}
			case BLACK_Q:{
				Q++;
				break;
			}
			case BLACK_K:{
				K++;
				break;
			}
			case WHITE_P:{
				p++;
				break;
			}
			case WHITE_B:{
				b++;
				break;
			}
			case WHITE_R:{
				r++;
				break;
			}
			case WHITE_N:{
				n++;
				break;
			}
			case WHITE_Q:{
				q++;
				break;
			}
			case WHITE_K:{
				k++;
				break;
			}
			}
		}
	res[0] = p; res[1] = b; res[2] = r; res[3] = n; res[4] = q; res[5] = k;
	res[6] = P; res[7] = B; res[8] = R; res[9] = N; res[10] = Q; res[11] = K;
	
}

//the function checks if the type the user wants to give to a tool is valid.
unsigned int checkValidSetType(char board[BOARD_SIZE][BOARD_SIZE], char type, char* color){
	unsigned int cntDiscs[12] = { 0 };
	countDiscs(board, cntDiscs);
	if (prefix(color, "white") == 1){
		switch (type){
		case 'm':{
			if (cntDiscs[0] >= 8)
				return 2;
			else
				return 0;
		}
		case 'b':{
			if (cntDiscs[1] >= 2)
				return 2;
			else
				return 0;
		}
		case 'r':{
			if (cntDiscs[2] >= 2)
				return 2;
			else
				return 0;
		}
		case 'n':{
			if (cntDiscs[3] >= 2)
				return 2;
			else
				return 0;
		}
		case 'q':{
			if (cntDiscs[4] >= 1)
				return 2;
			else
				return 0;
		}
		case 'k':{
			if (cntDiscs[5] >= 1)
				return 2;
			else
				return 0;
		}
		}
	}
	else if (prefix(color, "black") == 1){
		switch (type){
		case 'm':{
			if (cntDiscs[6] >= 8)
				return 2;
			else
				return 0;
		}
		case 'b':{
			if (cntDiscs[7] >= 2)
				return 2;
			else
				return 0;
		}
		case 'r':{
			if (cntDiscs[8] >= 2)
				return 2;
			else
				return 0;
		}
		case 'n':{
			if (cntDiscs[9] >= 2)
				return 2;
			else
				return 0;
		}
		case 'q':{
			if (cntDiscs[10] >= 1)
				return 2;
			else
				return 0;
		}
		case 'k':{
			if (cntDiscs[11] >= 1)
				return 2;
			else
				return 0;
		}
		}
	}

	return 0;
}

//the function gets input from the user char by char.
char* getInput()
{
	char *input, ch;
	int inputMaxSize = 10, inputCurSize = 0;
	input = myCalloc(sizeof(char)*inputMaxSize);
	while ((ch = getchar()) != '\n'){
		input[inputCurSize++] = ch;
		if (inputCurSize == inputMaxSize){
			input = myRealloc(input, sizeof(char)*inputMaxSize * 2);
			inputMaxSize *= 2;
		}
	}
	input[inputCurSize++] = '\0';
	return myRealloc(input, sizeof(char)*inputCurSize);
	
}

//realloc function that  free the memory if the realloc fails.
void * myRealloc(void * ptr, size_t size)
{
	void *newMem = realloc(ptr, size);
	if (newMem == NULL)
	{
		printf("Error: standard function myRealloc has failed");
		exit(3);
	}
	else
		return newMem;
}

//malloc function that increase the allocation counter and free the memory if the allocation fails.
void * myMalloc(size_t size)
{
	void *newMem = malloc(size);
	if (newMem == NULL)
	{
		printf("Error: standard function myMalloc has failed");
		exit(3);
	}
	else
		return newMem;
}

//calloc function that increase the allocation counter and free the memory if the allocation fails.
void * myCalloc(size_t size)
{
	void *newMem = calloc(1, size);
	if (newMem == NULL)
	{
		printf("Error: standard function Calloc has failed");
		exit(3);
	}
	else
		return newMem;
}

//free memory function that decrease the allocation counter.
void myFree(void * ptr)
{
	free(ptr);
	
}
//the function free alist of moves.
void freeList(listMoves* current_head){
	listMoves* node_remove;
	int cnt;
	if (current_head != NULL)
		cnt = current_head->cnt;
	while (current_head != NULL)
	{
		freeMove(&(current_head->m));
		node_remove = current_head;
		current_head = (listMoves*)(current_head->next);
		myFree(node_remove);
		node_remove = NULL;
		cnt--;
		if (cnt == 0)
			break;
	}
}



//the function free a move.
void freeMove(move* current_head){
	if (current_head != NULL){
		freePositon(current_head->currPos);
	}
}



//the function free position.
void freePositon(position* current_head){
	position* node_remove;
	while (current_head != NULL)
	{
		node_remove = current_head;
		current_head = (position*)(current_head->next);
		myFree(node_remove);
		node_remove = NULL;
	}
}

// the function checks if a string is a perfix of another string.
int prefix(char *pre, char *str)
{
	int t = strncmp(pre, str, strlen(str));
	if (t == 0)
		return 1;
	else return 0;
}


//increase listMoves by one
void increaseListMoves(listMoves* moves){
	listMoves* currMove = moves;
	unsigned int cnt = moves->cnt;
	while (cnt > 0){
		currMove = (listMoves*)currMove->next;
		cnt--;
	}

	currMove = myCalloc(sizeof(listMoves));
	currMove->m.currPos = myCalloc(sizeof(position));
	moves->cnt++;



}

//initialize new move
listMoves* initMoves(listMoves *moves){
	moves->next = myCalloc(sizeof(listMoves));
	position* ptr;
	moves->m.currPos = myCalloc(sizeof(position));
	ptr = moves->m.currPos;
	ptr->next = myCalloc(sizeof(position));
	moves->m.currPos->cnt = 0;
	moves->m.cnt = 0;
	moves->cnt = 0;
	return moves;
}

//this function add move to the moves list.
void addMove(listMoves* moves, position* from, position* to, unsigned int depth){

	listMoves* currMove = moves;
	position* ptr_currPos;
	unsigned int cnt = moves->cnt;
	position* from1 = myCalloc(sizeof(position));
	position* to1 = myCalloc(sizeof(position));
	from1->x = from->x; from1->y = from->y;
	to1->x = to->x; to1->y = to->y;
	while (cnt > 0){
		if (currMove->next == NULL)
			currMove->next = myCalloc(sizeof(listMoves));
		currMove = (listMoves*)currMove->next;
		cnt--;
	}

	currMove->m.currPos = (position*)from1;

	currMove->m.currPos->cnt = depth;
	if (currMove->m.currPos->next == NULL)
		currMove->m.currPos->next = myCalloc(sizeof(position));
	ptr_currPos = (position*)currMove->m.currPos->next;
	ptr_currPos->x = to1->x; ptr_currPos->y = to1->y;
	moves->cnt++;

	freePositon(to1);
	


}

//the function prints user move.
void printMoves(listMoves* moves, char board[BOARD_SIZE][BOARD_SIZE]){
	listMoves* currMove = moves;
	position* positon_ptr = currMove->m.currPos;
	unsigned int x1, y1, x2, y2;
	char x1_char, x2_char, type;
	unsigned int cnt = moves->cnt;
	while (cnt > 0){
		x1 = positon_ptr->x;
		if (x1 == 10)
			break;
		x1_char = char_cordinate(x1);
		y1 = positon_ptr->y;
		printf("<%c,%u> to ", x1_char, y1);
		positon_ptr = (position*)positon_ptr->next;
		x2 = positon_ptr->x;
		x2_char = char_cordinate(x2);
		y2 = positon_ptr->y;
		printf("<%c,%u>", x2_char, y2);

		if ((y2 == 8) || (y2 == 1)){
			type = board[x1 - 1][y1 - 1];

			if ((type == 'm') || (type == 'M')){
				if (currMove->m.currPos->cnt == 1)
					printf(" %s", "queen");

				if (currMove->m.currPos->cnt == 2)
					printf(" %s", "rook");

				if (currMove->m.currPos->cnt == 3)
					printf(" %s", "knight");

				if (currMove->m.currPos->cnt == 4)
					printf(" %s", "bishop");


			}
		}

		printf("\n");
		if (currMove->next == NULL)
			break;
		currMove = (listMoves*)currMove->next;
		positon_ptr = currMove->m.currPos;
		cnt--;
	}


}

//the function prints computer move.
void printComputerMove(move m, char board[BOARD_SIZE][BOARD_SIZE]){
	position* positon_ptr = m.currPos;
	unsigned int x1, y1, x2, y2;
	char x_c,type;
	x1 = positon_ptr->x;
	x_c = char_cordinate(x1);
	y1 = positon_ptr->y;
	printf("Computer: move <%c,%u> to ", x_c, y1);
	positon_ptr = (position*)positon_ptr->next;
	while ((positon_ptr != NULL) && (positon_ptr->x != 0)){
		x2 = positon_ptr->x;
		x_c = char_cordinate(x2);
		y2 = positon_ptr->y;
		printf("<%c,%u>", x_c, y2);
		positon_ptr = (position*)positon_ptr->next;
		if ((y2 == 8) || (y2 == 1)){
			type = board[x1 - 1][y1 - 1];

			if ((type == 'm') || (type == 'M')){
				if (m.currPos->cnt == 1)
					printf(" %s", "queen");

				if (m.currPos->cnt == 2)
					printf(" %s", "rook");

				if (m.currPos->cnt == 3)
					printf(" %s", "knight");

				if (m.currPos->cnt == 4)
					printf(" %s", "bishop");


			}
		}
	}
	printf("\n");
}

//copying board1 to board2.
void copyingBoard(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]){
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			board2[i][j] = board1[i][j];
		}
	}
}




//return 1 if the position is valid, else return 0
unsigned int checkValidPosition(position *p){
	if ((p->x <= 8) && (p->x >= 1) && (p->y <= 8) && (p->y >= 1))
		return 1;
	return 0;
}

//check color in position p: if white return 0, if black return 1, else return 2
unsigned int checkColorPosition(char board[BOARD_SIZE][BOARD_SIZE], position* p){
	char ch = 'x';
	int x = 0, y = 0;
	if (p != NULL){
		x = p->x; y = p->y;
	}
	if ((x >= 1) && (y >= 1)){
		ch = board[x - 1][y - 1];
	}

	if ((ch == WHITE_P) || (ch == WHITE_B) || (ch == WHITE_N) || (ch == WHITE_R) || (ch == WHITE_Q) || (ch == WHITE_K))
		return 0;
	else if ((ch == BLACK_P) || (ch == BLACK_B) || (ch == BLACK_N) || (ch == BLACK_R) || (ch == BLACK_Q) || (ch == BLACK_K))
		return 1;
	else{
		return 2;
	}

}



//if the position is empty return 0, else return 1
unsigned int checkPositionEmpty(char board[BOARD_SIZE][BOARD_SIZE], position* p){
	int x = p->x; int y = p->y;
	if ((x >= 1) && (y >= 1)){
		if (board[x - 1][y - 1] == EMPTY){
			return 0;
		}

	}
	return 1;
}


GameRef newGame()
{
	GameRef newGame = (GameRef)malloc(sizeof(Game));
	if (newGame == NULL)
		return NULL;
	newGame->fromType = EMPTY;
	newGame->nextPlayer = WHITE; //white by default
	newGame->minimaxDepth = 1;
	newGame->mode = 1;
	newGame->Xfrom = -1;
	newGame->Xto = -1;
	newGame->Yfrom = -1;
	newGame->Yto = -1;
	newGame->userColor = WHITE; //OUR DEFALUT SETTING
	newGame->computerColor = BLACK; //OUR DEFALUT SETTING
	return newGame;
}
