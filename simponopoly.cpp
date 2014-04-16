#include <iostream>
#include <vector>
#include "Game_Board.h"
#include "Space.h"
#include "Player.h"
#include "Action.h"
#include "Deck.h"
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
int getNumOptions(int s, int e);
int getNumPlayers();
void populateDecks(Game_Board*);

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
std::vector<Player> players;
int turn = 0;

Bank theBank;
Deck theMan;
Deck chest;

int main(){

	occupyPieces();

	if(welcome()){

		numPlayers = getNumPlayers();

		getPlayerInfo();

		Game_Board theBoard(numPlayers, &theBank, &theMan, &chest);

		populateDecks(&theBoard);

		Space* go = theBoard.findSpaceByIndex(0);
		for(int i = 0; i < numPlayers; i++){
			players[i].setInitialPosition();
			go->addPlayerToSpace(players[i]);
		}
		theBoard.printBoard();

		Die die1;
		Die die2;
		while(!gameOver()){
			Player* playerWithTurn = &(players[turn]);
			if(playerWithTurn->getInGame()){
				int result = playTurn(&theBoard, playerWithTurn, die1, die2, turn);

				//If a player has lost, remove them from the space and update numPlayers
				if(result == -1){
					playerWithTurn->toggleInGame();
					// std::cout << "Turn: " << turn << std::endl;
					Space* currentSpace = theBoard.findSpaceByIndex(playerWithTurn->getCurrentSpace());
					currentSpace->removePlayerFromSpace(*playerWithTurn);
					std::cout << players[turn].getPiece() << " has lost." << std::endl;
					theBoard.updateNumPlayers(numPlayers);
				}

				if(turn == numPlayers-1){
					turn = 0;
				}else{
					turn++;
				}
				
				//if the game is not over
				if(!gameOver()){
					playerWithTurn = &(players[turn]);
					while(!playerWithTurn->getInGame()){
						if(turn == numPlayers-1){
							turn = 0;
						}else{
							turn++;
						}
						playerWithTurn = &(players[turn]);
					}
					if(playerWithTurn->getInGame()){
						while(!getTurnOption()){
							//if the next player chooses to quit the game

							playerWithTurn->toggleInGame();
							PropertyAction transferAllProperty(playerWithTurn, NULL, NULL, &theBank, false, true, true);
							transferAllProperty.executeAction();
							Space* currentSpace = theBoard.findSpaceByIndex(playerWithTurn->getCurrentSpace());
							currentSpace->removePlayerFromSpace(*playerWithTurn);									//remove the player from the space
							std::cout << players[turn].getPiece() << " has quit the game!" << std::endl<<std::endl;
							std::cout << "Bank takes ownership of:" << std::endl;
							playerWithTurn->printOwnedSpaces();
							if(turn == numPlayers-1){																	//if turn == numPlayers, it will be out of bounds, so
								turn = 0;																			//set turn = 0
							}else{
								turn++;
							}
							playerWithTurn = &(players[turn]);
							if(gameOver()) break;
						}
					}
				}
			}else{
				if(turn == numPlayers-1){
					turn = 0;
				}else{
					turn++;
				}
			}
		}
		int i;
		for(i = 0; i < players.size(); i++){
			if(players[i].getInGame()){
				break;
			}
		}
		std::cout << std::endl << std::endl;
		std::cout << "\t__________________" << std::endl << std::endl <<std::endl;
		std::cout << "\t" << players[i].getPiece() << " is the Winner!" << std::endl << std::endl;
		std::cout << "\t__________________" << std::endl;
		std::cout << "\tThanks for Playing" << std::endl;

	}
	return 1;
}

