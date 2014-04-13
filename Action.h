#ifndef ACTION_H
#define ACTION_H
#include <string>
#include "Player.h"

class Player;

class Action{

	protected:
		std::string name; //name of the action
		std::string description;
		int value;
		Player* actingPlayer;
		Player* recievingPlayer;
	public:

		//constructors
		Action();
		Action(std::string newName);
		Action(std::string newName, std::string desc);

		//functions
		void print_name(); //prints the name of the action
		std::string getName();
		virtual void executeAction() = 0;
		virtual void executeAction(Player*) = 0;

		void setValue(int);
		bool hasValue();
		int getValue();

		void setActingPlayer(Player*);
		void setRecievingPlayer(Player*);
		Player* getActingPlayer();
		Player* getRecievingPlayer();

		void setDescription(std::string);
		std::string getDescription();

};

#endif