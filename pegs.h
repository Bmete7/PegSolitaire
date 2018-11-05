#ifndef PEGS_H
#define PEGS_H
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class Pegs{

	int lastMove;
	
	public:
		int possibleMoveCount;
		int boardSize;
		vector< vector<char> > pegBoard;
		bool goalState();
		Pegs();
		Pegs(Pegs& p1,vector< vector<char> > b1);
		void printBoard();
		vector< vector<char> > moveUp(int,int);
		vector< vector<char> > moveBottom(int,int);
		vector< vector<char> > moveLeft(int,int);
		vector< vector<char> > moveRight(int,int);
		bool canUp(int,int);
		bool canLeft(int,int);
		bool canBottom(int,int);
		bool canRight(int,int);
		int leftOverPegs();
		int moveCounter();
		double manhattan();
		int distanceFromCenter();
		int alonePegs();
};


#endif