int playTurn(Game_Board* theBoard, Player* thePlayer, Die d1, Die d2, int theTurn){

	//roll the die
	int v1 = d1.rollDie();
	int v2 = d2.rollDie();
	int moveValue = v1 + v2;

	std::cout << "The " << thePlayer->getPiece() << " is up!" << std::endl;
	std::cout << "Die rolled: " << v1 << " and " << v2 << "." << std::endl;
	std::cout << "The " << thePlayer->getPiece() << " advances " << moveValue << " spaces!" << std::endl;

	//move the player
	MoveAction move(thePlayer, theBoard, moveValue);
	move.executeAction();

	int choice = 1;
	bool owesOtherPlayer = false;
	Player* otherPlayer; //other player who might be interacted with (eg. has to pay rent to)

	Space* currentSpace = theBoard->findSpaceByIndex(thePlayer->getCurrentSpace());

	//if current space has an action, execute it
	if(currentSpace->hasAction()){
		Action* theAction = currentSpace->getAction();

		theAction->executeAction(thePlayer);

	}
	theBoard->printBoard();

	currentSpace = theBoard->findSpaceByIndex(thePlayer->getCurrentSpace());
	//if current space is ownable
	if(currentSpace->isOwnable()){
		//if the player owns that space, offer chance to:
		// * sell it to the bank
		// * sell it to another player
		// * do neither and continue
		if(thePlayer->ownsSpace(currentSpace)){
			std::cout << "\t (" << choice++ << ") Sell " << currentSpace->getName() << " to Bank for $" << (int)(currentSpace->getValue())*(3./4) << "?" << std::endl;
			std::cout << "\t (" << choice++ << ") Sell " << currentSpace->getName() << " to Another Player for $" << currentSpace->getValue() << "?" << std::endl;
			std::cout << "\t (" << choice++ << ") Neither. Continue." << std::endl;

			int result = getNumOptions(1, choice-1); //get choice 1-3 corresponding to above options
			//if player chooses to sell, sell it to the bank
			if(result == 1){
				PropertyAction sellBankProperty(thePlayer, NULL, currentSpace, &theBank, false, true, false);
				sellBankProperty.executeAction();
				std::cout << players[theTurn].getPiece() << " now has $" << players[theTurn].getMoney() << std::endl;
			}
			//else if selling to someone else, start process for selling to another player
			else if(result == 2){
				int c = 1;
				bool cancel = false;
				int playersArray[players.size()];
				Player* chosenPlayer = NULL;
				std::cout << "Which player?" << std::endl;
				//print players to choose from
				for(int i = 0; i < numPlayers; i++){
					if(players[i].getPiece() != thePlayer->getPiece() && players[i].getInGame()){
						std::cout << "\t(" << c << ") " << players[i].getPiece() << std::endl;
						playersArray[i] = c++;
					}else{
						playersArray[i] = 0;
					}
					
				}
				//choose which player to sell to
				std::cout << "\t(" << c << ") Cancel" << std::endl; //present a cancel option
				int result2 = getNumOptions(1, players.size()); //players.size() because we have extra cancel option
				for(int i = 0; i < players.size(); i++){
					if(playersArray[i] == result2){
						chosenPlayer = &players[i];
						break;
					}else if(result2 == c){ //user chose to cancel the transaction
						cancel = true;
						break;
					}
				}
				//if user didn't cancel, ask other player if they're willing to buy
				if(!cancel){
					std::cout << chosenPlayer->getPiece() << ", do you agree to buy " << currentSpace->getName() << " for " << currentSpace->getValue() << "?" << std::endl;
					//if they are, complete the sale
					if(yesOrNo()){
						//but only do it if player can actually afford it
						if(chosenPlayer->getMoney() > currentSpace->getValue()){
							PropertyAction sellPropertyToPlayer(thePlayer, chosenPlayer, currentSpace, &theBank, false, false, false);
							sellPropertyToPlayer.executeAction();
							std::cout << thePlayer->getPiece() << " sold " << currentSpace->getName() << " to " << chosenPlayer->getPiece() << " for $" << currentSpace->getValue() << std::endl;
						}else{
							std::cout << "Sorry, " << chosenPlayer->getPiece() << " doesn't have enough money for this transaction." << std::endl;
						}
					}else{
						std::cout << "Sorry " << thePlayer->getPiece() << ", " << chosenPlayer->getPiece() << " declined your offer." << std::endl;
					}
				}		
			}
			else{

			}
			choice++;
		}
		//if the space is unowned, present player with chance to buy it
		else if(!currentSpace->isOwned()){
			std::cout << "\t(" << choice << ") Buy " << currentSpace->getName() << " for $" << currentSpace->getValue() << "? (y/n)" << std::endl;
			if(yesOrNo()){
				PropertyAction buyProperty(thePlayer, NULL, currentSpace, &theBank, true, true, false);
				buyProperty.executeAction();
				std::cout << players[theTurn].getPiece() << " now has $" << players[theTurn].getMoney() << std::endl;
			}
			choice++;
		}
		//else, someone else owns the space, so player has to pay rent
		else{
			owesOtherPlayer = true;
			otherPlayer = currentSpace->getOwnerReference();
			std::string theOwner = currentSpace->getOwner();
			std::cout << "Darn! You have to pay " << theOwner << " $" << currentSpace->getRent() << "..." << std::endl;
			MoneyAction transaction(otherPlayer, currentSpace->getRent(), true);
			int amount = transaction.getAmount();
			transaction.executeAction();
			transaction.takeMoney(thePlayer, amount);
			transaction.executeAction();
			std::cout << players[theTurn].getPiece() << " now has $" << players[theTurn].getMoney() << std::endl;
			std::cout << theOwner << " now has $" << otherPlayer->getMoney() << std::endl;
		}
		theBoard->printBoard();
	}

	//if the player has run out of money
	if(!thePlayer->hasMoney()){
		//if the player lost last of their money to another player...
		if(owesOtherPlayer){
			std::cout << thePlayer->getPiece() << " is out of money, and now owes " << otherPlayer->getPiece() << " all his property. Sorry!" << std::endl;
			PropertyAction transferAllProperty(thePlayer, otherPlayer, NULL, &theBank, false, false, true);
			transferAllProperty.executeAction();
		}
		//else if they lost their money to the bank/THE MAN/Chest
		else{
			std::cout << thePlayer->getPiece() << " is out of money, and now owes The Bank all his property. Sorry!" << std::endl;
			std::cout << "Loosing:" << std::endl;
			thePlayer->printOwnedSpaces();

			PropertyAction transferAllProperty(thePlayer, NULL, NULL, &theBank, false, true, true);
			transferAllProperty.executeAction();
		}

		theTurn = -1;

	}

	return theTurn;
	
}

