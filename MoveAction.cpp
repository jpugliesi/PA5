#include <iostream>
#include "MoveAction.h"


	/***** Constructors *****/

	MoveAction::MoveAction() : Action("MoveAction"){

	}

	//create Moveaction of specific name and size
	MoveAction::MoveAction(Player* p, Game_Board* board, int moveValue) : Action("MoveAction"){
		player = p;
		theBoard = board;
		amount = moveValue;
	}

	//setAmount to move to size
	void MoveAction::setAmount(int size){
		amount = size;
	}

	//getAmount to move
	int MoveAction::getAmount(){
		return amount;
	}
	void MoveAction::executeAction(){
		int index = player->getCurrentSpace();
		Space *current = theBoard->findSpaceByIndex(index);
		current->removePlayerFromSpace(*player);

		player->move(amount);
		index = player->getCurrentSpace();
		Space *newSpace = theBoard->findSpaceByIndex(index);
		newSpace->addPlayerToSpace(*player);
	}