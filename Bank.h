//Bank.h
#ifndef BANK_H
#define BANK_H

class Bank{

	private:
		int money; //amount of money in the bank
	public:
		//constructors
		Bank(); //creates Bank with $100000 for money
		~Bank();

		//functions
		int withdraw(int); //given a withdrawl amount, withdraws that sum from the bank
		int deposit(int); //given a deposit amount, deposits that sum into the bank
};

#endif