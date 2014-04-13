//Game_Board.h
#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <string>
#include "Space.h"
#include "Deck.h"
#include "Bank.h"

class Game_Board{
	public:
		//variables
		const static int NUM_SPACES = 40;
		
		//constructors
		Game_Board(int, Bank*, Deck*, Deck*);
		~Game_Board();

		//functions
		void printBoard();
		Space* findSpaceByIndex(int index);
		Bank* getBank(); //returns a pointer to the Bank

	private:
		//variables
		const static int SPACE_WIDTH = 12; //number of characters in the width of a space
		const static int SPACES_IN_ROW = 11; //number of spaces in a row
		int num_players; //number of players currently in the game
		Bank* theBank;
		Deck* theManDeck; //Deck of THE MAN cards
		Deck* theChestDeck; //Deck of Chest cards

		/*** functions ***/

		Space spaces[NUM_SPACES]; //array of spaces on the board
		void occupySpaces();	  //fills spaces array with predefined spaces
		std::string centerString(std::string toCenter); //creates string suitably centered for a space

		//printing shenanigans

		//prints a board row from spaces array index start to end
		//prints form end to start if reverse is true
		void printBoardRowReverse(int start, int end, bool reverse);
		//prints two spaces that comprise the middle rows of the board
		//those spaces are s1 and s2
		void printMiddleRow(int s1, int s2);

		//helper methods for printing
		void printTopLine(int numSpaces); //prints line of '-' characters for top and bottom of rows
		void printRowWithName(int numSpaces, int firstSpace, bool isReverse); //prints a row with respective each space's name
		void printRowWithCharacter(int numSpaces, char x); //prints row filled with character x
		void printRowWithOwner(int numSpaces, int firstSpace, bool isReverse); //prints row of spaces with string of respective owner of each space 
		void printRowWithCurrentPlayers(int numSpaces, int firstSpace, bool isReverse); //prints row with spaces filled with corresponding players on those spaces
		void printBottom(); //prints bottoms for middle rows
		
};
#endif