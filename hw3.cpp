#include <iostream>
using namespace std;

const int direction = 8; // eight direction of knight's movement
const int x_move[direction] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int y_move[direction] = {1, 2, 2, 1, -1, -2, -2, -1};

class Stack{
	public:
		Stack(int stackCapacity);
		bool IsEmpty() const;
		int Top() const;
		void Push(const int &item); // insert element
		int Pop(); // delete element
	private:
		int *stack; // array of stack
		int top; // array index of top element
		int capacity; // size of stack
};

/* implement stack to record path of knight that can go forward and backward */
Stack::Stack (int stackCapacity) : capacity(stackCapacity){
	// We need dynamically create a stack that record visted location and step no.
	stack = new int[capacity];
	top = -1;
}

inline bool Stack::IsEmpty() const{
	return (top == -1);
}

inline int Stack::Top() const{
	if(IsEmpty()) throw "Stack is empty";
	return stack[top];
}

void Stack::Push(const int &x){
	if(top == capacity - 1) throw "Stack overflows";
	stack[++top] = x;
}

int Stack::Pop(){
	if(IsEmpty()) throw "Stack is empty. Cannot delete.";
	return stack[top--];
}

int main() {
	
	for(int size=1; size<=5; size++){
		if(size == 1){
			cout << "1" << endl;
			continue;
		}
		else if(size == 2 || size == 3 || size == 4){
			cout << "no solution" << endl;
			continue;
		}
		Stack x_pos(size*size); // Create a stack that record visited x position
		Stack y_pos(size*size); // Create a stack that record visited y position
		Stack move_direction(size*size); // Create a stack that record direction
		int chessboard[size][size] = {0};
		chessboard[0][0] = 1; // starting location
		
		// the location has not been visited yet on the chessboard
		int visit[size][size] = {0}; 
		visit[0][0] = 1; // starting location
		
		// knight move until all position had visited (all element is not equal to 0)
		// method : if check_visited == size*size , then stop visiting.
		int check_visited = 1;
		int knightX = 0, knightY = 0; // array index of knight location
		int i; // counter
		while(check_visited != 18){
			// push the position (x,y) into stack
			x_pos.Push(knightX);
			y_pos.Push(knightY);
			cout << knightX <<" "<< knightY <<" ";
			
			// try 8 directions to find possible path and move
			for(i=0; i < direction; i++){
				
				// move
				knightX += x_move[i];
				knightY += y_move[i];
				
				// check whether knight can move or not
				// if knight cannot move, then knight back
				if(knightX < 0 || knightY < 0 || knightX >= size || knightY >= size){
					knightX -= x_move[i];
					knightY -= y_move[i];
				}
				// record movign information and put in stack
				else if(chessboard[knightX][knightY] != 0){
					knightX -= x_move[i];
					knightY -= y_move[i];
				}
				else{ // chessboard[knightX][knightY] == 0
					chessboard[knightX][knightY] = ++check_visited;
					move_direction.Push(i);
					break;
				}
			}
			cout << i <<" "<< check_visited-1 << endl;
		}
		
		// print result of step labels of the chessboard
		for(i=0; i<size; i++){
			for(int j=0; j<size; j++)
				cout << chessboard[i][j] << " ";
			cout << endl;
		}
	}
	return 0;
}
