#include <iostream>
#include <string>
#include "MoneyAction.h"

	/***** Constructors *****/

	//create MoneyAction with name "Default"
	MoneyAction::MoneyAction() : Action("MoneyAction") { }

	MoneyAction::MoneyAction(Player* p, int amt, bool paying) : Action("MoneyAction") { 

		Action::setActingPlayer(p);
		amount = amt;
		pay = paying;
		description = "";

	}

	MoneyAction::MoneyAction(Player* p, int amt, bool paying, std::string desc) : Action("MoneyAction", desc) { 

		Action::setActingPlayer(p);
		amount = amt;
		pay = paying;

	}

	/***** Functions *****/

	//pay p amount sum of money
	int MoneyAction::payMoney(Player* p, int amt){
		Action::setActingPlayer(p);
		amount = amt;
		pay = true;
		return amount;
	}
	//take amount sum of money from player p
	int MoneyAction::takeMoney(Player* p, int amt){
		Action::setActingPlayer(p);
		amount = amt;
		pay = false;
		return amount;
	}

	int MoneyAction::getAmount(){
		return amount;
	}

	void MoneyAction::executeAction(){
		Player* player = Action::getActingPlayer();
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

	void MoneyAction::executeAction(Player* p){
		Action::setActingPlayer(p);
		Player* player = Action::getActingPlayer();
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