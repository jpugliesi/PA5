OBJS = Action.o MoneyAction.o MoveAction.o GoToAction.o PropertyAction.o CardAction.o Bank.o Deck.o Game_Board.o Player.o Space.o Die.o simponopoly.o
CC = g++
Debug = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: $(OBJS) simponopoly

simponopoly : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o simponopoly

Action.o : Action.cpp Action.h
	$(CC) $(CFLAGS) Action.cpp

MoneyAction.o : MoneyAction.cpp MoneyAction.h Action.h
	$(CC) $(CFLAGS) MoneyAction.cpp

MoveAction.o : MoveAction.cpp MoveAction.h Action.h
	$(CC) $(CFLAGS) MoveAction.cpp

GoToAction.o : GoToAction.cpp GoToAction.h Action.h
	$(CC) $(CFLAGS) GoToAction.cpp

PropertyAction.o : PropertyAction.cpp PropertyAction.h Action.h
	$(CC) $(CFLAGS) PropertyAction.cpp

CardAction.o : CardAction.cpp CardAction.h Action.h
	$(CC) $(CFLAGS) CardAction.cpp

Bank.o : Bank.cpp Bank.h
	$(CC) $(CFLAGS) Bank.cpp

Deck.o : Deck.cpp Deck.h
	$(CC) $(CFLAGS) Deck.cpp

Game_Board.o : Game_Board.cpp Game_Board.h Space.h
	$(CC) $(CFLAGS) Game_Board.cpp

Space.o : Space.cpp Space.h Player.h Action.h
	$(CC) $(CFLAGS) Space.cpp

Player.o : Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp

Die.o : Die.cpp Die.h
	$(CC) $(CFLAGS) Die.cpp

simponopoly.o : simponopoly.cpp
	$(CC) $(CFLAGS) simponopoly.cpp

clean:
	\rm *.o *~ simponopoly