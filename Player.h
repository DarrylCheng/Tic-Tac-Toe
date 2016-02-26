#ifndef PLAYER_H
#define PLAYER_H
using namespace std;

class Player{
	char symbol;
	int score;
public:
	Player();
	Player(char symbol);

	char getSymbol() const;
	int getScore() const;
	friend ostream& operator<< (ostream& os, const Player& p);
};

#include "Player.cpp"
#endif