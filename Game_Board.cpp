//Game_Board.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include "Game_Board.h"
#include "CardAction.h"
#include "MoneyAction.h"

	/***** Constructors *****/

	//Creates a game board with number of players playing, and occupies the spaces
	Game_Board::Game_Board(int numPlayers, Bank* bank, Deck* theMan, Deck* chestDeck){
		num_players = numPlayers;
		theBank = bank;
		theManDeck = theMan;
		theChestDeck = chestDeck;
		occupySpaces();
	}

	Game_Board::~Game_Board(){
	}

	//occupies the spaces array with predefined spaces, as follows:
	void Game_Board::occupySpaces(){

			spaces[0] = Space("Go", 1, false, 0); 	//give GoAction		
			spaces[1] = Space("Glassell", 2, true, 50);
			spaces[2] = Space("*Chest*", 3, false, 60);	 	
			spaces[3] = Space("Richmond", 4, true, 70);
			spaces[4] = Space("TAX", 5, false, 0); 
			spaces[5] = Space("El Sob", 6, true, 100);
			spaces[6] = Space("*THE  MAN*", 7, false, 0); 
			spaces[7] = Space("Terrace", 8, true, 110);
			spaces[8] = Space("El Cerrito", 9, true, 120); 
			spaces[9] = Space("Pinole", 10, true, 130);
			spaces[10] = Space("", 11, false, 0); 

			spaces[11] = Space("*Chest*", 12, false, 0); 
			spaces[12] = Space("Brooklyn", 13, true, 150);
			spaces[13] = Space("*THE  MAN*", 14, false, 0); 
			spaces[14] = Space("Siberia", 15, true, 150);
			spaces[15] = Space("", 16, false, 0); 		
			spaces[16] = Space("Austin", 17, true, 170);
			spaces[17] = Space("Memphis", 18, true, 170); 
			spaces[18] = Space("Wichita", 19, true, 180);
			spaces[19] = Space("*Chest*", 20, false, 0);

			spaces[20] = Space("", 21, false, 0); 
			spaces[21] = Space("Atlanta", 22, true, 200);
			spaces[22] = Space("", 23, false, 0); 		
			spaces[23] = Space("Tahoe", 24, true, 210);
			spaces[24] = Space("*Chest*", 25, false, 0); 
			spaces[25] = Space("Las Vegas", 26, true, 250);
			spaces[26] = Space("*THE  MAN*", 27, false, 0); 
			spaces[27] = Space("*Chest*", 28, false, 0);
			spaces[28] = Space("Chicago", 29, true, 270); 
			spaces[29] = Space("Seattle", 30, true, 300);
			spaces[30] = Space("", 31, false, 0);

			spaces[31] = Space("*THE  MAN*", 32, false, 0); 
			spaces[32] = Space("TAX", 33, false, 0);
			spaces[33] = Space("*THE  MAN*", 34, false, 0); 
			spaces[34] = Space("New York", 35, true, 400);
			spaces[35] = Space("*THE  MAN*", 36, false, 0); 
			spaces[36] = Space("TAX", 37, false, 0);
			spaces[37] = Space("*THE  MAN*", 38, false, 0); 
			spaces[38] = Space("TAX", 39, false, 0);
			spaces[39] = Space("San Fran", 0, true, 500);

			for(int i = 0; i < NUM_SPACES; i++){
				if(spaces[i].isOwnable() || spaces[i].getName() == ""){
					spaces[i].setAction(NULL);
				}
				//else for THE MAN and TAX, and GO, and SPACE
				else if(spaces[i].getName() == "*THE  MAN*"){
					spaces[i].setAction(new CardAction(theManDeck));
				}else if(spaces[i].getName() == "TAX"){
					spaces[i].setAction(new MoneyAction(NULL, 100, false, "Woops! Pay tax of $100."));
				}else if(spaces[i].getName() == "*Chest*"){
					spaces[i].setAction(new CardAction(theChestDeck));
				}
			}
			
	}

	//Prints out the game board
	void Game_Board::printBoard(){

		printBoardRowReverse(0, 10, false); //print out the top row of spaces
		int firstSpace = 39;
		int secondSpace = 11;

		//print out the middle rows (there are nine of them)
		for(int i = 0; i < 9; i++){
			printMiddleRow(firstSpace--, secondSpace++);
			if(i != 8){
				printBottom();
			}
		}

		//print out the bottom row of spaces
		printBoardRowReverse(20, 30, true);

	}

	//prints out a row of 11 spaces from firstSpace to lastSpace
	//prints in reverse order if isReverse is true
	void Game_Board::printBoardRowReverse(int firstSpace, int lastSpace, bool isReverse){

		int spacesToPrint = abs(lastSpace - firstSpace) + 1;

		if(!isReverse){
			printTopLine(spacesToPrint);
			printRowWithName(spacesToPrint, firstSpace, isReverse);
			printRowWithOwner(spacesToPrint, firstSpace, isReverse);
			printRowWithCharacter(spacesToPrint, ' ');
			printRowWithCurrentPlayers(spacesToPrint, firstSpace, isReverse);
			printTopLine(spacesToPrint);
		} else{
			printTopLine(spacesToPrint);
			printRowWithName(spacesToPrint, lastSpace, isReverse);
			printRowWithOwner(spacesToPrint, lastSpace, isReverse);
			printRowWithCharacter(spacesToPrint, ' ');
			printRowWithCurrentPlayers(spacesToPrint, lastSpace, isReverse);
			printTopLine(spacesToPrint);
		}
	}

	//Prints middle row with two spaces on either edge of the baord
	//those spaces are in spaces[space1Index] and spaces[space2Index]
	void Game_Board::printMiddleRow(int space1Index, int space2Index){

		//print out each spaces name, centered and ending with a |
		int padding = SPACE_WIDTH-2;

		for(int i = 0; i < SPACES_IN_ROW; i++){
			if(i == 0){
				Space current = spaces[space1Index];
				std::cout << "|" << std::left << std::setw(padding) << centerString(current.getName()) << "|";
			} else if(i == 10){
				Space current = spaces[space2Index];
				std::cout << "|" << std::left << std::setw(padding) << centerString(current.getName()) << "|";
			}else{
				int x = 1;
				if(i == 9) x = 2;
				for(int j = 0; j < SPACE_WIDTH - x; j++){
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl; // right side ending bracket

		//print out each spaces Owner, centered and ending with a |
		for(int i = 0; i < SPACES_IN_ROW; i++){
			if(i == 0){
				Space current = spaces[space1Index];
				if(current.isOwnable()){
					std::string owner = current.getOwner();
					std::string ownerLine = "Owner: " + owner;
					std::cout << "|" << std::left << std::setw(padding) << centerString(ownerLine) << "|";
				}else{
					std::cout << "|";
					for(int j = 0; j < SPACE_WIDTH - 2; j++){
						std::cout << " ";
					}
					std::cout << "|";
				}
			} else if(i == 10){
				Space current = spaces[space2Index];
				if(current.isOwnable()){
					std::string owner = current.getOwner();
					std::string ownerLine = "Owner: " + owner;
					std::cout << "|" << std::left << std::setw(padding) << centerString(ownerLine) << "|";
				} else{
					std::cout << "|";
					for(int j = 0; j < SPACE_WIDTH - 2; j++){
						std::cout << " ";
					}
					std::cout << "|";
				}
			}else{
				int x = 1;
				if(i == 9) x = 2;
				for(int j = 0; j < SPACE_WIDTH - x; j++){
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;

		for(int i = 0; i < SPACES_IN_ROW; i++){
			if(i == 0 || i == 10){
				std::cout << "|";
				for(int j = 0; j < SPACE_WIDTH-2; j++){
					std::cout << " ";
				}
				std::cout << "|";
			}else{
				int x = 1;
				if(i == 9) x = 2;
				for(int j = 0; j < SPACE_WIDTH - x; j++){
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;

		//Prints out the players currently on each space
		for(int i = 0; i < SPACES_IN_ROW; i++){
			if(i == 0){
				Space current = spaces[space1Index];
				std::string result = current.playersOnSpaceToString();
				std::cout << "|" << std::left << std::setw(padding) << centerString(result) << "|";
			} else if(i == 10){
				Space current = spaces[space2Index];
				std::string result = current.playersOnSpaceToString();
				std::cout << "|" << std::left << std::setw(padding) << centerString(result) << "|";
			}else{
				int x = 1;
				if(i == 9) x = 2;
				for(int j = 0; j < SPACE_WIDTH - x; j++){
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;

	}

	void Game_Board::printBottom(){

		//print bottom line for middle rows, ending with a |
			for(int i = 0; i < SPACES_IN_ROW; i++){
				if(i == 0 || i == 10){
					for(int j = 0; j < SPACE_WIDTH; j++){
						std::cout << "-";
					}
				}else{
					int x = 1;
					if(i == 9) x = 2;
					for(int j = 0; j < SPACE_WIDTH - x; j++){
						std::cout << " ";
					}
				}
			}
			std::cout << std::endl;

	}

	//Prints sequence of '-' characters to make a top line for the board
	void Game_Board::printTopLine(int numSpaces){
		//Print out top row of - for all boxes
		for(int i = 0; i < numSpaces; i++){
			for(int j = 0; j < SPACE_WIDTH-1; j++){
				std::cout << "-";
			}
			if(i == numSpaces-1){
				std::cout << "-";	//prints out a final - to solve off by one printing problem
			}
		}
		std::cout << std::endl;
	}

	//print out each spaces name, centered and ending with a |
	void Game_Board::printRowWithName(int numSpaces, int firstSpace, bool isReverse){
		
		int padding = SPACE_WIDTH -2;

		if(!isReverse){
			for(int i = 0; i < numSpaces; i++){
				Space current = spaces[firstSpace + i]; //gets current space
				std::cout << "|" << std::left << std::setw(padding) << centerString(current.getName());
			}
			std::cout << "|" << std::endl; // right side ending bracket
		} else{
			for(int i = 0; i < numSpaces; i++){
				Space current = spaces[firstSpace - i]; //gets current space
				std::cout << "|" << std::left << std::setw(padding) << centerString(current.getName());
			}
			std::cout << "|" << std::endl; // right side ending bracket
		}
	}

	//print out each spaces owner, centered and ending with a |
	void Game_Board::printRowWithOwner(int numSpaces, int firstSpace, bool isReverse){
		
		int padding = SPACE_WIDTH -2;

		if(!isReverse){
			for(int i = 0; i < numSpaces; i++){
				Space current = spaces[firstSpace + i]; //gets current space
				//only print out if the space is ownable
				if(current.isOwnable()){
					std::string owner = current.getOwner();
					std::string ownerLine = "Owner: " + owner;
					std::cout << "|" << std::left << std::setw(padding) << centerString(ownerLine);
				}else{
					std::cout << "|";
					for(int j = 0; j < SPACE_WIDTH - 2; j++){
						std::cout << " ";
					}
				}
			}
			std::cout << "|" << std::endl; // right side ending bracket
		}else{
			for(int i = 0; i < numSpaces; i++){
				Space current = spaces[firstSpace - i]; //gets current space
				//Only print out if the space is ownable
				if(current.isOwnable()){
					std::string owner = current.getOwner();
					std::string ownerLine = "Owner: " + owner;
					std::cout << "|" << std::left << std::setw(padding) << centerString(ownerLine);
				}else{
					std::cout << "|";
					for(int j = 0; j < SPACE_WIDTH - 2; j++){
						std::cout << " ";
					}
				}
			}
			std::cout << "|" << std::endl; // right side ending bracket
		}
	}

	//print out each spaces current players on that space, centered and ending with a |
	void Game_Board::printRowWithCurrentPlayers(int numSpaces, int firstSpace, bool isReverse){
		
		int padding = SPACE_WIDTH -2;
		std::stringstream ss;

		//run in regular order if not printing in reverse
		if(!isReverse){
			for(int i = 0; i < numSpaces; i++){
				Space current = spaces[firstSpace + i]; //gets current space
				std::string result = current.playersOnSpaceToString();
				std::cout << "|" << std::left << std::setw(padding) << centerString(result);
			}
			std::cout << "|" << std::endl; // right side ending bracket
		//else print the spaces as if in reverse order
		}else{
			for(int i = 0; i < numSpaces; i++){
				Space current = spaces[firstSpace - i]; //gets current space
				std::string result = current.playersOnSpaceToString(); //gets current players on the space
				std::cout << "|" << std::left << std::setw(padding) << centerString(result);
			}
			std::cout << "|" << std::endl; // right side ending bracket
		}
	}

	//Prints row of spaces, where each space is filled with character x
	//frequently used with ' '  character to make blank spaces
	void Game_Board::printRowWithCharacter(int numSpaces, char x){
		//print a blank row
		for(int i = 0; i < numSpaces; i++){
			std::cout << "|";
			for(int j = 0; j < SPACE_WIDTH-2; j++){
				std::cout << x;
			}
		}
		std::cout << "|" << std::endl;
	}

	//produces a string that will be centered within the 10 character wide inside of a space
	std::string Game_Board::centerString(std::string toCenter){
		std::stringstream ss;
		int len = toCenter.size();
		int position = (int) (10 - len)/2;
		for(int i = 0; i < position; i++){
			ss << " ";
		}

		ss << toCenter;
		std::string result = ss.str();
		ss.clear();
		ss << "";
		return result;
	}

	//finds and returns a pointer to a Space object at a provided index
	Space* Game_Board::findSpaceByIndex(int index){
		return &(spaces[index]);
	}

	Bank* Game_Board::getBank(){
		return theBank;
	}

	void Game_Board::updateNumPlayers(int n){
		num_players = n;
	}