#include <cstdio>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>

#include "pegs.h"

using namespace std;

class compareMoves { // for priority queue, sort them comparing their possible moves left
	public:
		bool operator()(Pegs &a1, Pegs &a2) {
			if (a2.moveCounter() < a1.moveCounter() ) return true;
			return false;
		}
};

class compareAlone { // for priority queue, sort them comparing their lonely pegs
public:
	bool operator()(Pegs &a1, Pegs &a2) {
		if ((a2.alonePegs())< (a1.alonePegs())) return true;
		return false;
	}
};


class compareManhattan { // for priority queue, sort them comparing their manhattan distances
public:
	bool operator()(Pegs &a1, Pegs &a2) {
		if (double( a2.manhattan()) / double(a2.leftOverPegs()) < double(a1.distanceFromCenter()) / double(a1.leftOverPegs())) return true;
		return false;
	}
};

class compareCenter { // for priority queue, sort them comparing their total distances from center
public:
	bool operator()(Pegs &a1, Pegs &a2) {
		if ( double(a2.distanceFromCenter() + a2.manhattan()) / double(a2.leftOverPegs()) < double(a1.distanceFromCenter() + a1.manhattan()) / double(a1.leftOverPegs()) ) return true;
		return false;
	}
};

class compareHeu { 
public:
	bool operator()(Pegs &a1, Pegs &a2) {
		if ( a2.distanceFromCenter() * a2.leftOverPegs() < a1.distanceFromCenter() * a1.leftOverPegs() ) return true;
		return false;
	}
};


void aStar(Pegs& a) {
	clock_t start = clock();
	int maxNodesKept = 0;
	int nodesGenerated = 0;
	int nodesExpanded = 0;
	//priority_queue<Pegs, vector<Pegs>, compareMoves> pq;
	priority_queue<Pegs, vector<Pegs>, compareAlone> pq;
	//priority_queue<Pegs, vector<Pegs>, compareHeu> pq;
	pq.push(a);
	Pegs cur;
	while (!pq.empty()) {
		cur = pq.top();
		++nodesExpanded;
		pq.pop();
		cur.printBoard();
		if (cur.goalState()) {
			system("cls");
			cur.printBoard();
			cout << "Well Done" << endl;
			cout << "Well Done" << endl;
			cout << cur.leftOverPegs() << " pegs left." << endl;
			cout << "With " << maxNodesKept << " max nodes in memory" << endl;
			cout << "Total of " << nodesGenerated << "nodes created" << endl;
			cout << "Total of " << nodesExpanded << "nodes expanded" << endl;
			cout << "Time elapsed " << double((clock() - start) / double(CLOCKS_PER_SEC / 1000)) << " ms" << endl;
			while (!pq.empty()) {
				pq.pop();
			}
			return;
		}
		for (int x = 0; x < a.boardSize; ++x) {
			for (int y = 0; y < a.boardSize; ++y) {
				if (cur.canBottom(x, y)) {

					Pegs pegnew(cur, cur.moveBottom(x, y));
					pq.push(pegnew);
					++nodesGenerated;
				}
				if (cur.canLeft(x, y)) {
					Pegs pegnew(cur, cur.moveLeft(x, y));
					pq.push(pegnew);
					++nodesGenerated;
				}
				if (cur.canRight(x, y)) {
					Pegs pegnew(cur, cur.moveRight(x, y));
					pq.push(pegnew);
					++nodesGenerated;
				}
				if (cur.canUp(x, y)) {
					Pegs pegnew(cur, cur.moveUp(x, y));
					pq.push(pegnew);
					++nodesGenerated;
				}
			}
		}
		system("cls");
		maxNodesKept = max(maxNodesKept, int(pq.size()));
	}
	return;
}

void BFS(Pegs& a) {
	clock_t start = clock();
	int maxNodesKept = 0;
	int nodesGenerated = 0;
	int nodesExpanded = 0;
	queue<Pegs> q;
	q.push(a);
	Pegs cur;
	while (!q.empty()) {
		cur = q.front();
		++nodesExpanded;
		q.pop();
		if (cur.goalState()) {
			while (!q.empty()) {
				q.pop();
			}
			cur.printBoard();
			cout << "Well Done" << endl;
			cout << "Well Done" << endl;
			cout << cur.leftOverPegs() << " pegs left." << endl;
			cout << "With " << maxNodesKept << " max nodes in memory" << endl;
			cout << "Total of " << nodesGenerated << "nodes created" << endl;
			cout << "Total of " << nodesExpanded << "nodes expanded" << endl;
			cout << "Time elapsed " << double((clock() - start) / double(CLOCKS_PER_SEC / 1000)) << " ms" << endl;
			return;
		}
		for (int x = 0; x < a.boardSize; ++x) {
			for (int y = 0; y < a.boardSize; ++y) {
				if (cur.canBottom(x, y)) {
					
					Pegs pegnew(cur, cur.moveBottom(x, y));
					q.push(pegnew);
					++nodesGenerated;
				}
				if (cur.canLeft(x, y)) {
					Pegs pegnew(cur, cur.moveLeft(x, y));
					q.push(pegnew);
					++nodesGenerated;
				}
				if (cur.canRight(x, y)) {
					Pegs pegnew(cur, cur.moveRight(x, y));
					q.push(pegnew);
					++nodesGenerated;
				}
				if (cur.canUp(x, y)) {
					Pegs pegnew(cur, cur.moveUp(x, y));
					q.push(pegnew);
					++nodesGenerated;
				}
			}
		}
		maxNodesKept = max(maxNodesKept, int(q.size()));
	}
	return;
}

void DFS(Pegs& a){
	clock_t start = clock();
	int maxNodesKept = 0;
	int nodesGenerated = 0;
	int nodesExpanded = 0;
	stack<Pegs> st;
	
	st.push(a);
	Pegs cur;
	while(!st.empty()){
		cur = st.top();
		++nodesExpanded;
		cur.printBoard();

		st.pop();
		if(cur.goalState()){
			while(!st.empty()){
				st.pop();
			}
			cur.printBoard();
			cout << "Well Done" <<endl;
			cout << "Well Done" << endl;
			cout << cur.leftOverPegs() << " pegs left." << endl;
			cout << "With " << maxNodesKept << " max nodes in memory" << endl;
			cout << "Total of " << nodesGenerated << "nodes created" << endl;
			cout << "Total of " << nodesExpanded << "nodes expanded" << endl;
			cout << "Time elapsed " << double((clock() - start) / double(CLOCKS_PER_SEC / 1000)) << " ms" << endl;
			return;
		}
		for(int x = 0; x < a.boardSize;++x){
			for(int y = 0; y < a.boardSize;++y){
				if(cur.canBottom(x,y)){

					Pegs pegnew(cur,cur.moveBottom(x,y));
					st.push(pegnew);
					++nodesGenerated;
				}
				if(cur.canLeft(x,y)){
					Pegs pegnew(cur,cur.moveLeft(x,y));
					st.push(pegnew);
					++nodesGenerated;
				}
				if(cur.canRight(x,y)){
					Pegs pegnew(cur,cur.moveRight(x,y));
					st.push(pegnew);
					++nodesGenerated;
				}
				if(cur.canUp(x,y)){
					Pegs pegnew(cur,cur.moveUp(x,y));
					st.push(pegnew);
					++nodesGenerated;
				}
			}
		}
//		cur.printBoard();
		maxNodesKept = max(maxNodesKept, int(st.size()));
	}
	return;

}

int main(){
	Pegs a;
	DFS(a);
	aStar(a);
	BFS(a);
	return 0;
}
