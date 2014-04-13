#include "PropertyAction.h"
#include "Action.h"
#include "MoneyAction.h"
#include <iostream>

	PropertyAction::PropertyAction() : Action("PropertyAction"){

	}
	PropertyAction::PropertyAction(Player* p1, Player* p2, Space* cs, Bank* bank, bool buying, bool isbank, bool transfer) : Action("PropertyAction"){
		Action::setActingPlayer(p1);
		Action::setRecievingPlayer(p2);
		currentSpace = cs;
		theBank = bank;
		willBuy = buying;
		isFromBank = isbank;
		isTransfer = transfer;
	}

	PropertyAction::PropertyAction(Player* p1, Player* p2, Space* cs, Bank* bank, bool buying, bool isbank, bool transfer, std::string desc) : Action("PropertyAction", desc){
		Action::setActingPlayer(p1);
		Action::setRecievingPlayer(p2);
		currentSpace = cs;
		theBank = bank;
		willBuy = buying;
		isFromBank = isbank;
		isTransfer = transfer;
	}

	void PropertyAction::executeAction(){
		if(isTransfer){
			if(isFromBank){
				transferPropertiesToBank();
			}else{
				transferPropertiesToOtherPlayer();
			}
		}
		else if(willBuy){
			if(!isFromBank) buyProperty();
			else buyBankProperty();
		}else{
			if(!isFromBank) sellProperty();
			else sellBankProperty();
		}
	}
	void PropertyAction::executeAction(Player* p){
		Action::setActingPlayer(p);
		if(isTransfer){
			if(isFromBank){
				transferPropertiesToBank();
			}else{
				transferPropertiesToOtherPlayer();
			}
		}
		else if(willBuy){
			if(!isFromBank) buyProperty();
			else buyBankProperty();
		}else{
			if(!isFromBank) sellProperty();
			else sellBankProperty();
		}
	}
	void PropertyAction::buyProperty(){
		Player* player1 = getActingPlayer();
		Player* player2 = getRecievingPlayer();
		MoneyAction transaction(player1, currentSpace->getValue(), false);
		transaction.executeAction();
		int buyValue = transaction.getAmount();
		transaction.payMoney(player2, buyValue);
		transaction.executeAction();

		currentSpace->setOwner(player1);
		player1->addSpace(currentSpace);
		player2->looseSpace(currentSpace->getSpaceIndex());
	}
	void PropertyAction::sellProperty(){
		Player* player1 = getActingPlayer();
		Player* player2 = getRecievingPlayer();
		MoneyAction transaction(player1, currentSpace->getValue(), true);
		transaction.executeAction();
		int sellValue = transaction.getAmount();
		transaction.takeMoney(player2, sellValue);
		transaction.executeAction();

		currentSpace->setOwner(player2);
		player2->addSpace(currentSpace);
		player1->looseSpace(currentSpace->getSpaceIndex());

	}

	void PropertyAction::buyBankProperty(){
		Player* player1 = getActingPlayer();
		MoneyAction transaction(player1, currentSpace->getValue(), false);
		transaction.executeAction();
		int buyValue = transaction.getAmount();
		theBank->deposit(buyValue);

		std::cout << player1->getPiece() << " bought " << currentSpace->getName() << " from the Bank for ";
		std::cout << buyValue << "." << std::endl;

		player1->addSpace(currentSpace);
		currentSpace->setOwner(player1);
	}
	void PropertyAction::sellBankProperty(){
		Player* player1 = getActingPlayer();
		int moneyToGain = (int)(currentSpace->getValue())*(3./4);
		MoneyAction transaction(player1, moneyToGain, true);
		int sellValue = transaction.getAmount();
		transaction.executeAction();
		theBank->withdraw(sellValue);

		std::cout << player1->getPiece() << " sold " << currentSpace->getName() << " back to the Bank for ";
		std::cout << sellValue << "." << std::endl;

		player1->looseSpace(currentSpace->getSpaceIndex());
		currentSpace->setOwner(NULL);
	}
	int PropertyAction::getPropertyActionValue(){
		return value;
	}

	void PropertyAction::transferPropertiesToBank(){
		//transfer from player1 to Bank
		Player* player1 = getActingPlayer();

		for(int i = 0; i < player1->getNumOwnedSpaces(); i++){
			Space* theSpace = player1->getOwnedSpace(i);
			player1->looseSpace(theSpace->getSpaceIndex());
			theSpace->setOwner(NULL);
		}

	}

	void PropertyAction::transferPropertiesToOtherPlayer(){
		//transfer from player1 to player2

		Player* player1 = getActingPlayer();
		Player* player2 = getRecievingPlayer();

		for(int i = 0; i < player1->getNumOwnedSpaces(); i++){
			Space* theSpace = player1->getOwnedSpace(i);
			player1->looseSpace(theSpace->getSpaceIndex());
			theSpace->setOwner(player2);
			player2->addSpace(theSpace);
		}
	}
