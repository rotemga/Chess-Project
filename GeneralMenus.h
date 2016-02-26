#ifndef GENERALMENUS_H_
#define GENERALMENUS_H_

#include "GraphicFramework.h"

int mainMenu(windowRef w, GameRef game);
int newGameMenu(windowRef w, GameRef game);
int AIsettingMenu(windowRef w, GameRef game);
int LoadOrSaveMenu(windowRef w, GameRef game, int loadOrSave);
int setOrGame(windowRef w, GameRef game, int setorgame);


#endif /* GENERALMENUS_H_ */