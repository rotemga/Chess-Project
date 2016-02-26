
#ifndef NEWGAMEMENU_C_
#define NEWGAMEMENU_C_

#include "NewGameMenu.h"

//show the new gamw menu.
int newGameMenu(windowRef w, GameRef game)
{

	int quit = 0;
	int retVal = 0;


	buttonRef cancelBtn = getBtn(cancelImgFile, (WSw / 2) - BtnRectWidth / 2, 4.2 * (WSh / 6));
	if (cancelBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef continueBtn = getBtn(continueImgFile, (WSw / 2) - BtnRectWidth / 2, 3.6 * (WSh / 6));
	if (continueBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef setBoardBtn = getBtn(setBoardImgFile, (WSw / 2) - BtnRectWidth / 2, 3 * (WSh / 6));
	if (setBoardBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef playerSelectionBtn = getBtn(playerSelectionImgFile, (WSw / 4) - BtnRectWidth / 2, 1.15 * (WSh / 6));
	if (playerSelectionBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef playerVsPlayerBtn = getBtn(playerVsPlayerImgFile, (WSw / 4) - BtnRectWidth / 2, 1.6 * (WSh / 6));
	if (playerVsPlayerBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef playerVsComputerBtn = getBtn(playerVsComputerImgFile, (WSw / 4) - BtnRectWidth / 2, 2.2 * (WSh / 6));
	if (playerVsComputerBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef nextPlayerBtn = getBtn(nextPlayerImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 1.15 * (WSh / 6));
	if (nextPlayerBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef whiteBtn = getBtn(whiteImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 1.6 * (WSh / 6));
	if (whiteBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef blackBtn = getBtn(blackImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 2.2 * (WSh / 6));
	if (blackBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	panelRef topPanel = getPanel(0, 0, WSw, WSh);
	if (topPanel == NULL){
		perror("ERROR: failed getPanel");
		return ERROR;
	}

	lableRef topPanelLbl = getLbl(backImgFile, 0, 0);
	if (topPanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, WSw, WSh);


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

		if (drowImgOnBtn(cancelBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}
		if (drowImgOnBtn(continueBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}
		if (drowImgOnBtn(setBoardBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(playerSelectionBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(playerVsPlayerBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(playerVsComputerBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(nextPlayerBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(whiteBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(blackBtn, w) == 1)
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
			case (SDL_QUIT) : {
				quit = QUIT;
				retVal = QUIT;
			}
							  break;
			case (SDL_KEYUP) :
				if (e.key.keysym.sym == SDLK_ESCAPE){
					quit = QUIT;
					retVal = QUIT;
				}
			case (SDL_MOUSEBUTTONUP) :
				if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(cancelBtn, e)){
					quit = QUIT;
					retVal = mainMenu(w, game);
					if ((retVal == QUIT) || (retVal == ERROR))
						quit = QUIT;
				}
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(setBoardBtn, e)){
										 retVal = setOrGame(w, game, 1);
										 if ((retVal == QUIT) || (retVal == ERROR))
											 quit = QUIT;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && (BtnArea(continueBtn, e))){
										 if (game->mode == 1){
											 retVal = setOrGame(w, game, 2);
											 if ((retVal == QUIT) || (retVal == ERROR))
												 quit = QUIT;
										 }
										 else{
											 retVal = AIsettingMenu(w, game);
											 if ((retVal == QUIT) || (retVal == ERROR))
												 quit = QUIT;
										 }
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(whiteBtn, e)){
										 reloadImgToBtn(whiteBtn, whiteButPressImgFile);
										 reloadImgToBtn(blackBtn, blackImgFile);
										 game->nextPlayer = WHITE;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(blackBtn, e)){
										 reloadImgToBtn(blackBtn, blackButPressImgFile);
										 reloadImgToBtn(whiteBtn, whiteImgFile);
										 game->nextPlayer = BLACK;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(playerVsPlayerBtn, e)){
										 reloadImgToBtn(playerVsPlayerBtn, playerVsPlayerPressImgFile);
										 reloadImgToBtn(playerVsComputerBtn, playerVsComputerImgFile);
										 game->mode = 1;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(playerVsComputerBtn, e)){
										 reloadImgToBtn(playerVsComputerBtn, playerVsComputerPressImgFile);
										 reloadImgToBtn(playerVsPlayerBtn, playerVsPlayerImgFile);
										 game->mode = 2;
									 }
			}
			// add functionality to all buttons here...

		}
		SDL_Delay(0);
	}



	// free allocated mem..
	freePanel(topPanel);
	freeBtn(cancelBtn);
	freeBtn(continueBtn);
	freeBtn(setBoardBtn);
	freeBtn(playerSelectionBtn);
	freeBtn(playerVsPlayerBtn);
	freeBtn(playerVsComputerBtn);
	freeBtn(nextPlayerBtn);
	freeBtn(whiteBtn);
	freeBtn(blackBtn);
	freeLbl(topPanelLbl);

	return retVal;
}






#endif /* NEWGAMEMENU_C_ */
