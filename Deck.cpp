//Deck.cpp
#include "Deck.h"
#include <algorithm>

	Deck::Deck(){
	}

	void Deck::shuffle(){
		std::random_shuffle(cards.begin(), cards.end());
	}

	void Deck::getAndExecuteCard(){
		Action* tmp= cards.front();
		cards.front()->executeAction();
		cards.push_back(tmp);
		cards.erase(cards.begin());
	}

	void Deck::getAndExecuteCard(Player* p){
		Action* tmp= cards.front();
		cards.front()->executeAction();
		cards.push_back(tmp);
		cards.erase(cards.begin());
	}

	void Deck::addCard(Action* newAction){
		cards.push_back(newAction);
	}