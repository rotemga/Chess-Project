
#include "GraphicFramework.h"

//generic function for creating a window
windowRef getWindow()
{
	// Initialize SDL and make sure it quits
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		perror("ERROR: unable to init SDL\n");
		return NULL;
	}
	atexit(SDL_Quit);

	// Create window surface
	SDL_WM_SetCaption("CHESS GAME", "CHESS GAME");

	windowRef w = (windowRef)malloc(sizeof(window));
	if (w == NULL)
		return NULL;

	w->window = SDL_SetVideoMode(WSw, WSh, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (w->window == NULL)
	{
		perror("ERROR: failed to set video mode\n");
		return NULL;
	}
	return w;
}


//function for freeing the window
void freeWindow(windowRef w)
{
	SDL_FreeSurface(w->window);
	free(w);
}


//generic function for creating a lable
lableRef getLbl(char* imgfile, int x, int y)
{
	lableRef newLbl = (lableRef)malloc(sizeof(lable));
	if (newLbl == NULL)
		return NULL;
	newLbl->LblRect.w = BtnRectWidth;
	newLbl->LblRect.h = BtnRectHight;
	newLbl->LblRect.x = x;
	newLbl->LblRect.y = y;
	if (imgfile == NULL)
		newLbl->LblImg = NULL;
	else
	{
		SDL_Surface* optimizedImage = LoadTransparent(imgfile);
		newLbl->LblImg = optimizedImage;
		if (newLbl->LblImg == NULL)
		{
			perror("ERROR: failed to load image\n");
			return NULL;
		}
	}
	return newLbl;
}

SDL_Surface* LoadTransparent(char* imgfile){

	/* Temporary storage for the image that's loaded */
	SDL_Surface* loadedImage = NULL;

	/*The optimized image that will be used*/
	SDL_Surface* optimizedImage = NULL;
	Uint32 colorkey;

	/*Load the image*/
	loadedImage = SDL_LoadBMP(imgfile);

	/* If something went wrong in loading the image */
	if (loadedImage == NULL)
	{
		printf("\n FILE: %s", imgfile);
		return NULL;
	}

	/*Create an optimized image*/
	optimizedImage = SDL_DisplayFormat(loadedImage);
	/*Free the old image*/
	SDL_FreeSurface(loadedImage);

	/*If the image wasn't optimized*/
	if (optimizedImage == NULL)
	{
		return NULL;
	}

	/* Map the color key */
	colorkey = SDL_MapRGB(optimizedImage->format, 255, 0, 255);
	/*Set all pixels of color magnata = RGB(255, 0 ,255) to be transparent
	SDL_SRCCOLORKEY - is for transparency*/
	if (SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey) == -1)
	{
		return NULL;
	}
	return optimizedImage;

}


//function for freeing lable
void freeLbl(lableRef lbl)
{
	SDL_FreeSurface(lbl->LblImg);
	free(lbl);
}

//generic function for creating a button
buttonRef getBtn(char* imgfile, int x, int y)
{
	buttonRef newBtn = (buttonRef)malloc(sizeof(button));

	if (newBtn == NULL)
		return NULL;

	lableRef btnLbl = getLbl(imgfile, x, y);
	if (btnLbl == NULL)
		return NULL;

	newBtn->lbl = btnLbl;

	return newBtn;
}

//function fot freeing button
void freeBtn(buttonRef btn)
{
	freeLbl(btn->lbl);
	free(btn);
}

