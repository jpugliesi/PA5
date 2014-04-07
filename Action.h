#ifndef ACTION_H
#define ACTION_H

class Action{

	protected:
		std::string name; //name of the action
	public:

		//constructors
		Action();
		Action(std::string newName);

		//functions
		void print_name(); //prints the name of the action


};

#endif