
#include "setOrGame.h"

//show the set or game menu (1 is set 2 is game)
int setOrGame(windowRef w, GameRef game, int setorGame)
{

	int quit = 0;
	int retVal = 0;
	int FROM = 1;
	int FROMGAME = 1;
	int legal = 0;
	int end = 0; //1 if the game ended
	int acceptMode = 0;
	char prevTo = 'm';
	int seeDegree = 0;
	int promotion = 0;
	int start = 0;
	int seebest = 0; //1 is see best in playerVSplayer

	if (strcmp(game->nextPlayer, game->computerColor) == 0)
		start = 1;


	buttonRef setBtn = getBtn(setAndReturnImgFile, (WSw / 2) - BtnRectWidth / 2, 5.2 * (WSh / 6));
	if (setBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef saveBtn = getBtn(saveGameImgFile, (5 * WSw / 6) - BtnRectWidth / 2 + 100, 1.9 * (WSh / 6));
	if (saveBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef mainMenuBtn = getBtn(mainMenuImgFile, (5 * WSw / 6) - BtnRectWidth / 2 + 100, 1.4 * (WSh / 6));
	if (mainMenuBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef seeBestBtn = getBtn(seeBestImgFile, (5 * WSw / 6) - BtnRectWidth / 2 + 100, 2.4 * (WSh / 6));
	if (seeBestBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef seeBestLevelBtn = getBtn(seeBestLevelImgFile, (5 * WSw / 6) - BtnRectWidth / 2 + 100, 2.4 * (WSh / 6));
	if (seeBestLevelBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef quitBtn = getBtn(squitImgFile, (5 * WSw / 6) - BtnRectWidth / 2 + 100, 3.9 * (WSh / 6));
	if (quitBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef removeBtn = getBtn(removeImg, (5 * WSw / 6) - BtnRectWidth / 2 + 100, (WSh / 2) - 100);
	if (removeBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef initBtn = getBtn(initBoardImg, (5 * WSw / 6) - BtnRectWidth / 2 + 100, (WSh / 2));
	if (initBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}


	buttonRef startBtn = getBtn(startImg, (5 * WSw / 6) - BtnRectWidth / 2 + 100, 2.9 * (WSh / 6));
	if (startBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef acceptBtn = getBtn(smallwhiterecImg, (WSw / 15) - BtnRectWidth / 2 + 130, 2.2 * (WSh / 6));
	if (acceptBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef rejectBtn = getBtn(smallwhiterecImg, (WSw / 15) - BtnRectWidth / 2 + 130, 2.7 * (WSh / 6));
	if (rejectBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}


	buttonRef promot[4];
	for (int col = 0; col < 4; col++)
	{
		promot[col] = getBtn(promotTileImg, 454 + col * 65, 610);
		((promot[col]->lbl)->LblRect).h = 65;
		((promot[col]->lbl)->LblRect).w = 65;
	}

	panelRef topPanel = getPanel(0, 0, WSw, WSh);
	if (topPanel == NULL){
		perror("ERROR: failed getPanel");
		return ERROR;
	}

	lableRef topPanelLbl = getLbl(blankBGImgFile, 0, 0);
	if (topPanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, WSw, WSh);


	panelRef chessPanel = getPanel(155, 100, 489, 500);
	if (chessPanel == NULL){
		perror("ERROR: failed getPanel");
		return ERROR;
	}

	lableRef chessPanelLbl = getLbl(chessBoardImgFile, 270, 100);
	if (chessPanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, 489, 500);

	panelRef toolsPanel = getPanel(270, 100, 489, 500);
	if (toolsPanel == NULL){
		perror("ERROR: failed getPanel");
		return ERROR;
	}

	lableRef instrucPanelLbl = getLbl(instrucImg, 120, 595);
	if (instrucPanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, 800, 83);

	lableRef blackTurnPanelLbl = getLbl(blackTurnImg, (5 * WSw / 6) - BtnRectWidth / 2 + 80, (WSh / 6));
	if (blackTurnPanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, 183, 46);

	lableRef whiteTurnPanelLbl = getLbl(whiteTurnImg, (5 * WSw / 6) - BtnRectWidth / 2 + 80, (WSh / 6));
	if (whiteTurnPanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, 183, 46);

	lableRef whitePanelLbl = getLbl(gameInstImg, 120, (3 * WSh / 4) + 30);
	if (whitePanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, 800, 105);



	buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE];
	setImgOnBoard(game, graphicBoard);


	// Draw images in panels




	while (!quit)
	{
		// Clear window to WHITE
		if (fillWindow(w, 255, 255, 255) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed fillWindow");
			break;
		}
		fillPanel(topPanel, 255, 255, 255);

		// Draw images

		if (drowImgOnLblPnl(topPanelLbl, topPanel) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}


		if (drowImgOnLblPnl(chessPanelLbl, chessPanel) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (setorGame == 1){
			if (drowImgOnBtn(setBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}
			if (drowImgOnBtn(removeBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}

			if (drowImgOnBtn(initBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}

			if (drowImgOnLblPnl(instrucPanelLbl, chessPanel) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}
		}
		else{

			if (drowImgOnBtn(acceptBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}
			if (drowImgOnBtn(rejectBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}
			if (drowImgOnBtn(saveBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}

			if (drowImgOnBtn(mainMenuBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}

			if (game->mode == 2){
				if (drowImgOnBtn(seeBestBtn, w) == 1)
				{
					quit = QUIT;
					retVal = ERROR;
					perror("ERROR: failed drowImg");
					break;
				}
				if ((strcmp(game->computerColor, game->nextPlayer) == 0) && (acceptMode == 0) && (promotion == 0) && (start == 1)){
					if (drowImgOnBtn(startBtn, w) == 1)
					{
						quit = QUIT;
						retVal = ERROR;
						perror("ERROR: failed drowImg");
						break;
					}
				}
			}
			else {
				if (drowImgOnBtn(seeBestLevelBtn, w) == 1)
				{
					quit = QUIT;
					retVal = ERROR;
					perror("ERROR: failed drowImg");
					break;
				}
			}

			if (drowImgOnBtn(quitBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}

			if (drowImgOnLblPnl(whitePanelLbl, chessPanel) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}


			if (strcmp(game->nextPlayer, BLACK) == 0){
				if ((acceptMode == 0) && (promotion == 0)){
					if (drowImgOnLblPnl(blackTurnPanelLbl, chessPanel) == 1)
					{
						quit = QUIT;
						retVal = ERROR;
						perror("ERROR: failed drowImg");
						break;
					}
				}
				else{
					if (drowImgOnLblPnl(whiteTurnPanelLbl, chessPanel) == 1)
					{
						quit = QUIT;
						retVal = ERROR;
						perror("ERROR: failed drowImg");
						break;
					}
				}
			}
			else if (strcmp(game->nextPlayer, WHITE) == 0){
				if ((acceptMode == 0) && (promotion == 0)){
					if (drowImgOnLblPnl(whiteTurnPanelLbl, chessPanel) == 1)
					{
						quit = QUIT;
						retVal = ERROR;
						perror("ERROR: failed drowImg");
						break;
					}
				}
				else{
					if (drowImgOnLblPnl(blackTurnPanelLbl, chessPanel) == 1)
					{
						quit = QUIT;
						retVal = ERROR;
						perror("ERROR: failed drowImg");
						break;
					}
				}
			}
		}



		for (int row = 0; row <BOARD_SIZE; row++)
		{
			for (int col = 0; col < BOARD_SIZE; col++)
			{
				if (drowImgOnLblPnl((graphicBoard[col][row])->lbl, toolsPanel) == 1)
				{
					quit = QUIT;
					retVal = ERROR;
					perror("ERROR: failed drowImg");
					break;
				}
			}
		}


		if (SDL_Flip(w->window) != 0)
		{
			perror("ERROR: failed perform SDL_Flip in MainMenu");
			return ERROR;
		}


		//computer turn
		if ((quit != QUIT) && (end == 0) && (game->mode == 2) && (strcmp(game->nextPlayer, game->computerColor) == 0) && (acceptMode == 0) && (promotion == 0) && (start == 0)){
			if (reloadImgToLbl(whitePanelLbl, whiteRecLowImg) == 1){
				perror("ERROR: failed reloadImg");
				return ERROR;
			}

			listMoves* moves1 = myCalloc(sizeof(listMoves));
			initMoves(moves1);
			listMoves* bestMoves = returnBestMoves(game->board, game->computerColor, game->minimaxDepth);
			game->Xfrom = bestMoves->m.currPos->x - 1;
			game->Yfrom = bestMoves->m.currPos->y - 1;
			game->fromType = game->board[game->Xfrom][game->Yfrom];
			position *temp;
			temp = (position*)bestMoves->m.currPos->next;
			game->Xto = temp->x - 1;
			game->Yto = temp->y - 1;
			gameBoardPress(game, 2, graphicBoard);
			if (promotMinimax(game, bestMoves, graphicBoard) == ERROR)
				return ERROR;
			freeList(moves1);
			freeList(bestMoves);

			if (reloadImgToLbl(whitePanelLbl, whiteRecImg) == 1){
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			char* color;
			if (strcmp(game->nextPlayer, WHITE) == 0)
				color = BLACK;
			else
				color = WHITE;
			listMoves* moves = myCalloc(sizeof(listMoves));
			if (isMate(game->board, color) == 1){
				if (reloadImgToLbl(whitePanelLbl, mateImg) == 1){
					perror("ERROR: failed reloadImg");
					return ERROR;
				}
				end = 1;
			}
			else if ((isTie(game->board, WHITE, moves) == 1) || (isTie(game->board, BLACK, moves) == 1)){
				if (reloadImgToLbl(whitePanelLbl, tieImg) == 1){
					perror("ERROR: failed reloadImg");
					return ERROR;
				}
				end = 1;
			}
			else if (Check(game->board, color) == 1){
				if (reloadImgToLbl(whitePanelLbl, checkImg) == 1){
					perror("ERROR: failed reloadImg");
					return ERROR;
				}
			}
			else
				if (reloadImgToLbl(whitePanelLbl, whiteRecLowImg) == 1){
					perror("ERROR: failed reloadImg");
					return ERROR;
				}
			freeList(moves);
		}

		if (seeDegree != 0){
			listMoves* moves1 = myCalloc(sizeof(listMoves));
			initMoves(moves1);
			listMoves* bestMoves = returnBestMoves(game->board, game->nextPlayer, seeDegree);
			game->Xfrom = bestMoves->m.currPos->x - 1;
			game->Yfrom = bestMoves->m.currPos->y - 1;
			game->fromType = game->board[game->Xfrom][game->Yfrom];
			position *temp;
			temp = (position*)bestMoves->m.currPos->next;
			game->Xto = temp->x - 1;
			game->Yto = temp->y - 1;
			prevTo = game->board[game->Xto][game->Yto];
			gameBoardPress(game, 2, graphicBoard);
			if (promotMinimax(game, bestMoves, graphicBoard) == ERROR)
				return ERROR;
			reloadImgToLbl(whitePanelLbl, whiteRecImg);
			reloadImgToBtn(acceptBtn, acceptImg);
			reloadImgToBtn(rejectBtn, rejectImg);
			acceptMode = 1;
			freeList(moves1);
			freeList(bestMoves);
			seeDegree = 0;
		}

		if (seebest == 1){

			if (reloadImgToLbl(whitePanelLbl, whiteRecImg) == 1)
				return ERROR;
			listMoves* moves1 = myCalloc(sizeof(listMoves));
			initMoves(moves1);
			listMoves* bestMoves = returnBestMoves(game->board, game->nextPlayer, game->minimaxDepth);
			game->Xfrom = bestMoves->m.currPos->x - 1;
			game->Yfrom = bestMoves->m.currPos->y - 1;
			game->fromType = game->board[game->Xfrom][game->Yfrom];
			position *temp;
			temp = (position*)bestMoves->m.currPos->next;
			game->Xto = temp->x - 1;
			game->Yto = temp->y - 1;
			prevTo = game->board[game->Xto][game->Yto];
			gameBoardPress(game, 2, graphicBoard);
			if (promotMinimax(game, bestMoves, graphicBoard) == ERROR)
				return ERROR;
			reloadImgToBtn(acceptBtn, acceptImg);
			reloadImgToBtn(rejectBtn, rejectImg);
			acceptMode = 1;
			freeList(moves1);
			freeList(bestMoves);
			seebest = 0;
		}


		//Poll for keyboard & mouse events
		SDL_Event e = { 0 };
		while ((SDL_PollEvent(&e) != 0) && quit == 0 && retVal == 0)
		{
			switch (e.type)
			{
			case (SDL_QUIT) :
				quit = QUIT;
				retVal = QUIT;
				break;
			case (SDL_KEYUP) :
				if (e.key.keysym.sym == SDLK_ESCAPE){
					quit = QUIT;
					retVal = QUIT;
				}
			case (SDL_MOUSEBUTTONUP) :
				if (setorGame == 1){
					if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(setBtn, e)){
						int valid = 0; //0 is valid 1 is invalid
						if (valid_board(game->board) == 1)
							valid = 1;
						position* kingPos = (position*)myCalloc(sizeof(position));
						kingPos->x = 10; kingPos->y = 10;
						findKingPos(game->board, WHITE, kingPos);
						if (kingPos->x == 10)
							valid = 1;
						kingPos->x = 10; kingPos->y = 10;
						findKingPos(game->board, BLACK, kingPos);
						if (kingPos->x == 10)
							valid = 1;
						freePositon(kingPos);
						if (valid == 0)
							quit = QUIT;
						else{
							reloadImgToLbl(instrucPanelLbl, illegalBoardImg);
						}
					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(initBtn, e)){
						char board[BOARD_SIZE][BOARD_SIZE];
						init_board(board);
						copyingBoard(board, game->board);
						setImgOnBoard(game, graphicBoard);
						reloadImgToLbl(instrucPanelLbl, instrucImg);
					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && PanelArea(toolsPanel, e) && !BtnArea(removeBtn, e)){
						reloadImgToLbl(instrucPanelLbl, instrucImg);
						if (FROM == 1){
							game->Xfrom = 7 - (((305 + 8 * cubeSize - e.button.x) / cubeSize));
							game->Yfrom = ((-e.button.y + 142 + 8 * cubeSize) / cubeSize);
							game->fromType = game->board[game->Xfrom][game->Yfrom];
							FROM = 2;
						}
						else
						{
							game->Xto = 7 - (((305 + 8 * cubeSize - e.button.x) / cubeSize));
							game->Yto = ((-e.button.y + 142 + 8 * cubeSize) / cubeSize);
							FROM = 1;
							gameBoardPress(game, 1, graphicBoard);
						}
					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(removeBtn, e)){
						if (FROM == 2){
							if (reloadImgToLbl((graphicBoard[game->Xfrom][game->Yfrom])->lbl, freeTileImg) == 1)
							{
								perror("ERROR: failed reloadImg");
								return ERROR;
							}
							game->board[game->Xfrom][game->Yfrom] = EMPTY;
							FROM = 1;
						}
					}
				}
				else{
					if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(startBtn, e) && (acceptMode == 0) && (game->mode == 2) && (start == 1)){
						reloadImgToBtn(startBtn, smallwhiterecImg);
						reloadImgToLbl(whitePanelLbl, loadingImg);
						start = 0;
					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(saveBtn, e) && (acceptMode == 0) && (promotion == 0)){
						retVal = LoadOrSaveMenu(w, game, 2);
						if ((retVal == QUIT) || (retVal == ERROR))
							quit = QUIT;
					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(mainMenuBtn, e)){
						quit = QUIT;
						retVal = mainMenu(w, game);
					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(quitBtn, e)){
						quit = QUIT;
						retVal = QUIT;
					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(seeBestLevelBtn, e) && (acceptMode == 0) && (promotion == 0) && (game->mode == 1) && (end == 0)){
						if ((e.button.y > 351) && (e.button.y <= 391)){
							if (e.button.x < 888)
								seeDegree = 1;
							else
								seeDegree = 2;
						}
						else if ((e.button.y > 391) && (e.button.y <= 431)){
							if (e.button.x < 888)
								seeDegree = 3;
							else
								seeDegree = 4;
						}
						else if ((e.button.y > 431) && (e.button.y <= 471))
							seeDegree = bestDepth(game->board, game->nextPlayer); //best depth
						if (seeDegree != 0)
							reloadImgToLbl(whitePanelLbl, loadingBestImg);
					}

					else if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(seeBestBtn, e) && (acceptMode == 0) && (game->mode == 2) && (promotion == 0) && (start == 0) && (end == 0)){
						reloadImgToLbl(whitePanelLbl, loadingBestImg);
						seebest = 1;
						continue;
					}
					else if (((e.button.button == SDL_BUTTON_LEFT) && BtnArea(acceptBtn, e) && (acceptMode == 1))){
						reloadImgToBtn(acceptBtn, smallwhiterecImg);
						reloadImgToBtn(rejectBtn, smallwhiterecImg);
						acceptMode = 0;
						seeDegree = 0;
						char* color;
						if (strcmp(game->nextPlayer, WHITE) == 0)
							color = BLACK;
						else
							color = WHITE;
						listMoves* moves = myCalloc(sizeof(listMoves));
						if (isMate(game->board, color) == 1){
							if (reloadImgToLbl(whitePanelLbl, mateImg) == 1){
								perror("ERROR: failed reloadImg");
								return ERROR;
							}
							end = 1;
						}
						else if ((isTie(game->board, WHITE, moves) == 1) || (isTie(game->board, BLACK, moves) == 1)){
							if (reloadImgToLbl(whitePanelLbl, tieImg) == 1){
								perror("ERROR: failed reloadImg");
								return ERROR;
							}
							end = 1;
						}
						else if (Check(game->board, color) == 1){
							if (reloadImgToLbl(whitePanelLbl, checkImg) == 1){
								perror("ERROR: failed reloadImg");
								return ERROR;
							}
						}
						else{
							if (game->mode == 1)
								reloadImgToLbl(whitePanelLbl, whiteRecImg);
							else
								reloadImgToLbl(whitePanelLbl, loadingImg);
						}
						freeList(moves);
					}
					else if (((e.button.button == SDL_BUTTON_LEFT) && BtnArea(rejectBtn, e) && (acceptMode == 1))){
						reloadImgToBtn(acceptBtn, smallwhiterecImg);
						reloadImgToBtn(rejectBtn, smallwhiterecImg);
						acceptMode = 0;
						seeDegree = 0;
						if (strcmp(game->nextPlayer, WHITE) == 0)
							game->nextPlayer = BLACK;
						else
							game->nextPlayer = WHITE;
						char* toolType = imgName(game->fromType);
						char* prevType = imgName(prevTo);
						if (reloadImgToLbl((graphicBoard[game->Xfrom][game->Yfrom])->lbl, toolType)
							== 1)
						{
							perror("ERROR: failed reloadImg");
							return ERROR;
						}
						if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, prevType) == 1)
						{
							perror("ERROR: failed reloadImg");
							return ERROR;
						}
						game->board[game->Xfrom][game->Yfrom] = game->fromType;
						game->board[game->Xto][game->Yto] = prevTo;


					}
					else if ((e.button.button == SDL_BUTTON_LEFT) && (BtnArea(promot[0], e) || BtnArea(promot[1], e)
						|| BtnArea(promot[2], e) || BtnArea(promot[3], e)) && (promotion == 1)){
						if (strcmp(game->nextPlayer, WHITE) == 0){ //promot black
							if (BtnArea(promot[0], e)){
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blackqImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = BLACK_Q;
							}
							else if (BtnArea(promot[1], e)){
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blackrImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = BLACK_R;
							}
							else if (BtnArea(promot[2], e)){
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blacknImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = BLACK_N;
							}
							else{
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blackbImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = BLACK_B;
							}
						}
						else{ //promot white
							if (BtnArea(promot[0], e)){
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whiteqImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = WHITE_Q;
							}
							else if (BtnArea(promot[1], e)){
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whiterImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = WHITE_R;
							}
							else if (BtnArea(promot[2], e)){
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whitenImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = WHITE_N;
							}
							else{
								if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whitebImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
								game->board[game->Xto][game->Yto] = WHITE_B;
							}
						}
						promotion = 0;
						if (reloadImgToLbl(whitePanelLbl, whiteRecImg) == 1){
							perror("ERROR: failed reloadImg");
							return ERROR;
						}
						char* color;
						if (strcmp(game->nextPlayer, WHITE) == 0)
							color = BLACK;
						else
							color = WHITE;
						listMoves* moves = myCalloc(sizeof(listMoves));
						if (isMate(game->board, color) == 1){
							if (reloadImgToLbl(whitePanelLbl, mateImg) == 1){
								perror("ERROR: failed reloadImg");
								return ERROR;
							}
							end = 1;
						}
						else if ((isTie(game->board, WHITE, moves) == 1) || (isTie(game->board, BLACK, moves) == 1)){
							if (reloadImgToLbl(whitePanelLbl, tieImg) == 1){
								perror("ERROR: failed reloadImg");
								return ERROR;
							}
							end = 1;
						}
						else if (Check(game->board, color) == 1){
							if (reloadImgToLbl(whitePanelLbl, checkImg) == 1){
								perror("ERROR: failed reloadImg");
								return ERROR;
							}
						}
						else{
							if (game->mode == 1)
								reloadImgToLbl(whitePanelLbl, whiteRecImg);
							else
								reloadImgToLbl(whitePanelLbl, loadingImg);
						}
						freeList(moves);
						continue;

					}
					if ((quit != QUIT) && (end == 0) && ((game->mode == 1) || ((strcmp(game->nextPlayer, game->userColor) == 0) && (acceptMode == 0) && (promotion == 0) && (start == 0)))){
						if ((e.button.button == SDL_BUTTON_LEFT) && PanelArea(toolsPanel, e) && (end == 0)){
							if (FROMGAME == 1){
								game->Xfrom = 7 - (((305 + 8 * cubeSize - e.button.x) / cubeSize));
								game->Yfrom = ((-e.button.y + 142 + 8 * cubeSize) / cubeSize);
								game->fromType = game->board[game->Xfrom][game->Yfrom];
								FROMGAME = 2;
								if (reloadImgToLbl(whitePanelLbl, whiteRecImg) == 1)
								{
									perror("ERROR: failed reloadImg");
									return ERROR;
								}
							}
							else
							{
								game->Xto = 7 - ((305 + 8 * cubeSize - e.button.x) / cubeSize);
								game->Yto = ((-e.button.y + 142 + 8 * cubeSize) / cubeSize);
								FROMGAME = 1;
								legal = gameBoardPress(game, 2, graphicBoard);
								if (legal == 0){ //move was illegal
									if (reloadImgToLbl(whitePanelLbl, illegalMoveImg) == 1){
										perror("ERROR: failed reloadImg");
										return ERROR;
									}
								}
								else if (legal == 2){ //promotion
									if (strcmp(game->nextPlayer, WHITE) == 0){
										reloadImgToLbl(whitePanelLbl, promotblackImg);
										promotion = 1;
									}
									else{
										reloadImgToLbl(whitePanelLbl, promotwhiteImg);
										promotion = 1;
									}
									continue;
								}
								else if (legal == 1) //legal move
								{
									if (reloadImgToLbl(whitePanelLbl, whiteRecImg) == 1)
										return ERROR;
									char* color;
									if (strcmp(game->nextPlayer, WHITE) == 0)
										color = BLACK;
									else
										color = WHITE;
									listMoves* moves = myCalloc(sizeof(listMoves));
									if (isMate(game->board, color) == 1){
										if (reloadImgToLbl(whitePanelLbl, mateImg) == 1){
											perror("ERROR: failed reloadImg");
											return ERROR;
										}
										end = 1;
									}
									else if ((isTie(game->board, WHITE, moves) == 1) || (isTie(game->board, BLACK, moves) == 1)){
										if (reloadImgToLbl(whitePanelLbl, tieImg) == 1){
											perror("ERROR: failed reloadImg");
											return ERROR;
										}
										end = 1;
									}
									else if (Check(game->board, color) == 1){
										if (reloadImgToLbl(whitePanelLbl, checkImg) == 1){
											perror("ERROR: failed reloadImg");
											return ERROR;
										}
									}
									else{
										if (game->mode == 1)
											reloadImgToLbl(whitePanelLbl, whiteRecImg);
										else
											reloadImgToLbl(whitePanelLbl, loadingImg);
									}
									freeList(moves);
								}
							}
						}
					}


				}
				// add functionality to all buttons here...

			}
			SDL_Delay(0);
		}
	}


	// free allocated mem..
	freePanel(topPanel);
	freeBtn(setBtn);
	freePanel(chessPanel);
	freeLbl(chessPanelLbl);
	freeLbl(topPanelLbl);
	freePanel(toolsPanel);
	freeBtn(mainMenuBtn);
	freeBtn(saveBtn);
	freeBtn(seeBestBtn);
	freeBtn(seeBestLevelBtn);
	freeBtn(quitBtn);
	freeBtn(removeBtn);
	freeBtn(startBtn);
	freeBtn(acceptBtn);
	freeBtn(rejectBtn);
	freeLbl(instrucPanelLbl);
	freeLbl(blackTurnPanelLbl);
	freeLbl(whiteTurnPanelLbl);
	freeLbl(whitePanelLbl);
	freeBtn(initBtn);
	freeBtn(promot[0]);
	freeBtn(promot[1]);
	freeBtn(promot[2]);
	freeBtn(promot[3]);
	freeGraphicBoard(graphicBoard);
	//free graphic board

	return retVal;
}

//function for freeing the graphic board
void freeGraphicBoard(buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE]){
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			freeBtn(graphicBoard[col][row]);
		}
	}
}

//function for setting images on the graphic board
void setImgOnBoard(GameRef game, buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE])
{
	for (int row = 0; row <BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			char* currImg = imgName(game->board[col][row]);
			graphicBoard[col][row] = getBtn(currImg, 305 + col * cubeSize, 142 + (7 - row) * cubeSize);
			((graphicBoard[col][row]->lbl)->LblRect).h = cubeSize;
			((graphicBoard[col][row]->lbl)->LblRect).w = cubeSize;
		}
	}
}


////returns the image name for the tool type
char* imgName(char letter){
	char* currImg;
	switch (letter)
	{
	case WHITE_P:
		currImg = whitepImg;
		break;
	case WHITE_R:
		currImg = whiterImg;
		break;
	case WHITE_B:
		currImg = whitebImg;
		break;
	case WHITE_N:
		currImg = whitenImg;
		break;
	case WHITE_Q:
		currImg = whiteqImg;
		break;
	case WHITE_K:
		currImg = whitekImg;
		break;
	case BLACK_P:
		currImg = blackpImg;
		break;
	case BLACK_R:
		currImg = blackrImg;
		break;
	case BLACK_B:
		currImg = blackbImg;
		break;
	case BLACK_N:
		currImg = blacknImg;
		break;
	case BLACK_Q:
		currImg = blackqImg;
		break;
	case BLACK_K:
		currImg = blackkImg;
		break;
	default:
		currImg = freeTileImg;
		break;
	}
	return currImg;
}

//return 1 if a move was made, 1 means we are in set, 2 means we are in game
int gameBoardPress(GameRef game, int setORgame, buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE])
{
	int moveMade = 0;
	if (setORgame == 2){ //game
		position *from = (position*)myMalloc(sizeof(position));
		position *to = (position*)myMalloc(sizeof(position));
		from->x = game->Xfrom + 1;
		from->y = game->Yfrom + 1;
		from->next = NULL;
		to->x = game->Xto + 1;
		to->y = game->Yto + 1;
		to->next = NULL;
		char* colorPressed = "";
		char* othercolor = "";
		if (game->fromType >= 'a' && game->fromType <= 'z'){
			colorPressed = WHITE; //lower case means white (1)
			othercolor = BLACK;
		}
		else{
			colorPressed = BLACK; //uper case means black (2)
			othercolor = WHITE;
		}
		if ((strcmp(game->nextPlayer, colorPressed) == 0) && (checkIfMoveIsValid(game->board, from, to, colorPressed) == 1)){
			char Newboard[BOARD_SIZE][BOARD_SIZE];
			copyingBoard(game->board, Newboard);
			makeMove(Newboard, colorPressed, from, to, ' ');
			if ((Check(Newboard, othercolor) == 1)) //the king is being threthend
				moveMade = 0;
			else{
				char* toolType = imgName(game->fromType);
				if (reloadImgToLbl((graphicBoard[game->Xfrom][game->Yfrom])->lbl, freeTileImg)
					== 1)
				{
					return ERROR;
				}
				if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, toolType) == 1)
				{
					return ERROR;
				}
				game->board[game->Xfrom][game->Yfrom] = EMPTY;
				game->board[game->Xto][game->Yto] = game->fromType;
				if (strcmp(game->nextPlayer, WHITE) == 0)
					game->nextPlayer = BLACK;
				else
					game->nextPlayer = WHITE;
				moveMade = 1;
				if (((game->fromType == 'M') && (game->Yfrom == 1) && (game->Yto == 0)) || ((game->fromType == 'm') && (game->Yfrom == 6) && (game->Yto == 7)))
					moveMade = 2;//the move was made, and its promotion
			}
		}
		else
			moveMade = 0;
		freePositon(from);
		freePositon(to);
	}
	else //set
	{
		if (game->fromType != EMPTY){
			char* toolType = imgName(game->fromType);
			if (reloadImgToLbl((graphicBoard[game->Xfrom][game->Yfrom])->lbl, freeTileImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, toolType) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xfrom][game->Yfrom] = EMPTY;
			game->board[game->Xto][game->Yto] = game->fromType;
		}
		print_board(game->board);
	}
	return moveMade;
}

int promotMinimax(GameRef game, listMoves* bestMoves, buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE]){

	if ((game->fromType == 'M') && (game->Yfrom == 1) && (game->Yto == 0)){
		if (bestMoves->m.currPos->cnt == 1){
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blackqImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = BLACK_Q;
		}
		else if (bestMoves->m.currPos->cnt == 2){
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blackrImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = BLACK_R;
		}
		else if (bestMoves->m.currPos->cnt == 3){
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blacknImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = BLACK_N;
		}
		else{
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, blackbImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = BLACK_B;
		}
	}


	if ((game->fromType == 'm') && (game->Yfrom == 6) && (game->Yto == 7)){
		if (bestMoves->m.currPos->cnt == 1){
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whiteqImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = WHITE_Q;
		}
		else if (bestMoves->m.currPos->cnt == 2){
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whiterImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = WHITE_R;
		}
		else if (bestMoves->m.currPos->cnt == 3){
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whitenImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = WHITE_N;
		}
		else{
			if (reloadImgToLbl((graphicBoard[game->Xto][game->Yto])->lbl, whitebImg) == 1)
			{
				perror("ERROR: failed reloadImg");
				return ERROR;
			}
			game->board[game->Xto][game->Yto] = WHITE_B;
		}
	}

	return 1;
}
