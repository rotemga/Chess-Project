#include "ChessLogic.h"

//------------------This file include promoting the game state------------------- 

//the function simulates the user turn.
int userTurn(char board[BOARD_SIZE][BOARD_SIZE], char* color, char* next_player, unsigned int game_mode, unsigned int depth_computer){
	char *input_ptr, *input, x, promotion = ' ';
	char* othercolor,* toprint;
	unsigned int colorP, tmp = 0;
	int error = 0;
	int gameOver = 0;
	unsigned int depth = 0;
	char Newboard[BOARD_SIZE][BOARD_SIZE];

	char fileName[12];
	position* p = (position*)myMalloc(sizeof(position));
	position *from = (position*)myMalloc(sizeof(position));
	position *toList = (position*)myMalloc(sizeof(position));
	listMoves* moves = myCalloc(sizeof(listMoves));
	if (prefix(color, WHITE) == 1){
		toprint = "White";
	}
	else{
		toprint = "Black";
	}
	printf("%s player - enter your move:\n", toprint);
	input = getInput();
	input_ptr = input;
	//------------------quit function-----------------
	if (strcmp(input, "quit") == 0){
		free(p);
		free(from);
		free(toList);
		freeList(moves);
		gameOver = 1;

		exit(3);
	}
	//-----------------move function------------------
	else if (prefix(input, "move <") == 1){
		input_ptr += 6;
		x = input_ptr[0];
		from->x = (unsigned int)num_cordinate(x);
		input_ptr++;
		if (input_ptr[0] != ',')
			error = 1;
		input_ptr++;
		from->y = (unsigned int)strtof(input_ptr, &input_ptr);
		from->next = NULL;
		if (input_ptr[0] != '>')
			error = 1;
		input_ptr += 5;

		if (input_ptr[0] != '<')
			error = 1;
		input_ptr++;
		x = input_ptr[0];
		toList->x = (unsigned int)num_cordinate(x);
		input_ptr++;
		if (input_ptr[0] != ',')
			error = 1;
		input_ptr++;
		toList->y = (unsigned int)strtof(input_ptr, &input_ptr);
		if (input_ptr[0] != '>')
			error = 1;
		toList->next = NULL;
		input_ptr++;
		if (input_ptr[0] != '\0'){
			input_ptr++;
			char* tmp = input_ptr;
			promotion = promotionPawn(tmp, color);

		}


		int x = from->x;
		int y = from->y;
		int xTo = toList->x;
		int yTo = toList->y;
		p->x = x; p->y = y;

		//check if a coardinate is valid on the board

		if (!((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			error = 1;
		}
		else if (!((xTo >= 1) && (xTo <= 8) && (yTo >= 1) && (yTo <= 8)))
		{
			error = 1;
		}

		colorP = checkColorPosition(board, p);

		//check if the first coardinate is in the color of the user

		if (!(((colorP == 0) && (prefix(color, WHITE) == 1)) || ((colorP == 1) && (prefix(color, BLACK) == 1)))){
			if (error != 1)
				error = 2;
		}


		// a case of illeagal move for disc (the move is not in her get moves), error =3 (if not 1 or 2) in this case
		unsigned int valid = checkIfMoveIsValid(board, from, toList, color);
		if (strcmp(color, WHITE) == 0)
			othercolor = BLACK;
		else
			othercolor = WHITE;

		copyingBoard(board, Newboard);
		if (valid == 1)//check if a player perform a move the will result his own king being threatened by the opponent
			makeMove(Newboard, color, from, toList, promotion);

		if ((valid != 1) || (Check(Newboard, othercolor) == 1)){
			if ((error != 1) && (error != 2))
				error = 3;
		}
		if (error == 1){
			print_message(WRONG_POSITION);
			freeList(moves);
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
		else if (error == 2){
			print_message(NO_DISC);	
			freeList(moves);
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
		else if (error == 3){
			print_message(ILLEGAL_MOVE);
			freeList(moves);
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
		else{//make the user move, there were no errors
			makeMove(board, color, from, toList, promotion);
			print_board(board);
			//Check for checkmate or tie

			if (isMate(board, color) == 1){
				printf("Mate! %s player wins the game\n", toprint);
				gameOver = 1;
				free(p);
				free(from);
				free(toList);
				freeList(moves);
				exit(3);
			}


			if (isTie(board, WHITE, moves) == 1){
				print_message(TIE);
				gameOver = 1;
				free(p);
				free(from);
				free(toList);
				freeList(moves);
				exit(3);
			}
			freeList(moves);
			moves = myCalloc(sizeof(listMoves));

			if (isTie(board, BLACK, moves) == 1){
				print_message(TIE);
				gameOver = 1;
				free(p);
				free(from);
				free(toList);
				freeList(moves);
				exit(3);
			}
			freeList(moves);
			if (Check(board, color) == 1){
				printf("Check!\n");

			}

		}
		free(p);
		free(from);
		free(toList);

	}



	//-----------------get_moves function------------------

	else if (prefix(input, "get_moves <") == 1){ // get moves function
		int exit = 0;
		input_ptr += 11;
		x = input_ptr[0];
		from->x = (unsigned int)num_cordinate(x);
		input_ptr++;
		if (input_ptr[0] != ',')
			error = 1;
		input_ptr++;
		from->y = (unsigned int)strtof(input_ptr, &input_ptr);
		from->next = NULL;
		if (input_ptr[0] != '>')
			error = 1;
		input_ptr++;
		if (input_ptr[0] != '\0')
			error = 1;

		if (checkValidPosition(from) == 0)
			error = 1;

		colorP = checkColorPosition(board, from);
		if ((prefix(color, WHITE) == 1) && (colorP != 0) && (error == 0)){
			error = 2;
		}
		else if ((prefix(color, BLACK) == 1) && (colorP != 1) && (error == 0)){
			error = 2;
		}
		if (error == 1){
			print_message(WRONG_POSITION);
			exit = 1;
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
		else if (error == 2){
			print_message(NO_DISC);
			exit = 1;
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
		tmp = movesFromPos(board, from, color, moves, 0, 0);
		if (tmp == 0){
			//nothing
		}
		if (exit==0)
			printMoves(moves, board);
		free(p);
		free(from);
		free(toList);
		freeList(moves);
		if (exit==0)
			userTurn(board, color, next_player, game_mode, depth_computer);
	}
	//-----------------get_best_moves function------------------
	else if (prefix(input, "get_best_moves") == 1){ // get best moves function
		input_ptr += 15;
		if (prefix(input_ptr, "best") == 1)
			depth = bestDepth(board, color);
		else
			depth = (unsigned int)strtof(input_ptr, &input_ptr);
		listMoves* bestMoves = returnBestMoves(board, color, depth);


		printMoves(bestMoves, board);
		freeList(bestMoves);

		free(p);
		free(from);
		free(toList);
		freeList(moves);
		userTurn(board, color, next_player, game_mode, depth_computer);

	}
	//-----------------get_score function------------------
	else if (prefix(input, "get_score") == 1){ // get score function
		input_ptr += 10;
		if (prefix(input_ptr, "best") == 1){
			depth = bestDepth(board, color);
			input_ptr += 5;
		}
		else{
			depth = (unsigned int)strtof(input_ptr, &input_ptr);
			input_ptr++;
		}
		move moveFormat = checkMoveFormat(board, color, input_ptr, game_mode, depth_computer, next_player);
		int score = alphabetaForGetScore(color, board, depth, &moveFormat);
		printf("%d\n", score);
		free(p);
		free(from);
		free(toList);
		freeList(moves);
		userTurn(board, color, next_player, game_mode, depth_computer);
	}
	//-----------------save function------------------
	else if (prefix(input, "save") == 1){ // get score function
		input_ptr += strlen("save ");
		strcpy(fileName, input_ptr);


		GameRef game = myCalloc(sizeof(Game));
		copyingBoard(board, game->board);
		game->mode = game_mode;
		game->nextPlayer = next_player;
		game->userColor = color;
		game->minimaxDepth = depth_computer;
		int succ = saveGame(fileName, game);
		if (succ == 1){
			print_message(WRONG_FILE_NAME);	
		}
		free(p);
		free(from);
		free(toList);
		freeList(moves);
		userTurn(board, color, next_player, game_mode, depth_computer);
	}
	//-----------------quit function------------------

	else if (prefix(input, "quit") == 1){ // get score function

		gameOver = 1;
		free(p);
		free(from);
		free(toList);
		freeList(moves);
		exit(3);
	}

	else{
		print_message(ILLEGAL_COMMAND);
		free(p);
		free(from);
		free(toList);
		freeList(moves);
		userTurn(board, color, next_player, game_mode, depth_computer);
	}

	myFree(input);
	return gameOver;
}



//the function simulates the computer turn, sending to minimax, do the move and print it.
int computerTurn(char board[BOARD_SIZE][BOARD_SIZE], char* color, unsigned int depth){
	int gameOver = 0;
	char type, *toprint, Newboard[BOARD_SIZE][BOARD_SIZE];
	copyingBoard(board, Newboard);
	listMoves* moves = myCalloc(sizeof(listMoves));
	listMoves* bestMoves = returnBestMoves(board, color, depth);
	position* computer_from = (position*)myMalloc(sizeof(position));
	computer_from->x = bestMoves->m.currPos->x;
	computer_from->y = bestMoves->m.currPos->y;
	computer_from->next = NULL;
	position *computer_to = (position*)myMalloc(sizeof(position));
	position *temp;
	temp = (position*)bestMoves->m.currPos->next;
	computer_to->x = temp->x;
	computer_to->y = temp->y;
	computer_to->next = temp->next;
	computer_to->cnt = temp->cnt;
	type = typePromotion(&bestMoves->m, color);
	makeMove(board, color, computer_from, computer_to, type);
	printComputerMove(bestMoves->m,Newboard);
	print_board(board);
	freePositon(computer_from);
	if (prefix(color, WHITE) == 1){
		toprint = "White";
	}
	else{
		toprint = "Black";
	}

	if (isMate(board, color) == 1){
		printf("Mate! %s player wins the game\n", toprint);
		gameOver = 1;
		freeList(moves);
		freeList(bestMoves);
		freePositon(computer_to);
		exit(3);
	}
	else if (isTie(board, WHITE, moves) == 1){
		print_message(TIE);
		gameOver = 1;
		freeList(moves);
		freeList(bestMoves);
		freePositon(computer_to);
		exit(3);
	}
	freeList(moves);
	freePositon(computer_to);
	moves = myCalloc(sizeof(listMoves));

	if (isTie(board, BLACK, moves) == 1){
		print_message(TIE);
		gameOver = 1;
		freeList(moves);
		freeList(bestMoves);
		exit(3);
	}
	freeList(moves);


	if (Check(board, color) == 1){
		printf("Check!\n");
	}
	freeList(bestMoves);
	return gameOver;

}






//this function return moves format.
move checkMoveFormat(char board[BOARD_SIZE][BOARD_SIZE], char* color, char* input_ptr, unsigned int game_mode, unsigned int depth_computer, char* next_player){
	int error = 0, ok = 10;
	char x, promotion = ' ';
	char* othercolor;
	position* p = (position*)myMalloc(sizeof(position));
	position *from = (position*)myMalloc(sizeof(position));
	position *toList = (position*)myMalloc(sizeof(position));
	move res;

	unsigned int colorP;
	char Newboard[BOARD_SIZE][BOARD_SIZE];
	if (prefix(input_ptr, "move <") == 1){
		input_ptr += 6;
		x = input_ptr[0];
		from->x = (unsigned int)num_cordinate(x);
		input_ptr++;
		if (input_ptr[0] != ',')
			error = 1;
		input_ptr++;
		from->y = (unsigned int)strtof(input_ptr, &input_ptr);
		from->next = NULL;
		if (input_ptr[0] != '>')
			error = 1;
		input_ptr += 5;

		if (input_ptr[0] != '<')
			error = 1;
		input_ptr++;
		x = input_ptr[0];
		toList->x = (unsigned int)num_cordinate(x);
		input_ptr++;
		if (input_ptr[0] != ',')
			error = 1;
		input_ptr++;
		toList->y = (unsigned int)strtof(input_ptr, &input_ptr);
		if (input_ptr[0] != '>')
			error = 1;
		toList->next = NULL;
		input_ptr++;
		if (input_ptr[0] != '\0'){
			input_ptr++;
			char* tmp = input_ptr;
			promotion = promotionPawn(tmp, color);
			if (prefix(tmp, "queen") == 1)
				ok = 1;
			else if (prefix(tmp, "rook") == 1)
				ok = 2;
			else if (prefix(tmp, "knight") == 1)
				ok = 3;
			else if (prefix(tmp, "bishop") == 1)
				ok = 4;

		}


		int x = from->x;
		int y = from->y;
		int xTo = toList->x;
		int yTo = toList->y;
		p->x = x; p->y = y;

		//check if a coardinate is valid on the board

		if (!((x >= 1) && (x <= 8) && (y >= 1) && (y <= 8))){
			error = 1;
		}
		else if (!((xTo >= 1) && (xTo <= 8) && (yTo >= 1) && (yTo <= 8)))
		{
			error = 1;
		}

		colorP = checkColorPosition(board, p);

		//check if the first coardinate is in the color of the user

		if (!(((colorP == 0) && (prefix(color, WHITE) == 1)) || ((colorP == 1) && (prefix(color, BLACK) == 1)))){
			if (error != 1)
				error = 2;
		}


		// a case of illeagal move for disc (the move is not in her get moves), error =3 (if not 1 or 2) in this case
		unsigned int valid = checkIfMoveIsValid(board, from, toList, color);
		if (strcmp(color, WHITE) == 0)
			othercolor = BLACK;
		else
			othercolor = WHITE;

		copyingBoard(board, Newboard);
		if (valid == 1)//check if a player perform a move the will result his own king being threatened by the opponent
			makeMove(Newboard, color, from, toList, promotion);

		if ((valid != 1) || (Check(Newboard, othercolor) == 1)){
			if ((error != 1) && (error != 2))
				error = 3;
		}
		if (error == 1){
			print_message(WRONG_POSITION);
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
		else if (error == 2){
			print_message(NO_DISC);
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
		else if (error == 3){
			print_message(ILLEGAL_MOVE);
			userTurn(board, color, next_player, game_mode, depth_computer);
		}
	}
	res.currPos = from;


	res.currPos->next = myCalloc(sizeof(position));
	position* ptrPos = (position*)res.currPos->next;
	ptrPos->x = toList->x;
	ptrPos->y = toList->y;

	res.currPos->cnt = ok;

	free(toList);
	free(p);

	return res;

}

