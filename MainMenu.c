#include "MainMenu.h"
#include <stdio.h>

//function for showing the main menu
int mainMenu(windowRef w, GameRef game)
{

	int quit = 0;
	int retVal = 0;
	game->fromType = EMPTY;
	game->nextPlayer = WHITE; //white by default
	game->minimaxDepth = 1;
	game->mode = 1;
	game->Xfrom = -1;
	game->Xto = -1;
	game->Yfrom = -1;
	game->Yto = -1;
	game->userColor = WHITE; //OUR DEFALUT SETTING
	game->computerColor = BLACK; //OUR DEFALUT SETTING
	char board[BOARD_SIZE][BOARD_SIZE];
	init_board(board);
	copyingBoard(board, game->board);

	buttonRef quitBtn = getBtn(quitImgFile, (WSw / 2) - BtnRectWidth / 2, 3.1 * (WSh / 6));
	if (quitBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef loadBtn = getBtn(loadImgFile, (WSw / 2) - BtnRectWidth / 2, 2.3 * (WSh / 6));
	if (loadBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef newGameBtn = getBtn(newGameImgFile, (WSw / 2) - BtnRectWidth / 2, 1.5 * (WSh / 6));
	if (newGameBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	panelRef topPanel = getPanel(0, 0, WSw, WSh);
	if (topPanel == NULL){
		perror("ERROR: failed getPanel");
		return ERROR;
	}

	lableRef topPanelLbl = getLbl(BGImgFile, 0, 0);
	if (topPanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, WSw, WSh);

	if (setAllUnSelected(loadBtn, quitBtn, newGameBtn) != 0){
		perror("ERROR: failed setAllUnSelected");
		return ERROR;
	}
	if (setButtonSelected(newGameBtn, BtnRGB, BtnRGB, BtnRGB) != 0){
		perror("ERROR: failed setButtonSelected");
		return ERROR;
	}


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

		if (drowImgOnLblPnl(topPanelLbl, topPanel) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		// Draw images

		if (drowImgOnBtn(quitBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}
		if (drowImgOnBtn(loadBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}
		if (drowImgOnBtn(newGameBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}


		if (SDL_Flip(w->window) != 0)
		{
			perror("ERROR: failed perform SDL_Flip in MainMenu");
			return ERROR;
		}

		//Poll for keyboard & mouse events
		SDL_Event e = { 0 };
		while (SDL_PollEvent(&e) != 0 && quit == 0 && retVal == 0)
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
				if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(quitBtn, e)){
					quit = QUIT;
					retVal = QUIT;
				}
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(newGameBtn, e)){
										 retVal = newGameMenu(w, game);
										 if ((retVal == QUIT) || (retVal == ERROR))
											 quit = QUIT;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(loadBtn, e)){
										 retVal = LoadOrSaveMenu(w, game, 1);
										 if ((retVal == QUIT) || (retVal == ERROR))
											 quit = QUIT;
									 }
			}
		}
		// add functionality to all buttons here...

		SDL_Delay(0);
	}

	// free allocated mem..
	freePanel(topPanel);
	freeBtn(quitBtn);
	freeBtn(loadBtn);
	freeBtn(newGameBtn);
	freeLbl(topPanelLbl);

	return retVal;
}

//make all the buttons look unpresed
int setAllUnSelected(buttonRef b1, buttonRef b2, buttonRef b3)
{
	if (setButtonUnSelected(b1, BtnRGB, BtnRGB, BtnRGB) == 1){
		perror("ERROR: failed setButtonUnSelected");
		return ERROR;
	}
	if (setButtonUnSelected(b2, BtnRGB, BtnRGB, BtnRGB) == 1){
		perror("ERROR: failed setButtonUnSelected");
		return ERROR;
	}
	if (setButtonUnSelected(b3, BtnRGB, BtnRGB, BtnRGB) == 1){
		perror("ERROR: failed setButtonUnSelected");
		return ERROR;
	}
	return 0;
}