//generic function for creating a panel
panelRef getPanel(int x, int y, int h, int w)
{
	panelRef newPanel = (panelRef)malloc(sizeof(panel));
	if (newPanel == NULL)
		return NULL;
	newPanel->PanelSurface = SDL_SetVideoMode(WSw, WSh, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (newPanel->PanelSurface == NULL)
	{
		perror("ERROR: failed to set video mode\n");
		return NULL;
	}
	newPanel->x = x;
	newPanel->y = y;
	newPanel->hight = h;
	newPanel->width = w;

	setPanelRect(newPanel, x, y, h, w);
	return newPanel;

}

//function for freeing panel
void freePanel(panelRef pnl)
{
	SDL_FreeSurface(pnl->PanelSurface);
	free(pnl);
}

//function for checking if abutton aws pressed
bool BtnArea(buttonRef btn, SDL_Event e)
{
	return ((e.button.x > (btn->lbl)->LblRect.x)
		&& (e.button.x < (btn->lbl)->LblRect.x + (btn->lbl)->LblRect.w)
		&& (e.button.y >(btn->lbl)->LblRect.y)
		&& (e.button.y < (btn->lbl)->LblRect.y + (btn->lbl)->LblRect.h)) ?
		true : false;
}

//function for checking if a panel was pressed
bool PanelArea(panelRef pnl, SDL_Event e)
{
	return ((e.button.x > pnl->x) && (e.button.x < pnl->x + pnl->width)
		&& (e.button.y > pnl->y) && (e.button.y < pnl->y + pnl->hight)) ?
		true : false;
}

//helping function to update panel vals
void setPanelRect(panelRef pnl, int x, int y, int h, int w)
{
	(pnl->PnlRect).x = x;
	(pnl->PnlRect).y = y;
	(pnl->PnlRect).w = w;
	(pnl->PnlRect).h = h;
}

int fillWindow(windowRef w, int r, int g, int b)
{
	if (SDL_FillRect(w->window, 0, SDL_MapRGB((w->window)->format, r, g, b))
		!= 0)
	{
		perror("ERROR: failed to draw rect\n");
		return 1;
	}
	return 0;
}

int fillPanel(panelRef pnl, int r, int g, int b)
{
	if (SDL_FillRect(pnl->PanelSurface, 0,
		SDL_MapRGB((pnl->PanelSurface)->format, r, g, b)) != 0)
	{
		perror("ERROR: failed to draw rect\n");
		return 1;
	}
	return 0;
}


//the function draw an image on the lable panel.
int drowImgOnLblPnl(lableRef lbl, panelRef pnl)
{
	return (drowImgOnLblGeneric(lbl, pnl->PanelSurface));
}

//the function draw an image on the button.
int drowImgOnBtn(buttonRef btn, windowRef w)
{
	return (drowImgOnLblGeneric(btn->lbl, w->window));
}

//the function draw an image on the lable.
int drowImgOnLbl(lableRef lbl, windowRef w)
{
	return (drowImgOnLblGeneric(lbl, w->window));
}

int drowImgOnLblGeneric(lableRef lbl, SDL_Surface *sur)
{
	if (SDL_BlitSurface(lbl->LblImg, NULL, sur, &(lbl->LblRect)) != 0)
	{
		SDL_FreeSurface(lbl->LblImg);
		perror("ERROR: failed to built image\n");
		return 1;
	}
	return 0;
}

//the function reloads image to button.
int reloadImgToBtn(buttonRef btn, char* newImgFile)
{
	SDL_FreeSurface((btn->lbl)->LblImg);
	(btn->lbl)->LblImg = LoadTransparent(newImgFile);
	if ((btn->lbl)->LblImg == NULL)
	{
		perror("ERROR: failed to load image\n");
		return 1;
	}
	return 0;
}

//the function reloads image to lable.
int reloadImgToLbl(lableRef lbl, char* newImgFile)
{
	SDL_FreeSurface(lbl->LblImg);
	lbl->LblImg = LoadTransparent(newImgFile);
	if (lbl->LblImg == NULL)
	{
		perror("ERROR: failed to load image\n");
		return 1;
	}
	return 0;
}

int putPanelInWindow(panelRef pnl, windowRef w)
{
	if (SDL_BlitSurface(pnl->PanelSurface, NULL, w->window, &(pnl->PnlRect))
		!= 0)
	{
		//SDL_FreeSurface(gamePanelBtn->BtnImg);
		perror("ERROR: failed to built image\n");
		return 1;
	}
	return 0;
}

//set the lable hight and weight
void setLblHightWigth(lableRef lbl, int h, int w)
{
	(lbl)->LblRect.h = h;
	(lbl)->LblRect.w = w;
}

int setButtonUnSelected(buttonRef btn, int red, int green, int blue)
{
	// we will use rgb map of (9,9,9) as a mark for selection of a button
	if (SDL_SetColorKey((btn->lbl)->LblImg, SDL_SRCCOLORKEY,
		SDL_MapRGB(((btn->lbl)->LblImg)->format, red, green, blue)) != 0)
	{
		perror("ERROR: failed to set color key\n");
		SDL_FreeSurface((btn->lbl)->LblImg);
		return 1;
	}
	return 0;
}

int setButtonSelected(buttonRef btn, int red, int green, int blue)
{
	if (SDL_SetColorKey((btn->lbl)->LblImg, 0,
		SDL_MapRGB(((btn->lbl)->LblImg)->format, red, green, blue)) != 0)
	{
		perror("ERROR: failed to set color key\n");
		SDL_FreeSurface((btn->lbl)->LblImg);
		return 1;
	}
	return 0;
}


