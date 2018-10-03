/* Author: Sophie Chen
 * Date:Sep. 12, 2018
 * Purpose: hw1.2
 */
#include <iostream>
using namespace std;

int main() {
	unsigned int N; // N factorial
	unsigned int counter;
	unsigned int tens; // ten digit
	int i; // counter
	int temp_index; // temporary

	while(cin >> N){
		/* N is not in range [0,50] */
		if( (N>50) || (N<=0) ) break;

		/* N is in range [0,50] */
		// create array to put every digit
		unsigned int digit_position[70] = {0};

		/* Check every digit whether meaningful, also known as the significant digits
		 * if check == 0, then it is not significant_digits
		 * if check == 1, then it is significant_digits, and it can be printed.
		 */
		unsigned int check_significant_digits[70] = {0};
		digit_position[0] = 1; // calculate factorial

		for(counter = 1; counter <= N; counter++){
			// every element(digit) product counter
			for(i=0; i<65; i++){
				digit_position[i] *= counter;
			}
			for(i=0; i<65; i++){
				temp_index = i;
				while((digit_position[temp_index] >= 10) || (digit_position[temp_index]!=0)){
					// carry
					tens = digit_position[temp_index] / 10;
					digit_position[temp_index+1] += tens;
					digit_position[temp_index] %= 10;

					// This digit can be assigned to 1, is significant digit.
					check_significant_digits[temp_index] = 1;

					// traversal next digit
					temp_index += 1;
				}
			}

			/* print factorial value from 1! to N! */
			cout << counter << "!=";
			for(i=64; i>=0; i--){
				// check and print all significant digit
				if(check_significant_digits[i] == 1){
					cout << digit_position[i];
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}
