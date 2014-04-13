//Deck.h
#ifndef DECK_H
#define DECK_H
#include "Action.h"
#include <vector>

class Deck{

	private:
		std::vector<Action*> cards;

	public:
		Deck();
		void shuffle();
		void getAndExecuteCard();
		void getAndExecuteCard(Player* p);
		void addCard(Action* newAction);


};

#endif