#include <iostream>
#include "GoToAction.h"
#include "MoneyAction.h"

	GoToAction::GoToAction() : Action("GoToAction"){
		
	}
	GoToAction::GoToAction(Player* p, Game_Board* board, 
							Space* space) : Action("GoToAction") {

		Action::setActingPlayer(p);
		theBoard = board;
		theBank = board->getBank();
		newSpace = space;

	}
	GoToAction::GoToAction(Player* p, Game_Board* board, 
							Space* space, std::string desc) : Action("GoToAction", desc) {

		Action::setActingPlayer(p);
		theBoard = board;
		theBank = board->getBank();
		newSpace = space;

	}

	void GoToAction::executeAction(){
		Player* player = Action::getActingPlayer();
		int index = player->getCurrentSpace();
		currentSpace = theBoard->findSpaceByIndex(index);
		currentSpace->removePlayerFromSpace(*player);

		player->setPosition(newSpace->getSpaceIndex());
		if(player->didPassGo()){
			MoneyAction passGo(player, 200, true, "You passed Go. Collect $200.");
			theBank->withdraw(200);
			passGo.executeAction();
		}
		newSpace->addPlayerToSpace(*player);
		
	}

	void GoToAction::executeAction(Player* p){
		Action::setActingPlayer(p);
		Player* player = Action::getActingPlayer();
		int index = player->getCurrentSpace();
		currentSpace = theBoard->findSpaceByIndex(index);
		currentSpace->removePlayerFromSpace(*player);

		player->setPosition(newSpace->getSpaceIndex());
		if(player->didPassGo()){
			MoneyAction passGo(player, 200, true, "You passed Go. Collect $200.");
			theBank->withdraw(200);
			passGo.executeAction();
		}
		newSpace->addPlayerToSpace(*player);
		
	}
