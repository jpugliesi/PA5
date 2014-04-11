#include "PropertyAction.h"
#include "Action.h"
#include "MoneyAction.h"
#include <iostream>

	PropertyAction::PropertyAction() : Action("PropertyAction"){

	}
	PropertyAction::PropertyAction(Player* p1, Player* p2, Space* cs, Bank* bank, bool buying, bool isbank) : Action("PropertyAction"){
		player1 = p1;
		player2 = p2;
		currentSpace = cs;
		theBank = bank;
		willBuy = buying;
		isFromBank = isbank;
	}
	void PropertyAction::executeAction(){
		if(willBuy){
			if(!isFromBank) buyProperty();
			else buyBankProperty();
		}else{
			if(!isFromBank) sellProperty();
			else sellBankProperty();
		}
	}
	void PropertyAction::buyProperty(){
		MoneyAction transaction;
		int buyValue = transaction.takeMoney(player1, currentSpace->getValue());
		transaction.payMoney(player2, buyValue);

		currentSpace->setOwner(player1);
		player1->getSpace(currentSpace);
		player2->looseSpace(currentSpace->getSpaceIndex());
	}
	void PropertyAction::sellProperty(){
		MoneyAction transaction;
		int sellValue = transaction.payMoney(player1, currentSpace->getValue());
		transaction.takeMoney(player2, sellValue);

		currentSpace->setOwner(player2);
		player2->getSpace(currentSpace);
		player1->looseSpace(currentSpace->getSpaceIndex());

	}

	void PropertyAction::buyBankProperty(){
		MoneyAction transaction;
		int buyValue = transaction.takeMoney(player1, currentSpace->getValue());
		theBank->deposit(buyValue);

		std::cout << player1->getPiece() << " bought " << currentSpace->getName() << " from the Bank for ";
		std::cout << buyValue << "." << std::endl;

		currentSpace->setOwner(player1);
		player1->getSpace(currentSpace);
	}
	void PropertyAction::sellBankProperty(){
		MoneyAction transaction;
		int moneyToGain = (int)(currentSpace->getValue())*(3./4);
		int sellValue = transaction.payMoney(player1, moneyToGain);
		theBank->withdraw(sellValue);

		std::cout << player1->getPiece() << " sold " << currentSpace->getName() << " back to the Bank for ";
		std::cout << sellValue << "." << std::endl;

		currentSpace->setOwner(NULL);
	}
	int PropertyAction::getPropertyActionValue(){
		return value;
	}
