#include "Board.h"
#include <cstdlib>
#include <vector>
#include <ctime>

Board::Board(){
	size = 9;
	board = new char[size];
	char index = '1';
	for(int i = 0; i < size; i++){
		board[i] = index++;
	}
}

Board::~Board(){
	delete board;
}

void Board::displayBoard() const{
	int x;
	for(x=0;x<size;x++){
		cout << "\t";
		for(int i=0;i<3;i++){
			cout << board[x++];
			if(i!=2){
				cout << " | ";
			}
		}
		x--;
		cout << endl << "\t=========" << endl;
	}
}

void Board::insert(int num, int turn) throw(Exceptions){
	num--;
	bool INPUT_INRANGE = num>=0 && num <=size;
	if( !INPUT_INRANGE ){
		throw(Exceptions("Input out of range or already occupied."));
	}
	bool FIELD_EMPTY = ( board[num] != 'X' && board[num] != 'O' );
	if ( FIELD_EMPTY ){
		board[num] = players[turn].getSymbol();
	} else {
		throw(Exceptions("Input out of range or already occupied."));
	}
}

void Board::setPlayers(Player& p1, Player& p2){
	players[0] = p1;
	players[1] = p2;
}

bool Board::isComputer(int turn) const{
	return players[turn].isComp();
}

bool Board::winConditionsMet(char * pboard){
	bool conditionsMet = false;
	static char winningConditions[8][3] = { {1,2,3},{4,5,6},{7,8,9}
										,{1,4,7},{2,5,8},{3,6,9}
										,{1,5,9},{3,5,7} };
	for(int i=0 ; i<8 && !conditionsMet ; i++){
		if(pboard[winningConditions[i][0]-1] == pboard[winningConditions[i][1]-1]){
			if(pboard[winningConditions[i][0]-1] == pboard[winningConditions[i][2]-1]){
					conditionsMet = true;
			}
		}
	}
	return conditionsMet;
}

char* Board::getBoard() const{
	return board;
}

bool Board::isEmpty() const{
	char index = '1';
	for(int x=0; x<size; x++){
		if (board[x] == index+x)
			return true;
	}
	return false;
}

// int count = 0;
int Board::minimax(char * pboard, int turn, int depth){
	// count++;
	if(winConditionsMet(pboard) && !players[turn].isComp()){
		return 20-depth; //bigger the better
	} else if(winConditionsMet(pboard) && players[turn].isComp()){
		return depth-20; //smaller the better
	}
	depth++;

	int score = -50;
	turn = (turn+1) % 2;
	int v;
	bool move = false;
	for(int i=0;i<9;i++){
		if(board[i] != 'X' && board[i] != 'O'){
			char temp = board[i];
			board[i] = players[turn].getSymbol();

			v = minimax(pboard,turn,depth);
			board[i] = temp;

			if (score == -50){
				score = v;
			} else if (players[turn].isComp()){
				score = min(score,v);
			} else {
				score = max(score,v);
			}

			move = true;
		}
	}
	if(!move)
		return 0;

	return score;
}

void Board::computer(int turn){
	int score = 100;
	int v;
	vector<int> index;
	// count = 0;
	for(int i=0;i<9;i++){
		if(board[i] != 'X' && board[i] != 'O'){
			char temp = board[i];
			board[i] = players[turn].getSymbol();

			v = minimax(board,turn,0);

			if(score > v){
				index.clear();
				score = v;
				index.push_back(i);
			} else if ( score == v ){
				index.push_back(i);
			}
			board[i] = temp;
		}
	}
	srand( time(NULL) );
	int num = rand() % index.size();
	num = index[num];

	//549945 First move.
	// cout << "Number of recursions done : " << count << endl;
	// system("pause");
	board[num] = players[turn].getSymbol(); //Make move
}

void Board::suggestedMoves(int turn){
	int score = -100;
	bool isDraw = true;
	int v;
	vector<int> index;

	for(int i=0;i<9;i++){
		if(board[i] != 'X' && board[i] != 'O'){
			char temp = board[i];
			board[i] = players[turn].getSymbol();

			v = minimax(board,turn,0);

			if(v != 0){
				isDraw = false;
			}
			if(score < v){
				index.clear();
				score = v;
				index.push_back(i);
			} else if ( score == v ){
				index.push_back(i);
			}

			board[i] = temp;
		}
	}

	if(score == -19){
		cout << "You're screwed.\n";
	} else if (isDraw){
		cout << "No advantageous moves.\n";
	} else {
		for(int i=0;i<index.size();i++){
			cout << index[i]+1 << " ";
		}
		cout << endl;
	}
}


int Board::minimaxAB(char * pboard, int turn, int depth,int &alpha,int &beta){
	if(winConditionsMet(pboard) && !players[turn].isComp()){
		return 20-depth; //bigger the better
	} else if(winConditionsMet(pboard) && players[turn].isComp()){
		return depth-20; //smaller the better
	}
	depth++;

	int score = -50;

	turn = (turn+1) % 2;
	int v;
	bool move = false;
	for(int i=0;i<9;i++){
		if(board[i] != 'X' && board[i] != 'O'){
			char temp = board[i];
			board[i] = players[turn].getSymbol();

			v = minimaxAB(pboard,turn,depth,alpha,beta);
			board[i] = temp;

			//If computer, selects the MAXIMUM from its min. Hence Alpha
			// if(players[turn].isComp()){ 

			// } else{

			// }
			if(players[turn].isComp()){ 
				if(score == -50){
					score = v;
				} else {
					score = min(score,v);
				}
			} else{
				if(score == -50){
					score = v;
				} else {
					score = max(score,v);
				}
			}
			move = true;
		}
	}
	if(!move)
		return 0;

	return score;
}

void Board::computerAB(int turn){
	int score = 100;
	int v;
	vector<int> index;
	int a = -10000, b= 10000;

	for(int i=0;i<9;i++){
		if(board[i] != 'X' && board[i] != 'O'){
			char temp = board[i];
			board[i] = players[turn].getSymbol();

			v = minimaxAB(board,turn,0,a,b);

			if(score > v){
				index.clear();
				score = v;
				index.push_back(i);
			} else if ( score == v ){
				index.push_back(i);
			}
			board[i] = temp;
		}
	}
	srand( time(NULL) );
	int num = rand() % index.size();
	num = index[num];

	board[num] = players[turn].getSymbol(); //Make move
}