#ifndef GOTOACTION_H
#define GOTOACTION_H
#include "Action.h"
#include "Space.h"
#include "Game_Board.h"
#include "Player.h"

class GoToAction : public Action{

	private:
		Space* currentSpace;
		Space* newSpace;
		Game_Board* theBoard;
		Player* player;
	public:
		GoToAction();
		GoToAction(Player&, Game_Board&, Space&);
		void executeAction();


};

#endif
