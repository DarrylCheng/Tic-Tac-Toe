#include <iostream>
#include <cstdlib>
#include <sstream>
#include "Board.h"
#include "Player.h"
using namespace std;

void getInput(int&);

int main(){
	/* Tic Tac Toe Game */

	//Create 2 players, X and O. True = AI, false = Player
	Player players[2] = {Player('X',false),Player('O',true)};
	int turn = 0;

	//Create game board
	Board board;
	board.setPlayers(players[0],players[1]);

	//initializing variables
	int num;

	while ( board.isEmpty() ){
		system("cls");
		cout << "\tTic Tac Toe\n\n";
		board.displayBoard();
		cout << "\nPlayer " << players[turn] << "\'s turn. \n";
		cout << "Enter the index number you want to input into.\n\n";
		try{
			if(board.isComputer(turn)){
				board.computer(turn);
			} else {
				cout << "Suggested moves: ";
				board.suggestedMoves(turn);
				getInput(num);
				if (num == 911){
					return 0;
				}
				board.insert(num, turn);
			}
		} catch ( Exceptions e ){
			cout << endl << e.getMsg() << endl;
			system("pause");
			continue;
		}
		if( board.winConditionsMet(board.getBoard()) )
			break;
		turn = (turn + 1) % 2;
	}

	system("cls");
	cout << "\tTic Tac Toe\n\n";
	board.displayBoard();
	if(board.winConditionsMet(board.getBoard())){
		cout << "\nThe winner is " << players[turn];
	} else {
		cout << "\nA draw game!";
	}
	
}

void getInput(int& num){
	string raw_num;
	cin.sync();
	cout << "Enter number : ";
	cin >> raw_num;
	if( !(istringstream(raw_num) >> num ) ){
		throw Exceptions("Error: Non-integer input detected.");
	}
}