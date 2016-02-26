#include "Board.h"

Board::Board(){
	size = 3;
	board = new char*[size];
	for(int i = 0; i < size; i++){
		board[i] = new char[size];
	}
	for(int row = 0; row < size; row++){
		for(int col = 0; col < size; col++){
			board[row][col] = '*';
		}
	}
}

Board::~Board(){
	delete board;
}

void Board::displayBoard() const{
	cout << "\t   1 2 3\n";
	for(int row = 0; row < size; row++){
		cout << "\t" << row+1 << "  ";
		for(int col = 0; col < size; col++){
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
}

void Board::insert(int row,int col, char symbol) throw(Exceptions){
	row--; col--;
	bool ROWANDCOL_INRANGE = row>=0 && row <size && col>=0 && col <size;
	if( !ROWANDCOL_INRANGE ){
		throw(Exceptions("Input row & column out of range or already occupied."));
	}
	bool ROWANDCOL_EMPTY = ( board[row][col] == '*' );
	if ( ROWANDCOL_EMPTY ){
		board[row][col] = symbol;
	} else {
		throw(Exceptions("Input row & column out of range or already occupied."));
	}
}

bool Board::winConditionsMet(){
	bool conditionsMet = false;
	for (int i = 0; i < size; i++){
		if ( board[0][i] != '*' && (board[0][i]==board[1][i]?board[0][i]:false) == board[2][i] ){
			//Check vertically
			conditionsMet = true;
		}
		if ( board[i][0] != '*' && (board[i][0]==board[i][1]?board[i][0]:false) == board[i][2] ){
			//Check horizontally
			conditionsMet = true;
		}
	}
	//Check diagonally
	if( board[0][0] != '*' && (board[0][0]==board[1][1]?board[0][0]:false) == board[2][2] ){
		conditionsMet = true;
	}
	if( board[0][2] != '*' && (board[0][2]==board[1][1]?board[0][2]:false) == board[2][0] ){
		conditionsMet = true;
	}
	return conditionsMet;
}