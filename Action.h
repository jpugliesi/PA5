#ifndef ACTION_H
#define ACTION_H
#include <string>
#include "Player.h"

class Player;

class Action{

	protected:
		std::string name; //name of the action
		int value;
		Player* actingPlayer;
		Player* recievingPlayer;
	public:

		//constructors
		Action();
		Action(std::string newName);

		//functions
		void print_name(); //prints the name of the action
		std::string getName();
		virtual void executeAction() = 0;
		void executeAction(Player*);

		void setValue(int);
		bool hasValue();
		int getValue();

		void setActingPlayer(Player*);
		void setRecievingPlayer(Player*);

};

#endif