

#ifndef LOADORSAVEMENU_C_
#define LOADORSAVEMENU_C_

#include "LoadOrSaveMenu.h"

//function for starting the load or save menu (1 is load, 2 is save)
int LoadOrSaveMenu(windowRef w, GameRef game, int loadOrSave)
{

	int quit = 0;
	int retVal = 0;
	char* slotNum = "0";
	char fileName[12];


	buttonRef slots[SLOTSNUM];
	for (int col = 0; col < SLOTSNUM; col++)
	{
		if (col == 0)
			slots[col] = getBtn(game1ImgFile, (WSw / 4) - BtnRectWidth / 2 - 40, (1.2 + 0.7*col) * (WSh / 6) + 20);
		if (col == 1)
			slots[col] = getBtn(game2ImgFile, (WSw / 4) - BtnRectWidth / 2 - 40, (1.2 + 0.7*col) * (WSh / 6) + 20);
		if (col == 2)
			slots[col] = getBtn(game3ImgFile, (WSw / 4) - BtnRectWidth / 2 - 40, (1.2 + 0.7*col) * (WSh / 6) + 20);
		if (col == 3)
			slots[col] = getBtn(game4ImgFile, (WSw / 4) - BtnRectWidth / 2 + 260, (1.2 + 0.7*(col - 3)) * (WSh / 6) + 20);
		if (col == 4)
			slots[col] = getBtn(game5ImgFile, (WSw / 4) - BtnRectWidth / 2 + 260, (1.2 + 0.7*(col - 3)) * (WSh / 6) + 20);
		if (col == 5)
			slots[col] = getBtn(game6ImgFile, (WSw / 4) - BtnRectWidth / 2 + 260, (1.2 + 0.7*(col - 3)) * (WSh / 6) + 20);
		if (col == 6)
			slots[col] = getBtn(game7ImgFile, (WSw / 4) - BtnRectWidth / 2 + 560, (1.2 + 0.7*(col - 6)) * (WSh / 6) + 20);
		if (col == 7)
			slots[col] = getBtn(game8ImgFile, (WSw / 4) - BtnRectWidth / 2 + 560, (1.2 + 0.7*(col - 6)) * (WSh / 6) + 20);
		if (col == 8)
			slots[col] = getBtn(game9ImgFile, (WSw / 4) - BtnRectWidth / 2 + 560, (1.2 + 0.7*(col - 6)) * (WSh / 6) + 20);
		if (col == 9)
			slots[col] = getBtn(game10ImgFile, (WSw / 4) - BtnRectWidth / 2 + 560, (1.2 + 0.7*(col - 6)) * (WSh / 6) + 20);
	}



	buttonRef loadBtn = getBtn(loadTheGameImgFile, (WSw / 2) - BtnRectWidth / 2, 3.8 * (WSh / 6));
	if (loadBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef saveBtn = getBtn(saveAndReturnImgFile, (WSw / 2) - BtnRectWidth / 2, 4.2 * (WSh / 6));
	if (saveBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef cancelBtn = getBtn(cancelImgFile, (WSw / 2) - BtnRectWidth / 2, 4.4 * (WSh / 6));
	if (saveBtn == NULL){
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

	lableRef whitePanelLbl = getLbl(halfWhiteRecImgFile, (WSw / 2) - 200, (WSh / 2) + 250);
	if (whitePanelLbl == NULL){
		perror("ERROR: failed getLable");
		return ERROR;
	}
	setLblHightWigth(topPanelLbl, 385, 32);

	panelRef messegePanel = getPanel(0, 0, WSw, WSh);
	if (messegePanel == NULL){
		perror("ERROR: failed getPanel");
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



		if (loadOrSave == 1){
			if (drowImgOnBtn(loadBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}

			if (drowImgOnBtn(cancelBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}
		}
		else{
			if (drowImgOnBtn(saveBtn, w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}
		}

		if (drowImgOnLblPnl(whitePanelLbl, messegePanel) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		for (int col = 0; col < SLOTSNUM; col++)
		{
			if (drowImgOnBtn(slots[col], w) == 1)
			{
				quit = QUIT;
				retVal = ERROR;
				perror("ERROR: failed drowImg");
				break;
			}
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
				if (SLOTSNUM >= 1){
					if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[0], e)){
						unmarkAllGames(slots);
						reloadImgToBtn(slots[0], game1PressImgFile);
						reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
						slotNum = "1";
					}
				}
									 if (SLOTSNUM >= 2){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[1], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[1], game2PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "2";
										 }
									 }
									 if (SLOTSNUM >= 3){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[2], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[2], game3PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "3";
										 }
									 }
									 if (SLOTSNUM >= 4){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[3], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[3], game4PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "4";
										 }
									 }
									 if (SLOTSNUM >= 5){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[4], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[4], game5PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "5";
										 }
									 }
									 if (SLOTSNUM >= 6){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[5], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[5], game6PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "6";
										 }
									 }
									 if (SLOTSNUM >= 7){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[6], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[6], game7PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "7";
										 }
									 }
									 if (SLOTSNUM >= 8){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[7], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[7], game8PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "8";
										 }
									 }
									 if (SLOTSNUM >= 9){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[8], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[8], game9PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "9";
										 }
									 }
									 if (SLOTSNUM >= 10){
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(slots[9], e)){
											 unmarkAllGames(slots);
											 reloadImgToBtn(slots[9], game10PressImgFile);
											 reloadImgToLbl(whitePanelLbl, halfWhiteRecImgFile);
											 slotNum = "10";
										 }
									 }

									 if (loadOrSave == 1){ //load case
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(loadBtn, e) && (strcmp(slotNum, "0") != 0)){
											 strcpy(fileName, "chess");
											 strcat(fileName, slotNum);
											 strcat(fileName, ".xml");
											 if (fileExists(fileName) == 0){ //the file exist
												 game = loadGame(fileName, game);
												 retVal = newGameMenu(w, game);
												 if ((retVal == QUIT) || (retVal == ERROR))
													 quit = QUIT;
											 }
											 else
											 {
												 if (reloadImgToLbl(whitePanelLbl, gameNotFoundImgFile) == 1){
													 perror("ERROR: failed reloadImg");
													 return ERROR;
												 }
											 }
										 }
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(cancelBtn, e)){
											 quit = QUIT;
											 retVal = mainMenu(w, game);
											 if ((retVal == QUIT) || (retVal == ERROR))
												 quit = QUIT;
										 }
									 }
									 else{
										 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(saveBtn, e)){
											 strcpy(fileName, "chess");
											 strcat(fileName, slotNum);
											 strcat(fileName, ".xml");
											 int succ = saveGame(fileName, game);
											 if (succ == 0)
												 quit = QUIT;
										 }
									 }
			}
			// add functionality to all buttons here...
		}

		SDL_Delay(0);
	}




	// free allocated mem..
	freePanel(topPanel);
	freeBtn(loadBtn);
	freeBtn(saveBtn);
	freeBtn(cancelBtn);
	freeLbl(topPanelLbl);
	freeLbl(whitePanelLbl);
	freePanel(messegePanel);
	for (int i = 0; i < SLOTSNUM; i++)
		freeBtn(slots[i]);

	return retVal;
}

//make all the buttons look unpresed
void unmarkAllGames(buttonRef slots[SLOTSNUM]){
	if (SLOTSNUM >= 1)
		reloadImgToBtn(slots[0], game1ImgFile);
	if (SLOTSNUM >= 2)
		reloadImgToBtn(slots[1], game2ImgFile);
	if (SLOTSNUM >= 3)
		reloadImgToBtn(slots[2], game3ImgFile);
	if (SLOTSNUM >= 4)
		reloadImgToBtn(slots[3], game4ImgFile);
	if (SLOTSNUM >= 5)
		reloadImgToBtn(slots[4], game5ImgFile);
	if (SLOTSNUM >= 6)
		reloadImgToBtn(slots[5], game6ImgFile);
	if (SLOTSNUM >= 7)
		reloadImgToBtn(slots[6], game7ImgFile);
	if (SLOTSNUM >= 8)
		reloadImgToBtn(slots[7], game8ImgFile);
	if (SLOTSNUM >= 9)
		reloadImgToBtn(slots[8], game9ImgFile);
	if (SLOTSNUM >= 10)
		reloadImgToBtn(slots[9], game10ImgFile);
}




#endif /* LOADORSAVEMENU_C_ */