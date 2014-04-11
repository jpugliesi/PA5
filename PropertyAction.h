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
		Bank* theBank;
		int value;

		void buyProperty();
		void sellProperty();

		void buyBankProperty();
		void sellBankProperty();
	public:
		PropertyAction();
		PropertyAction(Player* p1, Player* p2, Space* cs, Bank* bank, bool buyingIt, bool isbank);
		void executeAction();
		int getPropertyActionValue();

};

#endif