#include <iostream>
#include <string>
#include "MoneyAction.h"

	/***** Constructors *****/

	//create MoneyAction with name "Default"
	MoneyAction::MoneyAction() : Action("MoneyAction") { }

	MoneyAction::MoneyAction(Player* p, int amt, bool paying) : Action("MoneyAction") { 

		player = p;
		amount = amt;
		pay = paying;
		description = "";

	}

	MoneyAction::MoneyAction(Player* p, int amt, bool paying, std::string desc) : Action("MoneyAction") { 

		player = p;
		amount = amt;
		pay = paying;
		description = desc;

	}

	/***** Functions *****/

	//pay p amount sum of money
	int MoneyAction::payMoney(Player* p, int amt){
		player = p;
		amount = amt;
		pay = true;
		return amount;
	}
	//take amount sum of money from player p
	int MoneyAction::takeMoney(Player* p, int amt){
		player = p;
		amount = amt;
		pay = false;
		return amount;
	}

	int MoneyAction::getAmount(){
		return amount;
	}

	void MoneyAction::setPlayer(Player* p){
		player = p;
	}

	void MoneyAction::executeAction(){
		if(pay){
			if(description != ""){
				std::cout << description << std::endl;
			}
			player->giveMoney(amount);
		}else{
			if(description != ""){
				std::cout << description << std::endl;
			}
			player->takeMoney(amount);
		}
	}

	std::string MoneyAction::getDescription(){
		return description;
	}