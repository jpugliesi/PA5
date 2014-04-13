#ifndef PROPERTYACTION_H
#define PROPERTYACTION_H
#include "Player.h"
#include "Space.h"
#include "Bank.h"

class PropertyAction : public Action{

	private:
		Player* player1;
		Player* player2;
		Space* currentSpace;
		bool willBuy;
		bool isFromBank;
		bool isTransfer;
		Bank* theBank;
		int value;

		void buyProperty(); //player1 buys currentSpace from player2
		void sellProperty(); //player1 sells currentSpace to player2

		void buyBankProperty(); //player1 pays bank and gains property of currentSpace
		void sellBankProperty(); //Bank pays player1 3/4 of space value and gains ownership of currentSpace

		void transferPropertiesToBank(); //transfers all of player1's properties to the Bank
		void transferPropertiesToOtherPlayer(); //transfers all of player1's properties to player2
	public:
		PropertyAction();
		PropertyAction(Player* p1, Player* p2, Space* cs, Bank* bank, bool buyingIt, bool isbank, bool transfer);
		void executeAction();
		int getPropertyActionValue();

};

#endif