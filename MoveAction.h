#ifndef MOVEACTION_H
#define MOVEACTION_H
#include "Action.h"
#include "Player.h"
#include "Game_Board.h"

class MoveAction : public Action{

	protected:
		int amount; //amount to move
		Game_Board* theBoard;
		Player* player;
	public:
		//constructors
		MoveAction(); //blank moveAction
		MoveAction(Player* p, Game_Board* theBoard, int moveValue); //create Moveaction of specific name and size
		void executeAction();

		//functions
		void setAmount(int size); //setAmount to move to size
		int getAmount(); //getAmount to move
};

#endif