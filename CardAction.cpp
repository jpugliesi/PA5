//CardAction.cpp
#include "CardAction.h"

	CardAction::CardAction() : Action("CardAction"){}
	CardAction::CardAction(Deck* theDeck) : Action("CardAction"){
		deck = theDeck;
	}

	void CardAction::executeAction(){
		deck->getAndExecuteCard();
	}

	void CardAction::executeAction(Player* p){
		deck->getAndExecuteCard(p);
	}