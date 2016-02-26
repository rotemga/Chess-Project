##########################################################################################

README file for the Chess project (2015)
Partners: Inbal Ben David & Rotem Garfel

##########################################################################################

defult values: (as asked)
game mode: playerVSplayer
next player: White


if you choose playerVScomputer the defaults in the AI menu:
depth: 1
user color: White


Game instructions:
for GUI:
*in main menu you can choose between 3 options: new game which directs you to new game menu, load game which directs you to load menu and quit.

*in new game menu you can update the values such as next player and game mode. you can also move to a menu where you can update the board.
if you choose PLAYERVSCOPUTER you are being directs to the AI options menu after pressing "continue", else you will be moving to the game.

*in the AI menu you can choose the depth for the minimax and the user color, from there you are being directed to the game.

*in setboad you need to press on a game tool and then on the place you want to locate it on the board. (don't try to drag tools, only press).
if you want to remove the tool press remove after you press the tool. you can press on full board and start over with full board.

*in load game menu you can choose a slot (you can change the number of slots from 7 to 1-10 by only changing SLOTNUM in LOADORSAVEMENU.h) and load the game or cancel and go back to main menu.
we load games in the GUI by the name "chessX.xml when X represents the slot number, the game is loaded from the folder which all the modules are located in.

*in game you can save, go back to main menu, and quit. in playerVSplayer you can see best moves 1-4 or best by pressing the right button. in the other mode you need to press on "see best move".
 you need to wait for the move until you can see it on the board and accept/cancel it. if there was check and its computer turn after, the message will stay and the move will be loaded (without loading message).
if the computer is the one starts you need to press on start in order to start the game. the tool movement is like in set.

*in save game you can choose a slot for saving (pressing on save and return will take you back even if you wont choose a slut (there will be no save...)
we save games in the GUI by the name "chessX.xml when X represents the slot number, the game is saved to the folder which all the modules are located in. it runs over previous versions of files. 





##########################################################################################


List of modules:


AIsettingMenu - presents the user with selecting the level he wants to play against, and the user color.
ChessLogic - Include the user turn and computer turn functions.
ChessRules - Include the functions that implement the rules of the game.
FilesLogic -  Implements the connection with files, reading and loading games, or writing them to new files.
GameFlow - Include basic function that needed.
GraphicFramework - responsible to export function and utilities for creating labels,panels and such using the SDL library.
LoadOrSaveMenu - presents the user with the option to load desired board and game settings, or save the current game to one of the sluts.
Main - directs os to GUI or CONSOLE mode, and basically starts everything.
MainMenu - presents the user with the main menu, where he can start anew game, load an existing game or quit.
MiniMax - responsible for finding the best move using alpha beta pruning.
NewGameMenu - presents the user with the option to select the next player color and the game mode.
setOrGame - in game presents the actual game and make the arrangement to show the next move or wait for an event to come. in set it presents the game board before the game start and enables to set the tools on the board. 


##########################################################################################
