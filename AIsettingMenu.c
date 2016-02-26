#ifndef AISETTINGMENU_C_
#define AISETTINGMENU_C_

#include "AIsettingMenu.h"

// function for showing the AI menu and editing the felevent settings
int AIsettingMenu(windowRef w, GameRef game)
{

	int quit = 0;
	int retVal = 0;


	buttonRef continueBtn = getBtn(continueImgFile, (WSw / 2) - BtnRectWidth / 2, 4.8 * (WSh / 6));
	if (continueBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef minimaxDepthBtn = getBtn(minimaxDepthImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 1.15 * (WSh / 6));
	if (minimaxDepthBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef minimax1Btn = getBtn(minimax1ImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 1.6 * (WSh / 6));
	if (minimax1Btn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef minimax2Btn = getBtn(minimax2ImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 2.2 * (WSh / 6));
	if (minimax2Btn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef minimax3Btn = getBtn(minimax3ImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 2.8 * (WSh / 6));
	if (minimax3Btn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef minimax4Btn = getBtn(minimax4ImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 3.4 * (WSh / 6));
	if (minimax4Btn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef bestDepthBtn = getBtn(bestDepthImgFile, (3 * WSw / 4) - BtnRectWidth / 2, 4 * (WSh / 6));
	if (bestDepthBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef userColorBtn = getBtn(userColorImgFile, (WSw / 4) - BtnRectWidth / 2, 1.15 * (WSh / 6));
	if (userColorBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef whiteBtn = getBtn(whiteImgFile, (WSw / 4) - BtnRectWidth / 2, 1.6 * (WSh / 6));
	if (whiteBtn == NULL){
		perror("ERROR: failed getBtn");
		return ERROR;
	}

	buttonRef blackBtn = getBtn(blackImgFile, (WSw / 4) - BtnRectWidth / 2, 2.2 * (WSh / 6));
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
		perror("ERROR: failed getLabel");
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


		if (drowImgOnBtn(continueBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}
		if (drowImgOnBtn(minimaxDepthBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(minimax1Btn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(minimax2Btn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(minimax3Btn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(minimax4Btn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(bestDepthBtn, w) == 1)
		{
			quit = QUIT;
			retVal = ERROR;
			perror("ERROR: failed drowImg");
			break;
		}

		if (drowImgOnBtn(userColorBtn, w) == 1)
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
				if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(continueBtn, e)){
					quit = QUIT;
					retVal = setOrGame(w, game, 2);
				}
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(minimax1Btn, e)){
										 unmarkAll(minimax1Btn, minimax2Btn, minimax3Btn, minimax4Btn, bestDepthBtn);
										 reloadImgToBtn(minimax1Btn, minimax1PressImgFile);
										 game->minimaxDepth = 1;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(minimax2Btn, e)){
										 unmarkAll(minimax1Btn, minimax2Btn, minimax3Btn, minimax4Btn, bestDepthBtn);
										 reloadImgToBtn(minimax2Btn, minimax2PressImgFile);
										 game->minimaxDepth = 2;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(minimax3Btn, e)){
										 unmarkAll(minimax1Btn, minimax2Btn, minimax3Btn, minimax4Btn, bestDepthBtn);
										 reloadImgToBtn(minimax3Btn, minimax3PressImgFile);
										 game->minimaxDepth = 3;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(minimax4Btn, e)){
										 unmarkAll(minimax1Btn, minimax2Btn, minimax3Btn, minimax4Btn, bestDepthBtn);
										 reloadImgToBtn(minimax4Btn, minimax4PressImgFile);
										 game->minimaxDepth = 4;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(bestDepthBtn, e)){
										 unmarkAll(minimax1Btn, minimax2Btn, minimax3Btn, minimax4Btn, bestDepthBtn);
										 reloadImgToBtn(bestDepthBtn, bestDepthPressImgFile);
										 game->minimaxDepth = 5;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(whiteBtn, e)){
										 reloadImgToBtn(whiteBtn, whitePressImgFile);
										 reloadImgToBtn(blackBtn, blackImgFile);
										 game->userColor = WHITE;
										 game->computerColor = BLACK;
									 }
									 if ((e.button.button == SDL_BUTTON_LEFT) && BtnArea(blackBtn, e)){
										 reloadImgToBtn(blackBtn, blackPressImgFile);
										 reloadImgToBtn(whiteBtn, whiteImgFile);
										 game->userColor = BLACK;
										 game->computerColor = WHITE;
									 }




			}

		}
		SDL_Delay(0);
	}



	// free allocated mem
	freePanel(topPanel);
	freeBtn(continueBtn);
	freeBtn(minimaxDepthBtn);
	freeBtn(minimax1Btn);
	freeBtn(minimax2Btn);
	freeBtn(minimax3Btn);
	freeBtn(minimax4Btn);
	freeBtn(bestDepthBtn);
	freeBtn(whiteBtn);
	freeBtn(blackBtn);
	freeLbl(topPanelLbl);
	freeBtn(userColorBtn);

	return retVal;
}

void unmarkAll(buttonRef btn1, buttonRef btn2, buttonRef btn3, buttonRef btn4, buttonRef btn5){
	reloadImgToBtn(btn1, minimax1ImgFile);
	reloadImgToBtn(btn2, minimax2ImgFile);
	reloadImgToBtn(btn3, minimax3ImgFile);
	reloadImgToBtn(btn4, minimax4ImgFile);
	reloadImgToBtn(btn5, bestDepthImgFile);
}

#endif /* AISETTINGMENU_C_ */