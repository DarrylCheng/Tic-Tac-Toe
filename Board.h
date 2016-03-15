#ifndef BOARD_H
#define BOARD_H
#include "Exceptions.h"
#include "Player.h"


class Board{
	int minimax(char * pboard, int turn, int depth);
	char * board;
	Player players[2];
	int size;
public:
	Board();
	~Board();

	void displayBoard() const;
	void insert(int num, int turn) throw(Exceptions);
	void setPlayers(Player& p1, Player& p2);
	bool isComputer(int turn) const;
	bool winConditionsMet(char * pboard);
	bool isEmpty() const; //If board is filled, returns false.
	char* getBoard() const;
	void computer(int turn);
	void suggestedMoves(int turn);
};

#include "Board.cpp"
#endif