/*	Author : Sophie Chen
	Date : Sep.11, 2018
	Purpose : Assignment 1.1 : magic_square	*/

#include <iostream>
#include <iomanip> // setw function
using namespace std;

int print_magic_square(int N);

int print_magic_square(int N){
	int counter;

	// print size of magic square
	cout << N << endl;

	if(N==1){
		cout << " " << setw(2) << N << endl;
		return 0;
	}

	/* Declare array for magic square */
	int magic_square[N][N]; // means not put data

	int i, j; // index of array of magic square


	for(counter=1, i=0, j=N/2; counter <= N*N; counter++){
		// put data
		magic_square[i][j] = counter;

		// encounter that had put data
		if(counter % N == 0)	i += 1;
		// index that put data
		else{
			i-=1;
			j-=1;
		}
		// out of array of magic square range
		// to modify index
		if(i == -1)	i = N-1;
		if(j == -1)	j = N-1;
		if(i == N)	i = 0;
		if(j == N)	j = 0;
	}

	// print the magic square
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cout << " " << setw(2) << magic_square[i][j];
		}
		cout << endl;
	}
	cout << endl;
	return 0;

}

int main(void) {
	int N; // size of magic square

	for(N=1; N<=9; N+=2){
		print_magic_square(N);
	}
	return 0;
}
