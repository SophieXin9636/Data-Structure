#include <iostream>
using namespace std;

class TreeNode {
	friend class BSTree;
public:
	/* Constructor */
	TreeNode(int value = 0, TreeNode *l = 0, TreeNode *r = 0) :data(value), leftchild(l), rightchild(r){}
private:
	int data;
	TreeNode *leftchild;
	TreeNode *rightchild;
};

/* Binary Search Tree */
class BSTree {
	friend class TreeNode;
public:
	/* Default Constructor */
	BSTree() :Root(0) {}

	/* Tree operation */
	void insertNode(int insertData) {
		TreeNode *current = Root;
		if (!current) { // Root is nullptr
			TreeNode *newNode = new TreeNode(insertData);
			Root = newNode;
			return;
		}

		int check = 0;
		TreeNode *temp = 0;
		while (current) {
			temp = current;
			if (insertData > current->data) {
				current = current->rightchild;
				check = 1;
			}
			else if (insertData < current->data) {
				current = current->leftchild;
				check = 2;
			}
			/* delete when encountering same data of Node */
			else {
				deleteNode(insertData);
				return;
			}
		}
		TreeNode *newNode = new TreeNode(insertData);
		if (check == 1) temp->rightchild = newNode;
		else temp->leftchild = newNode;
	}

	/* delete Node */
	void deleteNode(int deleteData) {
		TreeNode *find = Root, *parent = 0;
		if (!find) throw "Binary Search Tree is Empty! Cannot delete.";

		/* search the deleted Node */
		bool found = false; // not found
		int pre_direction = 0; // direction of pre to find; left : 1, right : 2
		while (find) {
			if (deleteData == find->data) {
				found = true;
				break;
			}
			else {
				parent = find;
				if (deleteData > find->data) {
					find = find->rightchild;
					pre_direction = 2;
				}
				else {
					find = find->leftchild;
					pre_direction = 1;
				}
			}
		}

		int childCount = 0;
		if (find->leftchild != 0) childCount++;
		if (find->rightchild != 0) childCount++;

		if (found == false) return; // not found node

		/* decide how to delete node */
		// delete leaf node (including only root in BST) 
		if (childCount == 0) {
			/* root case */
			if (find == Root) Root = 0;
			/* not root case */
			else {
				if (pre_direction == 1) parent->leftchild = 0;
				else if (pre_direction == 2) parent->rightchild = 0;
			}
			delete find;
		}
		// delete nonleaf node that has one son 
		else if (childCount == 1) {
			/* the tree has a left child */
			if (find->rightchild == 0) {
				/* root case */
				if (find == Root) {
					TreeNode *temp = Root;
					TreeNode *right = find->rightchild;
					TreeNode *left = find->leftchild;
					if (temp->leftchild == 0) temp->rightchild = right;
					else temp->leftchild = left;
				}
				/* not root case */
				else {
					TreeNode *temp = find->leftchild;
					if (pre_direction == 1) parent->leftchild = temp;
					else if (pre_direction == 2) parent->rightchild = temp;
				}
				delete find;
			}
			/* the tree has a right child */
			else {
				/* root case */
				if (find == Root) {
					TreeNode *right = find->rightchild;
					TreeNode *left = find->leftchild;
					if (find->leftchild == 0) Root = right;
					else Root = left;
				}
				/* not root case */
				else {
					TreeNode *temp = find->rightchild;
					if (pre_direction == 1) parent->leftchild = temp;
					else if (pre_direction == 2) parent->rightchild = temp;
				}
				delete find;
			}
		}
		/* delete nonleaf node that has two son */
		else if (childCount == 2) {
			TreeNode *right = find->rightchild;
			TreeNode *left = find->leftchild;
			TreeNode *successor = find->rightchild;
			TreeNode *parent = find;

			/* delete root */
			if (find == Root) {
				while (successor->leftchild) {
					parent = successor;
					successor = successor->leftchild;
				}
				Root->data = successor->data;
				parent->rightchild = successor->rightchild;
				delete successor;
			}
			/* delete not root */
			else {
				while (successor->leftchild) {
					parent = successor;
					successor = successor->leftchild;
				}
				find->data = successor->data;
				if (successor->rightchild != 0) {
					parent->leftchild = successor->rightchild;
				}
				delete successor;
				parent->rightchild = 0;
			}
		}
	}

	/* print Binary Search Tree (Undone) */
	void printBST() {
		TreeNode *current = Root;
		cout << "node:  ";
		Inorder1(current);
		cout << endl;
		cout << "left:  ";
		Inorder2(current);
		cout << endl;
		cout << "right: ";
		Inorder3(current);
		cout << endl;
	}

	void Inorder1(TreeNode *current) {
		if (current) {
			Inorder1(current->leftchild);
			printf("%3d ", current->data); // print node
			Inorder1(current->rightchild);
		}
	}

	void Inorder2(TreeNode *current) {
		if (current) {
			Inorder2(current->leftchild);
			printf("%3d ", ((current->leftchild != NULL) ? current->leftchild->data : 0)); // print leftchild
			Inorder2(current->rightchild);
		}
	}

	void Inorder3(TreeNode *current) {
		if (current) {
			Inorder3(current->leftchild);
			printf("%3d ", ((current->rightchild != NULL) ? current->rightchild->data : 0)); // print rightchild
			Inorder3(current->rightchild);
		}
	}

private:
	TreeNode *Root;
};

int main() {
	int data;
	char c;
	while(true){
		if(cin.eof() == true) break;
		BSTree inputBST;
		while (cin >> data) {
			if (data == -1) break;
			inputBST.insertNode(data);
		}
		inputBST.printBST();
		cin >> c; // get '\n'
	}
	return 0;
}
