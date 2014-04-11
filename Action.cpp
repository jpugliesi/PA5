#include <iostream>
#include <string>
#include "Action.h"

	/***** Constructors *****/

	//Default Constructor creates action with name "Default"
	Action::Action(){
		name = "Default"; 
	}
	//Constructor that accepts a string to set as the action's name
	Action::Action(std::string newName){
		name = newName;
	}

	/***** Functions *****/

	//Prints out the name of the Action
	void Action::print_name(){
		std::cout << name << std::endl;
	}

	std::string Action::getName(){
		return name;
	}

	void Action::setValue(int newValue){
		value = newValue;
	}

	bool Action::hasValue(){
		if(value != 0) return true;
		return false;
	}

	int Action::getValue(){
		return value;
	}

	void Action::setActingPlayer(Player* p){
		actingPlayer = p;
	}
	
	void Action::setRecievingPlayer(Player* p){
		recievingPlayer = p;
	}