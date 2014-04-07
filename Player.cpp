//Player.cpp
#include "Player.h"

	/***** Constructors *****/
	
	//Default Constructor
	//Player has blank piece and $5000
	Player::Player(){

		piece = "";
		money = 5000;

	}
	Player::~Player(){
		
	}

	/***** Functions *****/

	//Sets player's piece to a new string
	void Player::setPiece(std::string newPiece){
		piece = newPiece;
	}

	//returns the player's piece as a string
	std::string Player::getPiece(){
		return piece;
	}

	//sets player's current position index
	int Player::setPosition(int newPosition){
		currentPosition = newPosition;
		return currentPosition;
	}

	//gets currentPosition index
	int Player::getCurrentSpace(){
		return currentPosition;
	}

	//advances move by num, modulo 40
	int Player::move(int num){
		currentPosition += num;
		if(currentPosition > 39){
			int value = currentPosition;
			currentPosition = value - 40;
		}
		return currentPosition;
	}

	//gets amount of money player has as an int value
	int Player::getMoney(){
		return money;
	}

	//adds money of amount 'amount' to player's money
	void Player::giveMoney(int amount){
		money += amount;
	}
	//takes money of amount 'amount' from player's money
	int Player::takeMoney(int amount){
		money -= amount;
		return amount;
	}



