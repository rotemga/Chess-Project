#ifndef LOADORSAVEMENU_H_
#define LOADORSAVEMENU_H_

#include "MainMenu.h"


#define SLOTSNUM 7
//***in order to change the slot number change the SLOTNUM to a val between 1-10 (no other changes are needed)***


#ifndef __gnu_linux__

#define backImgFile "images\\BG.bmp"
#define cancelImgFile "images\\cancel.bmp"
#define game1ImgFile "images\\game1.bmp"
#define game1PressImgFile "images\\game1press.bmp"
#define game2ImgFile "images\\game2.bmp"
#define game2PressImgFile "images\\game2press.bmp"
#define game3ImgFile "images\\game3.bmp"
#define game3PressImgFile "images\\game3press.bmp"
#define game4ImgFile "images\\game4.bmp"
#define game4PressImgFile "images\\game4press.bmp"
#define game5ImgFile "images\\game5.bmp"
#define game5PressImgFile "images\\game5press.bmp"
#define game6ImgFile "images\\game6.bmp"
#define game6PressImgFile "images\\game6press.bmp"
#define game7ImgFile "images\\game7.bmp"
#define game7PressImgFile "images\\game7press.bmp"
#define game8ImgFile "images\\game8.bmp"
#define game8PressImgFile "images\\game8press.bmp"
#define game9ImgFile "images\\game9.bmp"
#define game9PressImgFile "images\\game9press.bmp"
#define game10ImgFile "images\\game10.bmp"
#define game10PressImgFile "images\\game10press.bmp"
#define saveAndReturnImgFile "images\\savereturn.bmp"
#define loadTheGameImgFile "images\\load.bmp"
#define halfWhiteRecImgFile "images\\halfwhiterec.bmp"
#define gameNotFoundImgFile "images\\gamenotfound.bmp"



#else

#define backImgFile "images//BG.bmp"
#define cancelImgFile "images//cancel.bmp"
#define game1ImgFile "images//game1.bmp"
#define game1PressImgFile "images//game1press.bmp"
#define game2ImgFile "images//game2.bmp"
#define game2PressImgFile "images//game2press.bmp"
#define game3ImgFile "images//game3.bmp"
#define game3PressImgFile "images//game3press.bmp"
#define game4ImgFile "images//game4.bmp"
#define game4PressImgFile "images//game4press.bmp"
#define game5ImgFile "images//game5.bmp"
#define game5PressImgFile "images//game5press.bmp"
#define game6ImgFile "images//game6.bmp"
#define game6PressImgFile "images//game6press.bmp"
#define game7ImgFile "images//game7.bmp"
#define game7PressImgFile "images//game7press.bmp"
#define game8ImgFile "images//game8.bmp"
#define game8PressImgFile "images//game8press.bmp"
#define game9ImgFile "images//game9.bmp"
#define game9PressImgFile "images//game9press.bmp"
#define game10ImgFile "images//game10.bmp"
#define game10PressImgFile "images//game10press.bmp"
#define saveAndReturnImgFile "images//savereturn.bmp"
#define loadTheGameImgFile "images//load.bmp"
#define halfWhiteRecImgFile "images//halfwhiterec.bmp"
#define gameNotFoundImgFile "images//gamenotfound.bmp"

#endif


void unmarkAllGames(buttonRef slots[SLOTSNUM]);


#endif /* LOADORSAVEMENU_H_ */


