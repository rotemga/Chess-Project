#ifndef AISETTINGMENU_H_
#define AISETTINGMENU_H_

#include "LoadOrSaveMenu.h"
#ifndef __gnu_linux__

#define backImgFile "images\\BG.bmp"
#define minimaxDepthImgFile "images\\minimaxdepth.bmp"
#define minimax1ImgFile "images\\minimax1.bmp"
#define minimax2ImgFile "images\\minimax2.bmp"
#define minimax3ImgFile "images\\minimax3.bmp"
#define minimax4ImgFile "images\\minimax4.bmp"
#define bestDepthImgFile "images\\bestdepth.bmp"
#define userColorImgFile "images\\usercolor.bmp"
#define whiteImgFile "images\\whitebut.bmp"
#define blackImgFile "images\\blackbut.bmp"
#define continueImgFile "images\\continue.bmp"
#define minimax1PressImgFile "images\\minimax1press.bmp"
#define minimax2PressImgFile "images\\minimax2press.bmp"
#define minimax3PressImgFile "images\\minimax3press.bmp"
#define minimax4PressImgFile "images\\minimax4press.bmp"
#define bestDepthPressImgFile "images\\bestdepthpress.bmp"
#define whitePressImgFile "images\\whitebutpress.bmp"
#define blackPressImgFile "images\\blackbutpress.bmp"

#else

#define backImgFile "images//BG.bmp"
#define minimaxDepthImgFile "images//minimaxdepth.bmp"
#define minimax1ImgFile "images//minimax1.bmp"
#define minimax2ImgFile "images//minimax2.bmp"
#define minimax3ImgFile "images//minimax3.bmp"
#define minimax4ImgFile "images//minimax4.bmp"
#define bestDepthImgFile "images//bestdepth.bmp"
#define userColorImgFile "images//usercolor.bmp"
#define whiteImgFile "images//whitebut.bmp"
#define blackImgFile "images//blackbut.bmp"
#define continueImgFile "images//continue.bmp"
#define minimax1PressImgFile "images//minimax1press.bmp"
#define minimax2PressImgFile "images//minimax2press.bmp"
#define minimax3PressImgFile "images//minimax3press.bmp"
#define minimax4PressImgFile "images//minimax4press.bmp"
#define bestDepthPressImgFile "images//bestdepthpress.bmp"
#define whitePressImgFile "images//whitebutpress.bmp"
#define blackPressImgFile "images//blackbutpress.bmp"

#endif

void unmarkAll(buttonRef btn1, buttonRef btn2, buttonRef btn3, buttonRef btn4, buttonRef btn5);



#endif /* AISETTINGMENU_H_ */
