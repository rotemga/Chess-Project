#ifndef MAINMENU_H_
#define MAINMENU_H_


#include "NewGameMenu.h"

#ifndef __gnu_linux__

#define quitImgFile "images\\quit.bmp"
#define loadImgFile "images\\loadgame.bmp"
#define newGameImgFile "images\\newgame.bmp"
#define BGImgFile "images\\BG.bmp"

#else

#define quitImgFile "images//quit.bmp"
#define loadImgFile "images//loadgame.bmp"
#define newGameImgFile "images//newgame.bmp"
#define BGImgFile "images//BG.bmp"

#endif


//int newGamePress(windowRef W, GameRef game);
//int loadGamePress(windowRef W, GameRef game);
//int quitFunc(windowRef W, GameRef game);
int setAllUnSelected(buttonRef b1, buttonRef b2, buttonRef b3);
#endif /* MAINMENU_H_ */