//Space.h
#ifndef SPACE_H
#define SPACE_H

#include <string>
#include "Action.h"
#include "Player.h"

class Player;
class Action;

class Space{

	private:
		std::string name; //name of the space
		int index;
		int nextSpace; //index of space that comes after
		bool ownable; //whether or not the space is able to be owned
		int value;
		int rent;
		Player* owner; //owner of the space
		Player* currentPlayers; //array of players currently on the space
		int numPlayersOnSpace; //number of players currently on the space

		Action* action;	

	public:
		//constructors
		Space(); //creates ownable space with no players on it
		Space(std::string name, int nextSpace, bool canOwn, int newValue);
		~Space();

		//functions
		bool isOwnable(); //returns whether or not a space can be owned

		void addPlayerToSpace(Player aPlayer); //adds a player to the currentPlayers array
		Player* getPlayersOnSpace(); //returns array of players currently on the space
		std::string playersOnSpaceToString(); //returns string of piece's of players currently on the space
		void removePlayerFromSpace(Player aPlayer); //removes a player from the space

		void setName(std::string newName);
		std::string getName();

		int getSpaceIndex();
		int getValue();
		int getRent();

		void setAction(Action* anAction);
		bool hasAction();
		void executeAction();

		//may not be useful, currenty unimplemented
		std::string getOwner();
		bool isOwned();
		Player* getOwnerReference();
		void setOwner(Player* newOwner);
		void setNextSpace(int newNextspace);

		
};

#endif