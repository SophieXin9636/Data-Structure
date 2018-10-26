#include <iostream>
using namespace std;

/* Author：B063040059 陳縵欣
   Date：Oct. 24, 2018
   Purpose：Knight's tour problem (recursive) */
const int x_move[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int y_move[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool knight_tour(int **chess, int x, int y, const int &size, int step);

// return wheather knight can visit all path
bool knight_tour(int **chess, int x, int y, const int &size, int step){

	// all path has been traversed, stop move
	if(step == size * size)	return true;

	for(int i=0; i<8; i++){
		// knight move
		x += x_move[i];
		y += y_move[i];
		// index is int the chess_array range, so knight can move.
		if((x >= 0 && x < size) && (y >= 0 && y < size) && (chess[x][y]==0)){
			chess[x][y] = step + 1; // record the step
			// cout << x-x_move[i] <<" "<< y-y_move[i] <<" "<< i <<" "<< step+1 << endl;

			// knight go ahead
			if(knight_tour(chess, x, y, size, step+1)){
				return true;
			}
			else{
				chess[x][y] = 0;
			}
		}
		x -= x_move[i];
		y -= y_move[i];
	}
	return false; // no path can visit all position
}

int main() {
	for(int n=1; n<=6; n++){
		cout << "n = " << n <<": "<< endl;
		if(n == 1){
			cout << "1" << endl << endl;
			continue;
		}
		else if(n == 2 || n == 3 || n == 4){
			cout <<"no solution" << endl << endl;
			continue;
		}
		
		int **chessboard = new int*[n];
		for (int i=0; i<n; i++)
			chessboard[i] = new int[n];
		
		//  initialize chessboard
		for (int i=0; i<n; i++){
			for (int j=0; j<n; j++){
				chessboard[i][j] = 0;
			}
		}
		
		chessboard[0][0] = 1; // starting step
		
		if(knight_tour(chessboard, 0, 0, n, 1)){
			// print result of step labels of the chessboard
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++)
					cout << chessboard[i][j] << " ";
				cout << endl;
			}
		}
		else{
			cout <<"no solution"<< endl;
		}
		for (int i=0; i<n; i++)
			delete chessboard[i];
		delete [] chessboard;
		cout << endl;
	}
	return 0;
}
