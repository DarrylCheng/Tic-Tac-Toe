#include <iostream>
#include <cstdlib>
#include <sstream>
#include "Board.h"
#include "Player.h"
using namespace std;

void getInput(int&);

int main(){
	/* Tic Tac Toe Game */
	while(true){
		system("cls");
		cout << "\tTic Tac Toe\n\n";
		cout << "\t1. Play with Computer (You first)\n";
		cout << "\t2. Play with Computer (Computer first)\n";
		cout << "\t3. Play with your friend\n";
		cout << "\t4. *NEW* Play with Computer with hints (You first)\n";
		cout << "\t5. *NEW* Play with Computer with hints (Computer first)\n";
		cout << "\n\t6. Quit\n\n";

		int turn = 0;
		bool hints = false;
		bool player1, player2;
		try{
		int input;
			getInput(input);
			switch(input){
				//True = AI, False = Player
				case 1: player1 = false; player2 = true; break;
				case 2: player1 = true; player2 = false; break;
				case 3: player1 = false; player2 = false; break;
				case 4: player1 = false; player2 = true; hints = true; break;
				case 5: player1 = true; player2 = false; hints = true; break;
				case 6: return 0;
			}
			if(input <=0 || input >=7)
				throw Exceptions("Input out of range.");
		} catch ( Exceptions e ){
			cout << endl << e.getMsg() << endl;
			system("pause");
			continue;
		}

		Player players[2] = {Player('X',player1),Player('O',player2)};

		//Create game board
		Board board;
		board.setPlayers(players[0],players[1]);

		while ( board.isEmpty() ){
			int num;
			system("cls");
			cout << "\tTic Tac Toe\n\n";
			board.displayBoard();
			cout << "\nPlayer " << players[turn] << "\'s turn. \n";
			cout << "Enter the index number you want to input into.\n\n";
			try{
				if(board.isComputer(turn)){
					board.computer(turn);
				} else {
					if(hints){
						cout << "Suggested moves: ";
						board.suggestedMoves(turn);
					}
					getInput(num);
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
			if(board.isComputer(turn))
				cout << "\nThe computer won and you lost.";
			cout << "\nThe winner is " << players[turn] << endl;
		} else {
			cout << "\nA draw game!\n";
		}
		system("pause");
	}
	
}

void getInput(int& num){
	string raw_num;
	cin.sync();
	cout << "Enter number : ";
	cin >> raw_num;
	if( !(istringstream(raw_num) >> num ) || raw_num.length()>1){
		throw Exceptions("Error: Non-integer input detected.");
	}
}