#include <iostream>
#include "MoveAction.h"
#include "MoneyAction.h"


	/***** Constructors *****/

	MoveAction::MoveAction() : Action("MoveAction"){

	}

	//create Moveaction of specific name and size
	MoveAction::MoveAction(Player* p, Game_Board* board, int moveValue) : Action("MoveAction"){
		Action::setActingPlayer(p);
		theBoard = board;
		theBank = theBoard->getBank();
		amount = moveValue;
	}

	MoveAction::MoveAction(Player* p, Game_Board* board, int moveValue, std::string desc) : Action("MoveAction", desc){
		Action::setActingPlayer(p);
		theBoard = board;
		theBank = theBoard->getBank();
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
		Player* player = Action::getActingPlayer();
		int index = player->getCurrentSpace();
		Space *current = theBoard->findSpaceByIndex(index);
		current->removePlayerFromSpace(*player);

		player->move(amount);
		if(description != ""){
			std::cout << description << std::endl;
		}
		if(player->didPassGo()){
			std::cout << player->getPiece() << " passed Go! Collect $200." << std::endl;
			MoneyAction payForPassingGo(player, 200, true);
			theBank->withdraw(200);
			payForPassingGo.executeAction();
		}
		index = player->getCurrentSpace();
		Space *newSpace = theBoard->findSpaceByIndex(index);
		newSpace->addPlayerToSpace(*player);
		if(newSpace->getName() != ""){
			std::cout << player->getPiece() << " moved to " << newSpace->getName() << std::endl;
		}

	}

	void MoveAction::executeAction(Player* p){
		Action::setActingPlayer(p);
		Player* player = Action::getActingPlayer();
		int index = player->getCurrentSpace();
		Space *current = theBoard->findSpaceByIndex(index);
		current->removePlayerFromSpace(*player);

		player->move(amount);
		if(description != ""){
			std::cout << description << std::endl;
		}
		if(player->didPassGo()){
			std::cout << player->getPiece() << " passed Go! Collect $200." << std::endl;
			MoneyAction payForPassingGo(player, 200, true);
			theBank->withdraw(200);
			payForPassingGo.executeAction();
		}
		index = player->getCurrentSpace();
		Space *newSpace = theBoard->findSpaceByIndex(index);
		newSpace->addPlayerToSpace(*player);
		if(newSpace->getName() != ""){
			std::cout << player->getPiece() << " moved to " << newSpace->getName() << std::endl;
		}

	}