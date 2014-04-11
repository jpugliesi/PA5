#include <iostream>
#include "GoToAction.h"

	GoToAction::GoToAction() : Action("GoToAction"){
		
	}
	GoToAction::GoToAction(Player& p, Game_Board& board, 
							Space& space) : Action("GoToAction") {

		player = &p;
		theBoard = &board;
		newSpace = &space;

	}

	void GoToAction::executeAction(){

		int index = player->getCurrentSpace();
		currentSpace = theBoard->findSpaceByIndex(index);
		currentSpace->removePlayerFromSpace(*player);

		player->setPosition(newSpace->getSpaceIndex());
		newSpace->addPlayerToSpace(*player);
		
	}
