//Dice.cpp
#include "Die.h"
#include <stdlib.h>
#include <time.h>

	/***** Constructors *****/

	//Default Constructor
	//Creates six sided die
	Die::Die(){
		srand(time(NULL));
		numSides = 6;
	}
	Die::~Die(){

	}

	/***** Functions *****/

	//generates and returns random value between 1 and 6
	int Die::rollDie(){
		int value = (rand() % numSides) + 1;
		return value;
	}
