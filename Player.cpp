//Player.cpp
#include "Player.h"
#include "Space.h"
#include <iostream>

	/***** Constructors *****/
	
	//Default Constructor
	//Player has blank piece and $5000
	Player::Player(){

		piece = "";
		money = 1000;
		passedGo = false;

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
		if(newPosition < currentPosition){
			passedGo = true;
		}
		currentPosition = newPosition;
		return currentPosition;
	}

	//similar to setPosition, except only done on game start to prevent passed Go bug
	int Player::setInitialPosition(){
		currentPosition = 0;
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
			passedGo = true;
			currentPosition = value - 40;
		}
		return currentPosition;
	}

	bool Player::didPassGo(){
		if(passedGo == true){
			passedGo = false;
			return true;
		}
		return false;
	}

	//gets amount of money player has as an int value
	int Player::getMoney(){
		return money;
	}

	//returns true if player has money, false if 0;
	bool Player::hasMoney(){
		if(money > 0) return true;
		return false;
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

	void Player::addSpace(Space* space){
		ownedSpaces.push_back(space);
	}

	Space* Player::getOwnedSpace(int i){
		return ownedSpaces[i];
	}

	Space* Player::looseSpace(int index){
		Space* result;
		for(int i = 0; i < ownedSpaces.size(); i++){
			if (ownedSpaces[i]->getSpaceIndex() == index){
				result = ownedSpaces[i];
				ownedSpaces.erase(ownedSpaces.begin() + i);
				return result;
			}
		}
		return NULL;
	}

	bool Player::ownsSpace(Space* theSpace){

		for(int i = 0; i < ownedSpaces.size(); i++){
			if(ownedSpaces[i]->getName() == theSpace->getName()){
				return true;
			}
		}
		return false;
	}

	int Player::getNumOwnedSpaces(){
		return ownedSpaces.size();
	}

	void Player::printOwnedSpaces(){
		for(int i = 0; i < ownedSpaces.size(); i++){
			std::cout << "\t" << ownedSpaces[i]->getName() << std::endl;
		}
	}



