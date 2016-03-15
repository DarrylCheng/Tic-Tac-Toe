#include "Player.h"

Player::Player():score(0){}
Player::Player(char symbol, bool isComputer):symbol(symbol),isComputer(isComputer), score(0){}

char Player::getSymbol() const{
	return symbol;
}

int Player::getScore() const{
	return score;
}

bool Player::isComp() const{
	return isComputer;
}

ostream& operator<< (ostream& os, const Player& p){
	return os << p.getSymbol();
}