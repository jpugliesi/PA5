#include <iostream>
#include "MoveAction.h"

	/***** Constructors *****/

	MoveAction::MoveAction(){

	}

	//create Moveaction of specific name and size
	MoveAction::MoveAction(std::string newName, int size) : Action(newName){
		amount = size;
	}

	//cretae moveaction with default name, specific size
	MoveAction::MoveAction(int size) : Action(){
		amount = size;
	}

	//setAmount to move to size
	void MoveAction::setAmount(int size){
		amount = size;
	}

	//getAmount to move
	int MoveAction::getAmount(){
		return amount;
	}