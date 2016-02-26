TARGET := chessprog
CFLAGS := -g -Wall -std=c99 -pedantic-errors  -lm 
O_FILES:= Main.o ChessLogic.o MiniMax.o ChessRules.o GameFlow.o FilesLogic.o setOrGame.o AIsettingMenu.o GraphicFramework.o LoadOrSaveMenu.o NewGameMenu.o MainMenu.o


all: $(TARGET)


$(TARGET): $(O_FILES)
	gcc -o $(TARGET) $(O_FILES) -lm -std=c99 -pedantic-errors -g `sdl-config --libs`

Main.o: Main.c AIsettingMenu.h LoadOrSaveMenu.h
	gcc -c $(CFLAGS) $*.c `sdl-config --cflags`

ChessLogic.o: ChessLogic.c ChessLogic.h MiniMax.h FilesLogic.h
	gcc -c $(CFLAGS) $*.c

MiniMax.o: MiniMax.c MiniMax.h ChessRules.h
	gcc -c $(CFLAGS) $*.c

ChessRules.o: ChessRules.c ChessRules.h GameFlow.h
	gcc -c $(CFLAGS) $*.c

GameFlow.o: GameFlow.c GameFlow.h Chess.h
	gcc -c $(CFLAGS) $*.c

FilesLogic.o: FilesLogic.c FilesLogic.h Chess.h
	gcc -c $(CFLAGS) $*.c

setOrGame.o: setOrGame.c setOrGame.h GeneralMenus.h
	gcc -c $(CFLAGS) $*.c `sdl-config --cflags`

AIsettingMenu.o: AIsettingMenu.c AIsettingMenu.h LoadOrSaveMenu.h
	gcc -c $(CFLAGS) $*.c `sdl-config --cflags`

GraphicFramework.o: GraphicFramework.c GraphicFramework.h ChessLogic.h
	gcc -c $(CFLAGS) $*.c `sdl-config --cflags`

LoadOrSaveMenu.o: LoadOrSaveMenu.c LoadOrSaveMenu.h MainMenu.h
	gcc -c $(CFLAGS) $*.c `sdl-config --cflags`

NewGameMenu.o: NewGameMenu.c NewGameMenu.h setOrGame.h
	gcc -c $(CFLAGS) $*.c `sdl-config --cflags`

MainMenu.o: MainMenu.c MainMenu.h NewGameMenu.h
	gcc -c $(CFLAGS) $*.c `sdl-config --cflags`





clean:
	-rm $(TARGET) $(O_FILES)

