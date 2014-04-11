#include <iostream>
#include <string>
#include "MoneyAction.h"

	/***** Constructors *****/

	//create MoneyAction with name "Default"
	MoneyAction::MoneyAction() : Action("MoneyAction") { }

	/***** Functions *****/

	//pay p amount sum of money
	int MoneyAction::payMoney(Player* p, int amount){
		p->giveMoney(amount);
		return amount;
	}
	//take amount sum of money from player p
	int MoneyAction::takeMoney(Player* p, int amount){
		p->takeMoney(amount);
		return amount;
	}

	void MoneyAction::executeAction(){
		
	}