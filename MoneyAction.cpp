#include <iostream>
#include <string>
#include "MoneyAction.h"

	/***** Constructors *****/

	//create MoneyAction with name "Default"
	MoneyAction::MoneyAction() : Action() { }

	//create MoneyAction with specific name newName
	MoneyAction::MoneyAction(std::string newName) : Action(newName) { }

	/***** Functions *****/

	//pay p amount sum of money
	void MoneyAction::payMoney(Player& p, int amount){
		p.giveMoney(amount);
	}
	//take amount sum of money from player p
	int MoneyAction::takeMoney(Player& p, int amount){
		p.takeMoney(amount);
		return amount;
	}