#ifndef SETORGAME_H_
#define SETORGAME_H_


#include "GeneralMenus.h"

#define cubeSize 52

#ifndef __gnu_linux__

#define blankBGImgFile "images\\blankBG.bmp"
#define chessBoardImgFile "images\\chessboard.bmp"
#define setAndReturnImgFile "images\\setreturn.bmp"
#define saveGameImgFile "images\\ssavegame.bmp"
#define mainMenuImgFile "images\\smainmenu.bmp"
#define seeBestImgFile "images\\seebestmove.bmp"
#define seeBestLevelImgFile "images\\seebestmovelevel.bmp"
#define squitImgFile "images\\squit.bmp"
#define whitepImg "images\\Wpawn.bmp"
#define whitebImg "images\\Wbishop.bmp"
#define whiterImg "images\\Wrook.bmp"
#define whitenImg "images\\Wknight.bmp"
#define whiteqImg "images\\Wqueen.bmp"
#define whitekImg "images\\Wking.bmp"
#define blackpImg "images\\Bpawn.bmp"
#define blackbImg "images\\Bbishop.bmp"
#define blackrImg "images\\Brook.bmp"
#define blacknImg "images\\Bknight.bmp"
#define blackqImg "images\\Bqueen.bmp"
#define blackkImg "images\\Bking.bmp"
#define freeTileImg "images\\freetile.bmp"
#define removeImg "images\\remove.bmp"
#define instrucImg "images\\instruc.bmp"
#define blackTurnImg "images\\blackturn.bmp"
#define whiteTurnImg "images\\whiteturn.bmp"
#define illegalMoveImg "images\\illegalmove.bmp"
#define whiteRecImg "images\\whiterec.bmp"
#define whiteRecLowImg "images\\whiterecl.bmp"
#define checkImg "images\\check.bmp"
#define mateImg "images\\mate.bmp"
#define tieImg "images\\tie.bmp"
#define startImg "images\\start.bmp"
#define rejectImg "images\\cancelmove.bmp"
#define acceptImg "images\\accept.bmp"
#define smallwhiterecImg "images\\smallwhiterec.bmp"
#define promotblackImg "images\\promotblack.bmp"
#define promotwhiteImg "images\\promotwhite.bmp"
#define promotTileImg "images\\promottile.bmp"
#define illegalBoardImg "images\\illegalboard.bmp"
#define gameInstImg "images\\gameinst.bmp"
#define loadingImg "images\\loading.bmp"
#define loadingBestImg "images\\loadingbest.bmp"
#define initBoardImg "images\\initboard.bmp"




#else


#define blankBGImgFile "images//blankBG.bmp"
#define chessBoardImgFile "images//chessboard.bmp"
#define setAndReturnImgFile "images//setreturn.bmp"
#define saveGameImgFile "images//ssavegame.bmp"
#define mainMenuImgFile "images//smainmenu.bmp"
#define seeBestImgFile "images//seebestmove.bmp"
#define seeBestLevelImgFile "images//seebestmovelevel.bmp"
#define squitImgFile "images//squit.bmp"
#define whitepImg "images//Wpawn.bmp"
#define whitebImg "images//Wbishop.bmp"
#define whiterImg "images//Wrook.bmp"
#define whitenImg "images//Wknight.bmp"
#define whiteqImg "images//Wqueen.bmp"
#define whitekImg "images//Wking.bmp"
#define blackpImg "images//Bpawn.bmp"
#define blackbImg "images//Bbishop.bmp"
#define blackrImg "images//Brook.bmp"
#define blacknImg "images//Bknight.bmp"
#define blackqImg "images//Bqueen.bmp"
#define blackkImg "images//Bking.bmp"
#define removeImg "images//remove.bmp"
#define instrucImg "images//instruc.bmp"
#define blackTurnImg "images//blackturn.bmp"
#define whiteTurnImg "images//whiteturn.bmp"
#define illegalMoveImg "images//illegalmove.bmp"
#define whiteRecImg "images//whiterec.bmp"
#define whiteRecLowImg "images//whiterecl.bmp"
#define checkImg "images//check.bmp"
#define mateImg "images//mate.bmp"
#define tieImg "images//tie.bmp"
#define startImg "images//start.bmp"
#define rejectImg "images//cancelmove.bmp"
#define acceptImg "images//accept.bmp"
#define smallwhiterecImg "images//smallwhiterec.bmp"
#define promotblackImg "images//promotblack.bmp"
#define promotwhiteImg "images//promotwhite.bmp"
#define promotTileImg "images//promottile.bmp"
#define illegalBoardImg "images//illegalboard.bmp"
#define freeTileImg "images//freetile.bmp"
#define gameInstImg "images//gameinst.bmp"
#define loadingImg "images//loading.bmp"
#define loadingBestImg "images//loadingbest.bmp"
#define initBoardImg "images//initboard.bmp"


#endif



void setImgOnBoard(GameRef game, buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE]);
int gameBoardPress(GameRef game, int setORgame, buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE]);
char* imgName(char letter);
int promotMinimax(GameRef game, listMoves* bestMoves, buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE]);
void freeGraphicBoard(buttonRef graphicBoard[BOARD_SIZE][BOARD_SIZE]);


#endif /* SETORGAME_H_ */