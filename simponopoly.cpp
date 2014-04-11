#include <iostream>
#include "Game_Board.h"
#include "Space.h"
#include "Player.h"
#include "Action.h"
#include "Card.h"
#include "Bank.h"
#include "Die.h"
#include "MoneyAction.h"
#include "MoveAction.h"
#include "GoToAction.h"
#include "PropertyAction.h"

void occupyPieces();
int welcome();
int getOption();
int getTurnOption();
int getNumPlayers();

void getPlayerInfo();

int yesOrNo();

void printInstructions(); //to implement
void printAvailablePieces(int *chosenPieces);
bool pieceIsTaken(int *chosenPieces, int choice);

int playTurn(Game_Board* theBoard, Player* thePlayer, Die d1, Die d2, int turn);
int gameOver();

const int NUM_PIECES = 10;

std::string pieces[NUM_PIECES];
int numPlayers;
Player *players;
int turn = 0;

Bank theBank;

int main(){

	occupyPieces();

	if(welcome()){

		numPlayers = getNumPlayers();
		players = new Player[numPlayers];

		getPlayerInfo();

		Game_Board theBoard(numPlayers);
		Space* go = theBoard.findSpaceByIndex(0);
		for(int i = 0; i < numPlayers; i++){
			players[i].setPosition(0);
			go->addPlayerToSpace(players[i]);
		}
		theBoard.printBoard();

		Die die1;
		Die die2;
		while(!gameOver()){

			Player *playerWithTurn = &(players[turn]);
			turn = playTurn(&theBoard, playerWithTurn, die1, die2, turn);

			if(turn == numPlayers-1){
				turn = 0;
			}else{
				turn++;
			}
			
			if(!getTurnOption()){
				std::cout << "Thanks for Playing" << std::endl;
				return -1;
			}
			

		}

	}

	delete [] players;
	return 1;
}

int playTurn(Game_Board* theBoard, Player* thePlayer, Die d1, Die d2, int turn){

	int v1 = d1.rollDie();
	int v2 = d2.rollDie();
	int moveValue = v1 + v2;

	std::cout << "The " << thePlayer->getPiece() << " is up!" << std::endl;
	std::cout << "Die rolled: " << v1 << " and " << v2 << "." << std::endl;
	std::cout << "The " << thePlayer->getPiece() << " advances " << moveValue << " spaces!" << std::endl;

	MoveAction move(thePlayer, theBoard, moveValue);
	move.executeAction();
	if(thePlayer->didPassGo()){
		std::cout << thePlayer->getPiece() << " passed Go! Collects $200" << std::endl;
		MoneyAction payForPassingGo;
		theBank.withdraw(200);
		payForPassingGo.payMoney(thePlayer, 200);
	}


	int choice = 1;
	Space* currentSpace = theBoard->findSpaceByIndex(thePlayer->getCurrentSpace());
	if(currentSpace->isOwnable()){
		theBoard->printBoard();

		if(thePlayer->ownsSpace(currentSpace)){
			std::cout << "\t (" << choice << ") Sell this property for $" << (int)(currentSpace->getValue())*(3./4) << "? (y/n)" << std::endl;
			if(yesOrNo()){
				PropertyAction sellBankProperty(thePlayer, NULL, currentSpace, &theBank, false, true);
				sellBankProperty.executeAction();
				std::cout << players[turn].getPiece() << " now has $" << players[turn].getMoney() << std::endl;
			}
			choice++;
		}else if(!currentSpace->isOwned()){
			std::cout << "\t(" << choice << ") Buy this property for $" << currentSpace->getValue() << "? (y/n)" << std::endl;
			if(yesOrNo()){
				PropertyAction buyProperty(thePlayer, NULL, currentSpace, &theBank, true, true);
				buyProperty.executeAction();
				std::cout << players[turn].getPiece() << " now has $" << players[turn].getMoney() << std::endl;
			}
			choice++;
		}else{
			std::string theOwner = currentSpace->getOwner();
			std::cout << "Darn! You have to pay " << theOwner << currentSpace->getRent() << "..." << std::endl;
			MoneyAction transaction;
			int amount = transaction.payMoney(currentSpace->getOwnerReference(), currentSpace->getRent());
			transaction.takeMoney(thePlayer, amount);
			std::cout << players[turn].getPiece() << " now has $" << players[turn].getMoney() << std::endl;
			std::cout << theOwner << " now has $" << currentSpace->getOwnerReference()->getMoney() << std::endl;
		}
	}else if(currentSpace->hasAction()){
		
	}

	//a test to see if players advance to go (0th index space) if landed on any right side space
	for(int i = 11; i < 20; i++){
		if(thePlayer->getCurrentSpace() == i){
			std::cout << "The" << thePlayer->getPiece() << " advanced to GO!" << std::endl;
			GoToAction goToGo(*thePlayer, *theBoard, *(theBoard->findSpaceByIndex(0)));
			goToGo.executeAction();
		}
	}
	theBoard->printBoard();


	return turn;
	
}

