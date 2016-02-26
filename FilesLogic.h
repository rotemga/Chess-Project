#ifndef FILESLOGIC_H_
#define FILESLOGIC_H_


#include "Chess.h"


GameRef loadGame(char* file, GameRef game);
int readingFile(FILE* gameFile, GameRef game);
int saveGame(char* gameFile, GameRef game);
int fileExists(char* name);


#endif /* FILESLOGIC_H_ */