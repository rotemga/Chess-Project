#include "FilesLogic.h"

//function for loading a game
GameRef loadGame(char* file, GameRef game)
{

	// get new Game struct reference
	if (game == NULL)
		return NULL;

	//open file
	FILE* gameFile = fopen(file, "r");
	if (gameFile == NULL)
		return NULL;

	// reading the file
	if (readingFile(gameFile, game) == 1)
		return NULL;

	if (fclose(gameFile) != 0)
		return NULL;
	return game;
}

//the function that reads the file, being called from load game
int readingFile(FILE* gameFile, GameRef game)
{

	char line[100];
	char* lineContent = NULL;
	int row, col;
	while (fgets(line, sizeof(char) * 100, gameFile) != NULL){
		lineContent = strtok(line, " \t<>?");
		if (strcmp(lineContent, "xml") == 0)
			continue;
		else if (strcmp(lineContent, "game") == 0)
			continue;
		else if (strcmp(lineContent, "next_turn") == 0){
			lineContent = strtok(NULL, " \t<>?");
			if (strcmp(lineContent, "White") == 0)
				game->nextPlayer = WHITE;
			else if (strcmp(lineContent, "Black") == 0)
				game->nextPlayer = BLACK;
		}
		else if (strcmp(lineContent, "game_mode") == 0){
			lineContent = strtok(NULL, " \t<>?");
			if (strcmp(lineContent, "1") == 0)
				game->mode = 1;
			else if (strcmp(lineContent, "2") == 0)
				game->mode = 2;
		}
		else if (strcmp(lineContent, "difficulty") == 0){
			lineContent = strtok(NULL, " \t<>?");
			if (strcmp(lineContent, "1") == 0)
				game->minimaxDepth = 1;
			else if (strcmp(lineContent, "2") == 0)
				game->minimaxDepth = 2;
			else if (strcmp(lineContent, "3") == 0)
				game->minimaxDepth = 3;
			else if (strcmp(lineContent, "4") == 0)
				game->minimaxDepth = 4;
			else if (strcmp(lineContent, "best") == 0)
				game->minimaxDepth = 5;
		}
		else if (strcmp(lineContent, "user_color") == 0){
			lineContent = strtok(NULL, " \t<>?");
			if (strcmp(lineContent, "White") == 0){
				game->userColor = WHITE;
				game->computerColor = BLACK;
			}
			else if (strcmp(lineContent, "Black") == 0){
				game->userColor = BLACK;
				game->computerColor = WHITE;
			}
		}
		else if (strcmp(lineContent, "board") == 0){
			for (row = BOARD_SIZE - 1; row >= 0; row--){
				if (fgets(line, sizeof(char) * 100, gameFile) != NULL){
					lineContent = strtok(line, "\t<>?");
					lineContent = strtok(NULL, "\t<>?");
					for (col = 0; col < BOARD_SIZE; col++){
						if (lineContent[col] == '_')
							game->board[col][row] = EMPTY;
						else
							game->board[col][row] = lineContent[col];
					}
				}
			}
		}
	}
	return 0;
}

//function for saving the game as xml file. 1 if fail 0 if succeed
int saveGame(char* fileName, GameRef game){
	char row;
	int col;
	FILE *gameFile = fopen(fileName, "w");
	if (gameFile == NULL)
		return 1;
	fprintf(gameFile, "%s", "<?xml version=\"1.0\" encoding=\"UTF-8\"?> \n");
	fprintf(gameFile, "%s", "<game>\n");
	if (strcmp(game->nextPlayer, WHITE) == 0)
		fprintf(gameFile, "%s", "\t<next_turn>White</next_turn>\n");
	else if (strcmp(game->nextPlayer, BLACK) == 0)
		fprintf(gameFile, "%s", "\t<next_turn>Black</next_turn>\n");
	if (game->mode == 1)
		fprintf(gameFile, "%s", "\t<game_mode>1</game_mode>\n");
	else if (game->mode == 2)
		fprintf(gameFile, "%s", "\t<game_mode>2</game_mode>\n");
	fprintf(gameFile, "%s", "\t<difficulty>");
	if (game->minimaxDepth == 5)
		fprintf(gameFile, "%s", "Best");
	else if (game->mode != 1){
		char dif = game->minimaxDepth + '0';
		fprintf(gameFile, "%c", dif);
	}
	fprintf(gameFile, "%s", "</difficulty>\n");
	fprintf(gameFile, "%s", "\t<user_color>");
	if (game->mode != 1){
		if (strcmp(game->userColor, WHITE) == 0)
			fprintf(gameFile, "%s", "White");
		else if (strcmp(game->userColor, BLACK) == 0)
			fprintf(gameFile, "%s", "Black");
	}
	fprintf(gameFile, "%s", "</user_color>\n");
	fprintf(gameFile, "%s", "\t<board>\n");
	for (row = '0' + BOARD_SIZE; row >= '1'; row--){
		fprintf(gameFile, "\t\t<row_%c>", row);
		for (col = 0; col < BOARD_SIZE; col++){
			if (game->board[col][row - '1'] == EMPTY)
				fprintf(gameFile, "%c", '_');
			else
				fprintf(gameFile, "%c", game->board[col][row - '1']);
		}
		fprintf(gameFile, "</row_%c>\n", row);
	}
	fprintf(gameFile, "%s", "\t</board>\n");
	fprintf(gameFile, "%s", "</game>");
	fclose(gameFile);
	return 0;
}



//IF FILE EXISTS RETURN 0 OTHERWISE RETURN 1
int fileExists(char* name)
{
	FILE *file = NULL;
	file = fopen(name, "r");
	if (file != NULL)
	{
		fclose(file);
		return 0;
	}
	return 1;
}