//CardAction.h
#ifndef CARDACTION_H
#define CARDACTION_H
#include "Action.h"
#include "Deck.h"

class Deck;

class CardAction : public Action{

	private:
		Deck* deck;
	public:
		CardAction();
		CardAction(Deck* theDeck);
		void executeAction();
		void executeAction(Player*);
};

#endif