//============================================================================
// Name        : TicTacToe.cpp
// Author      : David Huang
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Computer plays this game using MINIMAX algorithm.
//============================================================================

#include <iostream>
#include <list>

using namespace std;

#define _MAX +2048
#define _MIN -2048

static enum {PLAYING, OWIN, XWIN, DRAW} state;

struct Player{
	char	symbol;		//'X' or 'O' or ' '
	bool	myTurn;
};

class TicTacToe{
	int		board[10];
	Player	player1;	//Human
	Player	player2;	//Computer uses the "minimax" algorithm



	void	init();
	bool	checkState();
	bool	createMoveList(int board[10], list<int> &moveList);

	int		minimax();
	int		minMove(int board[10]);
	int		maxMove(int board[10]);

public:
	void showBoard();
	bool play();
};

bool TicTacToe::checkState()
{
	bool draw = true;
	if((board[1] == board[2] && board[2] == board[3] && board[1] != 0) ||
			(board[4] == board[5] && board[5] == board[6] && board[4] != 0) ||
			(board[7] == board[8] && board[8] == board[9] && board[7] != 0) ||
			(board[1] == board[5] && board[5] == board[9] && board[1] != 0) ||
			(board[3] == board[5] && board[5] == board[7] && board[3] != 0) ||
			(board[1] == board[4] && board[4] == board[7] && board[1] != 0) ||
			(board[2] == board[5] && board[5] == board[8] && board[2] != 0) ||
			(board[3] == board[6] && board[6] == board[9] && board[3] != 0)){
		if(player1.myTurn == true){
			state = XWIN;
		}
		else{
			state = OWIN;
		}
	}
	else{
		for(int i=1; i<=9; i++){
			if(board[i] == 0)
				draw = false;
		}
		if(draw == true)
			state = DRAW;
	}
	return true;
}

bool TicTacToe::createMoveList(int board[10], list<int> &moveList)
{
	for(int i=1; i<=9; i++){
		if(board[i] == 0){
			moveList.push_back(i);
		}
	}
	return true;
}

int TicTacToe::minimax()
{
	list<int> moveList;
	int bestMove;
	int val = _MIN;
	int minMoveVal;

	createMoveList(board, moveList);

	while(!moveList.empty()){
		player1.myTurn = false;
		player2.myTurn = true;

		board[moveList.front()] = 2;
		checkState();
		if(state == OWIN){
			state = PLAYING;
			bestMove = moveList.front();
			board[moveList.front()] = 0;
			return bestMove;
		}

		minMoveVal = minMove(board);
		if(minMoveVal >= val){
			val = minMoveVal;
			bestMove = moveList.front();
		}
		board[moveList.front()] = 0;
		moveList.pop_front();
	}
	return bestMove;
}

int TicTacToe::minMove(int board[10])
{
	list<int> moveList;
	int bestMove;		//Just for debug within this function.
	int val = _MAX;
	int maxMoveVal;

	createMoveList(board, moveList);

	while(!moveList.empty()){
		player1.myTurn = true;
		player2.myTurn = false;
		board[moveList.front()] = 1;
		checkState();
		if(state == XWIN){
			state = PLAYING;
			bestMove = moveList.front();
			board[moveList.front()] = 0;
			return _MIN;	//Worst for computer player, so minimum number can make sure this move is excluded.
		}
		else if(state == DRAW){
			state = PLAYING;
			bestMove = moveList.front();
			board[moveList.front()] = 0;
			return 0;
		}
		else{
			maxMoveVal = maxMove(board);
			if(maxMoveVal <= val){
				val = maxMoveVal;
				bestMove = moveList.front();
			}
		}

		board[moveList.front()] = 0;
		moveList.pop_front();
	}
	return val;
}

int TicTacToe::maxMove(int board[10])
{
	list<int> moveList;
	int bestMove;		//Just for debug within this function.
	int val = _MIN;
	int minMoveVal;

	createMoveList(board, moveList);

	while(!moveList.empty()){
		player1.myTurn = false;
		player2.myTurn = true;
		board[moveList.front()] = 2;
		checkState();
		if(state == OWIN){
			state = PLAYING;
			bestMove = moveList.front();
			board[moveList.front()] = 0;
			return _MAX;	//Best for computer player, so maximum number can make sure this move is included.
		}
		else if(state == DRAW){
			state = PLAYING;
			bestMove = moveList.front();
			board[moveList.front()] = 0;
			return 0;
		}
		else{
			minMoveVal = minMove(board);
			if(minMoveVal >= val){
				val = minMoveVal;
				bestMove = moveList.front();
			}
		}

		board[moveList.front()] = 0;
		moveList.pop_front();
	}
	return val;
}

bool TicTacToe::play()
{
	char	playAgain;
	char	moveFirst;
	int		pos;
	int		humanInput = 0;	//1 - human input is valid. 2 - machine input is valid
	int		bestMove;

	init();
	cout << endl;
	cout << "*****************************" << endl;
	cout << "*  TicTacToe game begins!!! *" << endl;
	cout << "*****************************" << endl;
	cout << endl;

	showBoard();

	cout << "You first or computer first?" << endl;
	cout << "I(i) - Human first, Others - Computer first." << endl;
	cout << "Your selection:";
	cin >> moveFirst;
	cout << "First player uses 'X'." << endl;
	if(moveFirst == 'I' or moveFirst == 'i'){
		player1.myTurn = true;
		player2.myTurn = false;
	}
	else{
		player1.myTurn = false;
		player2.myTurn = true;
	}

	state = PLAYING;

	while(state != OWIN && state != XWIN && state != DRAW){

		if(player1.myTurn == true){
			while(humanInput ==0){
				cout << endl << "Please enter the position (1 ~ 9):";
				cin >> pos;

				if(board[pos] == 0 && (pos >= 1 && pos <= 9)){
					board[pos] = 1;
					humanInput = 1;
				}
				else{
					cout << "Invalid position." << endl;
				}
			}

			cout << "After your move:" << endl;
			showBoard();

			humanInput = 0;
			checkState();
			player1.myTurn = false;
			player2.myTurn = true;
		}
		else{
			bestMove = minimax();	//When human moves first, computer use minimax() to get the next position.

			board[bestMove] = 2;
			cout << "After computer move:" << endl;
			showBoard();

			checkState();
			player2.myTurn = false;
			player1.myTurn = true;
		}
	}

	if(state == XWIN)
		cout << "Congratulations! You win!" << endl << endl;
	else if(state == OWIN)
		cout << "Sorry! Computer Win!" << endl;
	else if(state == DRAW)
		cout << "Draw!" << endl;

	cout << "Do you want to play again?" << endl << "Y - Yes, Others - No" << endl;
	cin >> playAgain;

	if(playAgain == 'Y' or playAgain == 'y')
		return true;
	else
		return false;
}

void TicTacToe::init()
{
	player1.symbol = 'X';
	player2.symbol = 'O';

	for(int i=0; i<=9; i++){
		board[i] = 0;
	}
}

void TicTacToe::showBoard()
{
	cout << "-------------" << endl;
	for(int i=1; i<=9; i++){
		switch(board[i]){
		case 0:
			cout << "| " << " " << " ";
			break;
		case 1:
			cout << "| " << "X" << " ";
			break;
		case 2:
			cout << "| " << "O" << " ";
			break;
		default:
			break;
		}

		if(i==3 || i==6 || i==9){
			cout << "|" << endl;
			cout << "-------------" << endl;
		}
	}
}
int main() {
	TicTacToe game;
	while(game.play());
	return 0;
}
