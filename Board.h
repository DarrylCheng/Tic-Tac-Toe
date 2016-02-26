#ifndef BOARD_H
#define BOARD_H
#include "Exceptions.h"

class Board{
	char ** board;
	int size;
public:
	Board();
	~Board();

	void displayBoard() const;
	void insert(int row,int col, char symbol) throw(Exceptions);
	bool winConditionsMet();
};

#include "Board.cpp"
#endif