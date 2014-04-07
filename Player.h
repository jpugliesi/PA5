//Player.h
#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player{

	private:
		std::string piece; //player's chosen piece
		int money; //amount of money a player has
		int currentPosition; //index position of player on the board
	public:

		//constructors
		Player();
		~Player();

		//functions
		int getCurrentSpace(); //returns index of space Player is on
		int move(int size); //advances player's position index by int size
		int setPosition(int position); //sets the player's positon index to position

		void setPiece(std::string newPiece); //sets player's piece to newPiece
		std::string getPiece(); //returns player's piece

		int getMoney(); //returns amount of money player has
		void giveMoney(int amount); //adds money of amount 'amount' to player's money
		int takeMoney(int amount); //takes money of amount 'amount' from player's money
};

#endif