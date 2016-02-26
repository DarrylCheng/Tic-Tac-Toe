#include <iostream>
#include <cstdlib>
#include <sstream>
#include "Board.h"
#include "Player.h"
using namespace std;

void getInput(int&,int&);

int main(){
	/* Tic Tac Toe Game */

	//Create 2 players, X and O.
	Player players[2] = {Player('X'),Player('O')};
	int turn = 0;

	//Create game board
	Board board;

	//initializing variables
	int row, col;

	do{
		//Banner
		system("cls");
		cout << "\tTic Tac Toe\n\n";
		board.displayBoard();
		cout << "\nPlayer " << players[turn] << "\'s turn. \n";
		cout << "Enter the coordinate to input, row then column.\n\n";

		try{
			getInput(row,col);
			board.insert(row, col, players[turn].getSymbol());
		} catch ( Exceptions e ){
			cout << endl << e.getMsg() << endl;
			system("pause");
			continue;
		}
		if(board.winConditionsMet()){
			system("cls");
			cout << "\tTic Tac Toe\n\n";
			board.displayBoard();
			cout << "\nThe winner is " << players[turn];
			break;
		}
		turn = (turn + 1) % 2;
	} while (true);
}

void getInput(int& row, int& col){
	string raw_row, raw_col;
	cin.sync();
	cout << "Enter row : ";
	cin >> raw_row;
	cout << "Enter column : ";
	cin >> raw_col;
	if(!(istringstream(raw_row) >> row ) || !(istringstream(raw_col) >> col )){
		throw Exceptions("Error: Non-integer input detected.");
	}
}