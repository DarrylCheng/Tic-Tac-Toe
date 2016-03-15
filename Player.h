#ifndef PLAYER_H
#define PLAYER_H
using namespace std;

class Player{
	char symbol;
	bool isComputer;
	int score;
public:
	Player();
	Player(char symbol, bool isComputer);

	char getSymbol() const;
	int getScore() const;
	bool isComp() const;

	friend ostream& operator<< (ostream& os, const Player& p);
};

#include "Player.cpp"
#endif