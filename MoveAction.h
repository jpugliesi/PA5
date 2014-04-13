#ifndef MOVEACTION_H
#define MOVEACTION_H
#include "Action.h"
#include "Player.h"
#include "Game_Board.h"
#include <string>

class MoveAction : public Action{

	protected:
		int amount; //amount to move
		Game_Board* theBoard;
		Bank* theBank;
	public:
		//constructors
		MoveAction(); //blank moveAction
		MoveAction(Player* p, Game_Board* theBoard, int moveValue); //create Moveaction of specific name and size
		MoveAction(Player* p, Game_Board* theBoard, int moveValue, std::string desc); //create Moveaction of specific name and size

		void executeAction();
		void executeAction(Player* p);

		//functions
		void setAmount(int size); //setAmount to move to size
		int getAmount(); //getAmount to move
};

#endif