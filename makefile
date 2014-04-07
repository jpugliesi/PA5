OBJS = Action.o MoneyAction.o MoveAction.o Bank.o Card.o Game_Board.o Player.o Space.o Die.o simponopoly.o
CC = g++
Debug = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

simponopoly : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o simponopoly

Action.o : Action.cpp Action.h
	$(CC) $(CFLAGS) Action.cpp

MoneyAction.o : MoneyAction.cpp MoneyAction.h Action.h
	$(CC) $(CFLAGS) MoneyAction.cpp

MoveAction.o : MoveAction.cpp MoveAction.h Action.h
	$(CC) $(CFLAGS) MoveAction.cpp

Bank.o : Bank.cpp Bank.h
	$(CC) $(CFLAGS) Bank.cpp

Card.o : Card.cpp Card.h
	$(CC) $(CFLAGS) Card.cpp

Game_Board.o : Game_Board.cpp Game_Board.h Space.h
	$(CC) $(CFLAGS) Game_Board.cpp

Player.o : Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp

Space.o : Space.cpp Space.h Player.h Action.h
	$(CC) $(CFLAGS) Space.cpp

Die.o : Die.cpp Die.h
	$(CC) $(CFLAGS) Die.cpp

simponopoly.o : simponopoly.cpp
	$(CC) $(CFLAGS) simponopoly.cpp

clean:
	\rm *.o *~ simponopoly