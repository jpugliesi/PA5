#ifndef MOVEACTION_H
#define MOVEACTION_H
#include "Action.h"

class MoveAction : public Action{

	protected:
		int amount; //amount to move
	public:
		//constructors
		MoveAction(); //blank moveAction
		MoveAction(std::string name, int size); //create Moveaction of specific name and size
		MoveAction(int size); //cretae moveaction with default name, specific size

		//functions
		void setAmount(int size); //setAmount to move to size
		int getAmount(); //getAmount to move
};

#endif