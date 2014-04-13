//Player.h
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Space.h"

class Space;

class Player{

	private:
		std::string piece; //player's chosen piece
		int money; //amount of money a player has
		int currentPosition; //index position of player on the board
		std::vector<Space*> ownedSpaces;
		bool passedGo;
	public:

		//constructors
		Player();
		~Player();

		//functions
		int getCurrentSpace(); //returns index of space Player is on
		int move(int size); //advances player's position index by int size
		int setPosition(int position); //sets the player's space index to position
		bool didPassGo(); //returns true if player's index has just exceeded 39, then sets passedGo to false

		void setPiece(std::string newPiece); //sets player's piece to newPiece
		std::string getPiece(); //returns player's piece

		int getMoney(); //returns amount of money player has
		bool hasMoney(); //returns true if player has money, false otherwise
		void giveMoney(int amount); //adds money of amount 'amount' to player's money
		int takeMoney(int amount); //takes money of amount 'amount' from player's money

		void addSpace(Space* space); //adds a space to player's owned spaces
		Space* getOwnedSpace(int index); //get a pointer to a player's owned space at index index
		Space* looseSpace(int index); //removes space from player's owned spaces
		bool ownsSpace(Space* theSpace); //returns true if player owns theSpace, false otherwise
		int getNumOwnedSpaces(); //returns int of number of spaces owned
		void printOwnedSpaces(); //prints out names of owned properties(spaces)
};

#endif