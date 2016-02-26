#include "Player.h"

Player::Player(){
	score = 0;
}

Player::Player(char symbol){
		this->symbol = symbol;
		score = 0;
}

char Player::getSymbol() const{
	return symbol;
}

int Player::getScore() const{
	return score;
}

ostream& operator<< (ostream& os, const Player& p){
	return os << p.getSymbol();
}