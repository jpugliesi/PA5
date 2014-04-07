//Die.h
#ifndef DIE_H
#define DIE_H
class Die{

	private:
		int numSides; //number of sides on the die
	public:
		//constructors
		Die();
		~Die();

		//functions
		int rollDie(); //generates and returns random value between 1 and 6
};
#endif