int gameOver(){
	int over = 0;
	if(turn == -1){
		over = 1;
	}

	return over; //temporary
}

void getPlayerInfo(){
	int chosenPieces[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	for(int i = 0; i < numPlayers; i++){
		printAvailablePieces(chosenPieces);
		std::cout << std::endl;
		std::cout << "Player " << i+1 << ", choose your piece: ";
		int x;

		do{

		std::cin >> x;

		if (std::cin.fail() || (x < 1 || x > NUM_PIECES)){

			std::cin.clear();
			std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
			std::cout << "Invalid Choice. Choose from the available pieces: ";
			continue; //jump to while statement
		}else if(pieceIsTaken(chosenPieces, x)){
			std::cin.clear();
			std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
			std::cout << "That piece is already taken. Choose a different option: ";
			continue; //jump to while statement
		}

		//a good piece is chosen
		players[i].setPiece(pieces[x-1]);
		std::cout << "\nExcellent Choice, Player " << i+1 << " is now the: " << players[i].getPiece() << std::endl << std::endl;
		chosenPieces[x-1] = 0;
		std::cin.ignore(100000, '\n'); //clear the stream
		break; //exit the loop

		} while(true);
	}
}

bool pieceIsTaken(int *chosenPieces, int choice){
	choice -= 1;
	if(chosenPieces[choice] == 1){
		return false;
	} else if(chosenPieces[choice] == 0){
		return true;
	}
	return true;
}

void printAvailablePieces(int *availablePieces){

	for(int i = 0; i < NUM_PIECES; i++){
		if(availablePieces[i] == 1){
			std::cout << "(" << i+1 << ") " << pieces[i] << std::endl;
		} else{
			std::cout << "X Taken X " << pieces[i] << std::endl;

		}
	}

}

void occupyPieces(){
	pieces[0] = "!";
	pieces[1] = "@";
	pieces[2] = "#";
	pieces[3] = "$";
	pieces[4] = "%";
	pieces[5] = "^";
	pieces[6] = "&";
	pieces[7] = "*";
	pieces[8] = "+";
	pieces[9] = "?";
}

int welcome(){
	std::cout << "***** Welcome to Simponopoly! *****" << std::endl;
	std::cout << "___________________________________" << std::endl;
	std::cout << "Choose an option to get started:" << std::endl;
	std::cout << "\t(1) Print Instructions and Play" << std::endl;
	std::cout << "\t(2) Start the GAME!!!" << std::endl;
	std::cout << "\t(3) Quit" << std::endl;

	int choice = getOption();
	switch(choice){

		case 1: printInstructions();
				return 1;
		case 2: return 1;
		case 3: return 0;

	}
	return 0;
}

void printInstructions(){

}

int getTurnOption(){

	std::cout << players[turn].getPiece() << " is up next..." << std::endl;
	std::cout << players[turn].getPiece() << "'s Money: $" << players[turn].getMoney() << std::endl;


	std::cout << "Continue playing? ";
	return yesOrNo();

}

int yesOrNo(){
	char x;
	do{

	std::cin >> x;

	if (std::cin.fail() || (x != 'y' && x != 'n')){

		std::cin.clear();
		std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
		std::cout << "Please Enter a Valid Option (y for yes, n for no): ";
		continue; //jump to while statement

	}

	//a good integer entered
	
	std::cin.ignore(100000, '\n'); //clear the stream
	break; //exit the loop

	} while(true);

	int goOn;
	if(x == 'y'){
		goOn = 1;
	}else{
		goOn = 0;
	}
	return goOn;
}

int getOption(){

	int x;

	do{

	std::cin >> x;

	if (std::cin.fail() || (x < 1 || x > 3)){

		std::cin.clear();
		std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
		std::cout << "Please Enter a Valid Option: ";
		continue; //jump to while statement

	}

	//a good integer entered

	std::cin.ignore(100000, '\n'); //clear the stream
	break; //exit the loop

	} while(true);

	return x;

}

int getNumPlayers(){

	std::cout << "Enter the number of players: ";
	int x;

	do{

	std::cin >> x;

	if (std::cin.fail() || (x < 2 || x > 4)){

		std::cin.clear();
		std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
		std::cout << "Invalid Choice. Must be between 2 and 4 players, inclusive: ";
		continue; //jump to while statement

	}

	//a good integer entered

	std::cin.ignore(100000, '\n'); //clear the stream
	break; //exit the loop

	} while(true);

	return x;

}