//if there is only one player left, game is over
int gameOver(){
	int over = 0;
	int count = 0;
	for(int i = 0; i < players.size(); i++){
		if(players[i].getInGame()){
			count++;
		}
	}
	if(count == 1) over = 1;

	return over; //temporary
}

// add cards to THE MAN deck and Chest Deck
void populateDecks(Game_Board* theBoard){
	//cards for THE MAN deck
	std::string description = "You didn't file your damn taxes. Pay THE MAN a fine of $100";
	theMan.addCard(new MoneyAction(NULL, 100, false, description));
	description = "You were caught J-walking. Pay ticket of $200.";
	theMan.addCard(new MoneyAction(NULL, 200, false, description));
	description = "You made a citizen's arrest! Collect reward of $200.";
	theMan.addCard(new MoneyAction(NULL, 200, true, description));
	description = "You became a high ranking government official. Collect salary of $150.";
	theMan.addCard(new MoneyAction(NULL, 150, true, description));
	description = "You jeopordized a top-secret mission. Pay fine of $500";
	theMan.addCard(new MoneyAction(NULL, 500, false, description));
	description = "THE MAN is watching you. Pay $150 for tin-foil hat.";
	theMan.addCard(new MoneyAction(NULL, 150, false, description));
	description = "You get a tax write-off. Collect $50.";
	theMan.addCard(new MoneyAction(NULL, 50, true, description));
	description = "You were caught speeding. Pay ticket of $350.";
	theMan.addCard(new MoneyAction(NULL, 350, false, description));
	description = "You littered! How dare you!. Pay fine of $500.";
	theMan.addCard(new MoneyAction(NULL, 500, false, description));
	description = "You won Ms. America! Collect $400.";
	theMan.addCard(new MoneyAction(NULL, 400, true, description));
	description = "You got a fat research stipend! Collect $300.";
	theMan.addCard(new MoneyAction(NULL, 300, true, description));
	description = "You are disliked. Pay $50.";
	theMan.addCard(new MoneyAction(NULL, 50, false, description));
	description = "You skipped jury duty. Pay fine of $450.";
	theMan.addCard(new MoneyAction(NULL, 450, false, description));
	description = "You attended jury duty. Collect compensation of $100.";
	theMan.addCard(new MoneyAction(NULL, 100, true, description));
	description = "THE MAN is poor. Give him $150.";
	theMan.addCard(new MoneyAction(NULL, 150, false, description));
	description = "You are poor. Collect handout of $100.";
	theMan.addCard(new MoneyAction(NULL, 100, true, description));
	description = "You are a menace to society. Pay $250!";
	theMan.addCard(new MoneyAction(NULL, 250, false, description));
	description = "You know too much. Here. Take this and shut up.";
	theMan.addCard(new MoneyAction(NULL, 200, true, description));
	description = "You are an oil mongol. Respect us! Here's $200";
	theMan.addCard(new MoneyAction(NULL, 200, true, description));
	description = "You are a good person. Here is $50.";
	theMan.addCard(new MoneyAction(NULL, 50, true, description));
	description = "You have been exiled to Siberia.";
	//14 is siberia's index in the gameboard spaces array
	theMan.addCard(new GoToAction(NULL, theBoard, theBoard->findSpaceByIndex(14), description));

	//cards for chest deck
	description = "Advance 3 spaces.";
	chest.addCard(new MoveAction(NULL, theBoard, 3, description));
	description = "Advance 20 spaces.";
	chest.addCard(new MoveAction(NULL, theBoard, 20, description));
	description = "You won the ugly pagent. Collect $50";
	chest.addCard(new MoneyAction(NULL, 50, true, description));
	description = "You won a trip to Las Vegas!";
	chest.addCard(new GoToAction(NULL, theBoard, theBoard->findSpaceByIndex(25), description));
	description = "Pack up and move to El Sob.";
	chest.addCard(new GoToAction(NULL, theBoard, theBoard->findSpaceByIndex(5), description));
	description = "Meet THE MAN";
	chest.addCard(new GoToAction(NULL, theBoard, theBoard->findSpaceByIndex(13), description));
	description = "They call it Debt Row...";
	chest.addCard(new GoToAction(NULL, theBoard, theBoard->findSpaceByIndex(31), description));
	description = "They call it Debt Row...";
	chest.addCard(new GoToAction(NULL, theBoard, theBoard->findSpaceByIndex(31), description));
	description = "Pack up and move to Brooklyn.";
	chest.addCard(new GoToAction(NULL, theBoard, theBoard->findSpaceByIndex(12), description));

	//shuffle dem decks
	theMan.shuffle();
	chest.shuffle();



}

//gets players pieces
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
		Player p;
		players.push_back(p);
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

//prints available pieces
void printAvailablePieces(int *availablePieces){

	for(int i = 0; i < NUM_PIECES; i++){
		if(availablePieces[i] == 1){
			std::cout << "(" << i+1 << ") " << pieces[i] << std::endl;
		} else{
			std::cout << "X Taken X " << pieces[i] << std::endl;

		}
	}

}

//occupies pieces array
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

//welcome and launch method
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

int getNumOptions(int start, int end){

	int x;

	do{

	std::cin >> x;

	if (std::cin.fail() || (x < start || x > end)){

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