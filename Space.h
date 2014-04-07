//Space.h
#ifndef SPACE_H
#define SPACE_H

#include <string>
#include "Player.h"
#include "Action.h"

class Space{

	private:
		std::string name; //name of the space
		Action action; //space's action
		int nextSpace; //index of space that comes after
		bool ownable; //whether or not the space is able to be owned
		Player owner; //owner of the space
		Player currentPlayers[4]; //array of players currently on the space
		int numPlayersOnSpace; //number of players currently on the space	

	public:

		//constructors
		Space(); //creates ownable space with no players on it
		Space(std::string name, int nextSpace, bool canOwn);
		~Space();

		//functions
		bool isOwnable(); //returns whether or not a space can be owned

		void addPlayerToSpace(Player aPlayer); //adds a player to the currentPlayers array
		Player* getPlayersOnSpace(); //returns array of players currently on the space
		std::string playersOnSpaceToString(); //returns string of piece's of players currently on the space
		void removePlayerFromSpace(Player aPlayer); //removes a player from the space

		void setName(std::string newName);
		std::string getName();

		//may not be useful, currenty unimplemented
		std::string getOwner();
		void setOwner(Player newOwner);
		void setAction(Action anAction);
		void setNextSpace(int newNextspace);

		
};

#endif