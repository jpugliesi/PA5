#include "Bank.h"

	/***** Constructors *****/

	Bank::Bank(){

		money = 100000; //creates bank with initial amount of 100,000

	}

	//deconstructor
	Bank::~Bank(){
	}

	/***** Functions *****/

	//Given int deposit_money as a parameter, increases Bank money by deposit_money
	//Returns the new amount of money in the bank
	int Bank::deposit(int deposit_money){
		money += deposit_money;
		return money;
	}

	//Given int withdraw_money as a parameter, increases Bank money by withdraw_money
	//If withdraw request leaves money > 0, Returns the new amount of money in the bank
	//Else, returns -1 to state that too much money was requested
	int Bank::withdraw(int withdraw_money){
		if(money -= withdraw_money > 0){
			return money;
		}
		return -1;
	}