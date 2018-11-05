#include "pegs.h"
#include <cstdio>
#include <iostream>
#include <vector>

Pegs::Pegs(){
	boardSize = 7;
	pegBoard.resize(7);
	vector<char> inners(boardSize);
	for(int i = 0 ; i < boardSize; ++i){
		pegBoard[i] = inners;
	}
	
	for(int i = 0 ; i < boardSize; ++i){
		for(int j = 0 ; j< boardSize; ++j){
			if( (i <= 1 &&  j <= 1  )  || (i >= 5 && j >= 5) || (i <= 1 && j >= 5) || (i >= 5 && j <= 1 )      ){ // change for a different sized board
				pegBoard[i][j] = ' ';
			}
			else{
				pegBoard[i][j] = '*'; // true means there is a piece there
			}
		}
	}
	pegBoard[3][3] = '-'; // make center an empty place too
}

Pegs::Pegs(Pegs& p1,vector< vector<char> > b1){
	this->boardSize = p1.boardSize;
	this->pegBoard = b1;	
}

void Pegs::printBoard(){
	cout << "Current Board"<<endl;
	cout << endl;
	for(int i = 0 ; i < boardSize; ++i){
		for(int j = 0 ; j< boardSize; ++j){
			cout << pegBoard[i][j] << "  ";
		}
		cout << endl;
	}

}

bool Pegs::goalState(){
	for ( int x = 0 ; x < boardSize ;++x){
		for ( int y = 0 ; y < boardSize ;++y){
			if(canBottom(x,y) || canLeft(x,y) || canUp(x,y) || canRight(x,y)) return false; // means there is still a valid move there.
		}
	}
	return true;
}

vector< vector<char> > Pegs::moveRight(int x,int y){
	vector< vector<char> > tempBoard = pegBoard;
	tempBoard[x][y] = '-';
	tempBoard[x][y+1] = '-';
	tempBoard[x][y+2] = '*';
	return tempBoard;

}

vector< vector<char> > Pegs::moveUp(int x,int y){
	vector< vector<char> > tempBoard = pegBoard;
	
	tempBoard[x][y] = '-';
	tempBoard[x-1][y] = '-';
	tempBoard[x-2][y] = '*';
	return tempBoard;
	
}

vector< vector<char> > Pegs::moveLeft(int x,int y){
	vector< vector<char> > tempBoard = pegBoard;
	tempBoard[x][y] = '-';
	tempBoard[x][y-1] = '-';
	tempBoard[x][y-2] = '*';
	return tempBoard;
	
}

vector< vector<char> > Pegs::moveBottom(int x,int y){

		vector< vector<char> > tempBoard = pegBoard;
		tempBoard[x][y] = '-';
		tempBoard[x+1][y] = '-';
		tempBoard[x+2][y] = '*';
		return tempBoard;
	
}

int Pegs::moveCounter(){
	int count = 0;
	for(int x = 0 ; x < boardSize; ++x){
		for(int y = 0 ; y < boardSize; ++y){		
			if (canBottom(x,y)) ++count;
			if (canUp(x,y)) ++count;
			if (canLeft(x,y)) ++count;
			if (canRight(x,y)) ++count;
		}
	}
	return count;
}

bool Pegs::canBottom(int x, int y){
		return (((x<5) &&(pegBoard[x][y] == '*') && (pegBoard[x+1][y] == '*') && (pegBoard[x+2][y] == '-')));
}

bool Pegs::canUp(int x, int y){
	return (((x>1) && (pegBoard[x][y] == '*') && (pegBoard[x-1][y] == '*') && (pegBoard[x-2][y] == '-')));
}

bool Pegs::canRight(int x, int y){
	return (((y<5) && (pegBoard[x][y] == '*') && (pegBoard[x][y+1] == '*') && (pegBoard[x][y+2] == '-')));
}

bool Pegs::canLeft(int x, int y){
	return (((y>1) && (pegBoard[x][y] == '*') && (pegBoard[x][y-1] == '*') && (pegBoard[x][y-2] == '-')));
}

int Pegs::leftOverPegs() {
	int pegLeft = 0;
	for (int x = 0; x < boardSize; ++x) {
		for (int y = 0; y < boardSize; ++y) {
			if (pegBoard[x][y] == '*') ++pegLeft;
		}
	}
	return pegLeft;
}

double Pegs::manhattan() { // manhattan distance of each piece among them
	int dist=0;
	
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			if (pegBoard[i][j] == '*') {
				for (int x = 0; x < boardSize; ++x) {
					for (int y = 0; y < boardSize; ++y) {
						if (pegBoard[x][y] == '*') {
							dist += abs(x - i) + abs(y - j);
						}
					}
				}
			}
		}
	}
	return dist / leftOverPegs();
}

int Pegs::distanceFromCenter() {
	int dist=0;
	for (int x = 0; x < boardSize; ++x) {
		for (int y = 0; y < boardSize; ++y) {
			if (pegBoard[x][y] == '*') {
				dist += abs(x - 3) + abs(y - 3);
			}
		}
	}
	return dist;
}

int Pegs::alonePegs() {
	int alone = 0;
	for (int x = 0; x < boardSize; ++x) {
		for (int y = 0; y < boardSize; ++y) {
			if (pegBoard[x][y] == '*') {
				if (x == 0) {
					if (pegBoard[x + 1][y] != '*' && pegBoard[x][y + 1] != '*' && pegBoard[x][y - 1] != '*') alone++;
				}
				else if (x == boardSize -1 ) {
					if (pegBoard[x - 1][y] != '*' && pegBoard[x][y + 1] != '*' && pegBoard[x][y - 1] != '*') alone++;
				}
				else if (y==0) {
					if (pegBoard[x + 1][y] != '*' && pegBoard[x - 1][y] != '*' && pegBoard[x][y + 1] != '*') alone++;
				}
				else if (y == boardSize - 1) {
					if (pegBoard[x - 1][y] != '*' && pegBoard[x + 1][y] != '*' && pegBoard[x][y - 1] != '*') alone++;
				}
				else {
					if (pegBoard[x + 1][y] != '*' && pegBoard[x][y + 1] != '*' && pegBoard[x][y - 1] != '*' && pegBoard[x  -1][y] != '*') alone++;
				}
			}
		}
	}
	return alone;
}