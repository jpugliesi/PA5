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