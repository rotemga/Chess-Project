

#include "AIsettingMenu.h"

int main(int argc, char* args[])

{


	if ((argc == 2) && (strcmp(args[1], "gui") == 0)){
		windowRef w = getWindow();
		if (w == NULL)
		{
			perror("ERROR: window is NULL");
			return 1;
		}

		GameRef newGame = (GameRef)malloc(sizeof(Game));
		int ret = mainMenu(w, newGame);
		if (ret == ERROR)
		{
			perror("An error occurred while the game was played\n");
			freeWindow(w);
			free(newGame);
			return 1;
		}

		free(newGame);
		freeWindow(w);
	}
	else{


		int game_over = 0;
		char board[BOARD_SIZE][BOARD_SIZE];
		char *input = NULL, *user_color = WHITE, *next_player = WHITE, *computer_color = BLACK;
		unsigned int setting_over = 0, depth = 1, game_mode = 1, tmp_mode = 0, tmp = 0;
		position* kingPos = (position*)myCalloc(sizeof(position));
		listMoves* moves = myCalloc(sizeof(listMoves));
		kingPos->x = 10; kingPos->y = 10;
		char fileName[12] = "";
		GameRef game = newGame();
		init_board(board);
		copyingBoard(board, game->board);

		print_board(board);
		while (!setting_over)
		{
			print_message(ENTER_SETTINGS);
			input = getInput();
			if (strcmp(input, "start") != 0)
			{
				char *input_ptr = input;
				if (prefix(input, "game_mode ") == 1){ //if game_mode==1 it's two player mode, else if game_mode==2 it's player vs. Al mode
					input_ptr += strlen("game_mode ");
					tmp_mode = atoi(input_ptr);
					if (tmp_mode == 1){
						game_mode = tmp_mode;
						print_message(TWO_PLAYERS_GAME_MODE);
					}
					else if (tmp_mode == 2){
						game_mode = tmp_mode;
						print_message(PLAYER_VS_AI_GAME_MODE);
					}
					else{
						print_message(WRONG_GAME_MODE);
					}
				}

				else if (prefix(input, "difficulty ") == 1){ //minimax_depth function
					if (game_mode == 1){
						print_message(ILLEGAL_COMMAND); //CHECK IF WE NEED TO PRINT THIS MESSEGE HERE
					}
					else{
						input_ptr += strlen("difficulty ");
						if (((prefix(input_ptr, "-")) == 1) || (isspace(input_ptr[1]) != 0) || (prefix(input_ptr, " ") == 1)){
							print_message(WRONG_MINIMAX_DEPTH);
							break;
						}
						else if (prefix(input_ptr, "depth")){
							input_ptr += strlen("depth");
							tmp = atoi(input_ptr);
							depth = depth_update(tmp, depth);

						}
						else if (prefix(input_ptr, "best")){ //if depth==10, we say that it's difficulty best
							depth = 10;
						}
						else{
							print_message(WRONG_MINIMAX_DEPTH);
						}
					}
				}

				else if (prefix(input, "user_color ") == 1){ //user_color function
					if (game_mode == 1){
						print_message(ILLEGAL_COMMAND);
					}
					else {
						char current_color[6] = "";
						input_ptr += strlen("user_color ");
						for (int i = 0; i < 5; i++){
							current_color[i] = input_ptr[i];
						}
						current_color[5] = '\0';
						user_color = color_update(current_color, user_color);
					}
				}
				else if (prefix(input, "load ") == 1){ //loads the game settings from the file x
					input_ptr += strlen("load ");
					strcpy(fileName, input_ptr);

					if (fileExists(fileName) == 0){ //the file exist
						game = loadGame(fileName, game);
						copyingBoard(game->board, board);
						if (prefix(game->nextPlayer, WHITE) == 1)
							next_player = WHITE;
						else{
							next_player = BLACK;
						}
						if (prefix(game->userColor, WHITE) == 1)
							user_color = WHITE;
						else{
							user_color = BLACK;
						}

						tmp = game->minimaxDepth;
						if (tmp > 0)
							depth = game->minimaxDepth;
						game_mode = game->mode;
						print_board(board);
					}
					else{
						print_message(WRONG_FILE_NAME);
					}



				}

				else if (strcmp(input, "clear") == 0) //clear function
					clear(board);

				else if (prefix(input, "next_player ") == 1){
					char current_color[6];
					input_ptr += strlen("next_player ");
					for (int i = 0; i < 5; i++){
						current_color[i] = input_ptr[i];
					}
					current_color[5] = '\0';
					next_player = color_update(current_color, next_player);
				}

				else if (prefix(input, "rm <") == 1){ //rm <x,y> function
					char x = ' ';// , y;
					input_ptr += strlen("rm <");
					x = input_ptr[0];
					input_ptr++;
					if (input_ptr[0] != ',')
						print_message(WRONG_POSITION);
					input_ptr++;
					unsigned int y_num = (unsigned int)strtof(input_ptr, &input_ptr);
					if (input_ptr[0] != '>')
						print_message(WRONG_POSITION);
					unsigned int x_num = num_cordinate(x);
					remove_disc(board, x_num, y_num);
				}

				else if (prefix(input, "set <") == 1){ //set <x,y> a b function
					char x = ' ';
					input_ptr += strlen("set <");
					x = input_ptr[0];
					input_ptr++;
					if (input_ptr[0] != ',')
						print_message(WRONG_POSITION);
					input_ptr++;

					unsigned int y_num = (unsigned int)strtof(input_ptr, &input_ptr);
					if (input_ptr[0] != '>')
						print_message(WRONG_POSITION);
					unsigned int x_num = (unsigned int)num_cordinate(x);
					input_ptr++;
					input_ptr = next_argument(input_ptr);
					char a_color[6];
					for (int i = 0; i < 5; i++){
						a_color[i] = input_ptr[i];
					}
					a_color[5] = '\0';
					input_ptr += 5;
					input_ptr = next_argument(input_ptr);
					char* b_type = NULL; char b;
					b_type = input_ptr;
					b = discChar(b_type);
					set_disc(board, x_num, y_num, a_color, b, 0);
				}

				else if (strcmp(input, "print") == 0) //print function
					print_board(board);

				else if (strcmp(input, "quit") == 0){ //quit function
					setting_over = 1;
					game_over = 1;
					myFree(input);
					exit(3);
				}
				else
					print_message(ILLEGAL_COMMAND);
			}
			else{ //start function
				int exit = 0;
				int valid = valid_board(board);
				if (valid == 1){
					exit = 1;
				}
				else if (valid == 0)//the board is valid
					setting_over = 1;
				findKingPos(board, WHITE, kingPos);
				if ((kingPos->x == 10)&&(exit==0)){
					print_message(WROND_BOARD_INITIALIZATION);
					setting_over = 0;
					exit = 1;
				}
				kingPos->x = 10; kingPos->y = 10;
				findKingPos(board, BLACK, kingPos);
				if ((kingPos->x == 10) && (exit == 0)){
					print_message(WROND_BOARD_INITIALIZATION);
					setting_over = 0;
					exit = 1;
				}
				if ((exit == 0)&&(isTie(board, BLACK, moves) == 1)){
					print_message(TIE);
					setting_over = 1;
					game_over = 1;
					exit = 1;


				}
				
				freeList(moves);
				moves = myCalloc(sizeof(listMoves));
				moves->cnt = 0;

				if ((exit == 0) && (isTie(board, WHITE, moves) == 1)){
					print_message(TIE);
					setting_over = 1;
					game_over = 1;
					exit = 1;

				}
				//freeList(moves);
				if ((exit == 0) && (prefix(user_color, WHITE) == 1)&& (isMate(board, BLACK) == 1)){
					printf("Mate! %s player wins the game\n", "Black");
					setting_over = 1;
					game_over = 1;
					exit = 1;
				}
				else if ((exit == 0)&&(prefix(user_color, BLACK) == 1) && (isMate(board, WHITE) == 1))
				{
					printf("Mate! %s player wins the game\n", "White");
					setting_over = 1;
					game_over = 1;
					exit = 1;
				}
			}

			myFree(input);


		}
		freeList(moves);
		// ***END OF SETTING STATE, MOVE TO GAME STATE***

		unsigned int cnt_turns = 1;
		if (prefix(next_player, BLACK) == 1){
			cnt_turns = 2;
		}
		if (game_mode == 1){
			if (prefix(next_player, BLACK) == 1){
				user_color = BLACK;
			}
			else
			{
				user_color = WHITE;
			}
		}

		if (prefix(user_color, BLACK) == 1)
			computer_color = WHITE;
		while (!game_over){

			if (cnt_turns % 2) { // white's turn

				if (game_mode == 2){ //--------player vs.Al (computer) mode

					if (prefix(user_color, WHITE) == 1){ //the user color is white
						game_over = userTurn(board, WHITE,next_player, game_mode, depth);
					}
					else{	//the computer is white
						if (depth == 10)//best case
							depth = bestDepth(board, computer_color);
						game_over = computerTurn(board, WHITE, depth);
					}

				}


				else if (game_mode == 1){ //-----two player mode
					if (prefix(user_color, BLACK) == 1){ //the user color is black
						game_over = userTurn(board, BLACK,next_player,game_mode, depth);
						user_color = WHITE;

					}
					else{
						game_over = userTurn(board, WHITE, next_player, game_mode, depth);
						user_color = BLACK;



					}
				}
				cnt_turns++;
			}

			else if (!(cnt_turns % 2)){ // black's turn

				if (game_mode == 2){ //--------it's two player mode

					if (prefix(user_color, BLACK) == 1){ //the user color is black
						game_over = userTurn(board, BLACK, next_player, game_mode, depth);
					}
					else{	//the computer is black
						if (depth == 10)//best case
							depth = bestDepth(board, computer_color);
						game_over = computerTurn(board, BLACK, depth);
					}

				}


				else if (game_mode == 1){ //-----two player mode
					if (prefix(user_color, BLACK) == 1){ //the user color is black
						game_over = userTurn(board, BLACK, next_player, game_mode, depth);
						user_color = WHITE;

					}
					else{
						game_over = userTurn(board, WHITE, next_player, game_mode, depth);
						user_color = BLACK;

					}
				}
				cnt_turns++;

			}

		}
	}
	return 0;

}


