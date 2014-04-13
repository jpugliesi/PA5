//Card.h
#ifndef CARD_H
#define CARD_H
#include <string>
#include "Action.h"

class Card{

	private:
		std::string description;
		Action* action;
	public:
		Card();
		Card(std::string desc, Action a);
		~Card();

};

#endif