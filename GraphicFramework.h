
#ifndef GRAPHICFRAMEWORK_H_
#define GRAPHICFRAMEWORK_H_

#include "SDL.h"
#include "SDL_video.h"
#include <stdio.h>
#include <stdbool.h>
#include "ChessLogic.h"

#define WSw 1024
#define WSh 768
#define BtnRectWidth 265
#define BtnRectHight 60

#define BtnRGB 9
#define BG_RED 131
#define BG_GREEN 159
#define BG_BLUE 199

#define QUIT 3
#define ERROR 2

typedef struct window
{
	SDL_Surface *window;
} window;

typedef window* windowRef;

typedef struct lable
{
	SDL_Rect LblRect;
	SDL_Surface *LblImg;
} lable;
typedef lable* lableRef;

typedef struct button
{
	lableRef lbl;
} button;

typedef button* buttonRef;

typedef struct panel
{
	SDL_Rect PnlRect;
	SDL_Surface *PanelSurface;
	int x;
	int y;
	int hight;
	int width;
} panel;
typedef panel* panelRef;


windowRef getWindow();
void freeWindow(windowRef w);
lableRef getLbl(char*, int, int);
void freeLbl(lableRef lbl);
buttonRef getBtn(char* imgfile, int x, int y);
void freeBtn(buttonRef btn);
panelRef getPanel(int, int, int, int);
void freePanel(panelRef pnl);
bool BtnArea(buttonRef btn, SDL_Event e);
bool PanelArea(panelRef pnl, SDL_Event e);
void setPanelRect(panelRef pnl, int x, int y, int h, int w);
int fillWindow(windowRef w, int r, int g, int b);
int drowImgOnBtn(buttonRef btn, windowRef w);
int drowImgOnLblPnl(lableRef lbl, panelRef pnl);
int drowImgOnLblGeneric(lableRef lbl, SDL_Surface *sur);
int reloadImgToBtn(buttonRef btn, char* newImgFile);
int reloadImgToLbl(lableRef lbl, char* newImgFile);
int fillPanel(panelRef pnl, int r, int g, int b);
int putPanelInWindow(panelRef pnl, windowRef w);
void setLblHightWigth(lableRef lbl, int h, int w);
int setButtonUnSelected(buttonRef btn, int red, int green, int blue);
int setButtonSelected(buttonRef btn, int red, int green, int blue);
SDL_Surface* LoadTransparent(char* imgfile);


#endif /* GRAPHICFRAMEWORK_H_ */