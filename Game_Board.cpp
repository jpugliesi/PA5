//Game_Board.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include "Game_Board.h"

	/***** Constructors *****/

	//Creates a game board with number of players playing, and occupies the spaces
	Game_Board::Game_Board(int numPlayers){
		num_players = numPlayers;
		occupySpaces();
	}

	Game_Board::~Game_Board(){
	}

	//occupies the spaces array with predefined spaces, as follows:
	void Game_Board::occupySpaces(){

			spaces[0] = Space("Go", 1, false); 			
			spaces[1] = Space("Glassell", 2, true);
			spaces[2] = Space("*Chest*", 3, false);	 	
			spaces[3] = Space("Richmond", 4, true);
			spaces[4] = Space("TAX", 5, false); 
			spaces[5] = Space("El Sob", 6, true);
			spaces[6] = Space("*THE  MAN*", 7, false); 
			spaces[7] = Space("Terrace", 8, true);
			spaces[8] = Space("El Cerrito", 9, true); 
			spaces[9] = Space("Pinole", 10, true);
			spaces[10] = Space("", 11, false); 

			spaces[11] = Space("*Chest*", 12, false); 
			spaces[12] = Space("Brooklyn", 13, true);
			spaces[13] = Space("*THE  MAN*", 14, false); 
			spaces[14] = Space("Siberia", 15, true);
			spaces[15] = Space("", 16, false); 		
			spaces[16] = Space("Austin", 17, true);
			spaces[17] = Space("Memphis", 18, true); 
			spaces[18] = Space("Wichita", 19, true);
			spaces[19] = Space("*Chest*", 20, false);

			spaces[20] = Space("", 21, false); 
			spaces[21] = Space("Atlanta", 22, true);
			spaces[22] = Space("", 23, false); 		
			spaces[23] = Space("Tahoe", 24, true);
			spaces[24] = Space("*Chest*", 25, false); 
			spaces[25] = Space("Las Vegas", 26, true);
			spaces[26] = Space("*THE  MAN*", 27, false); 
			spaces[27] = Space("*Chest*", 28, false);
			spaces[28] = Space("Chicago", 29, true); 
			spaces[29] = Space("Seattle", 30, true);
			spaces[30] = Space("", 31, false);

			spaces[31] = Space("*THE  MAN*", 32, false); 
			spaces[32] = Space("TAX", 33, false);
			spaces[33] = Space("*THE  MAN*", 34, false); 
			spaces[34] = Space("New York", 35, true);
			spaces[35] = Space("*THE  MAN*", 36, false); 
			spaces[36] = Space("TAX", 37, false);
			spaces[37] = Space("*THE  MAN*", 38, false); 
			spaces[38] = Space("TAX", 39, false);
			spaces[39] = Space("San Fran", 0, true);
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