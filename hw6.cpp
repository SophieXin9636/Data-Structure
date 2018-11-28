#include <iostream>
#include "stdlib.h"
using namespace std;

class TreeNode {
	friend class BSTree;
public:
	/* Constructor */
	TreeNode(int value=0, TreeNode *l = 0, TreeNode *r = 0) :data(value), leftchild(l), rightchild(r) {}
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
		TreeNode *current = Root;
		if (!current) throw "Binary Search Tree is Empty! Cannot delete.";

		current = searchNode(deleteData);
		if (!current) return; // not found node

		/* delete leaf node that don't have child (ok)*/
		else if (current->leftchild == 0 && current->rightchild == 0) {
			delete current;
		}
		/* delete nonleaf node that has one son (not)*/
		else if (current->leftchild == 0 || current->rightchild == 0) {
			/* the tree has a left child */
			if (current->rightchild == 0) {
				TreeNode *temp = current->leftchild;
				current->data = temp->data; // move data to current node
				delete temp;
			}
			/* the tree has a right child */
			else {
				TreeNode *temp = current->rightchild;
				current->data = temp->data; // move data to current node
				delete temp;
			}
		}
		/* delete nonleaf node that has two son */
		else if (current->leftchild != 0 && current->rightchild != 0) {
			TreeNode *link = current->rightchild;
			TreeNode *temp = current;
			current = current->leftchild;
			current->rightchild = link;
			delete temp;
		}
	}

	/* Search Node in Binary Search Tree and return address of the node */
	TreeNode* searchNode(int searchData) {
		TreeNode *current = Root;
		if (!current) return 0; // no data, BST is Empty!
		while (current) {
			if (searchData > Root->data)	current = current->rightchild;
			else if (searchData < Root->data) current = current->leftchild;
			/* delete when encountering same data of Node */
			else return current;
		}
		return 0; // not found, so return nullptr
	}

	/* print Binary Search Tree (Undone) */
	void printBST() {
		TreeNode *current = Root;
		TreeNode *temp = 0;

		cout << "node: ";
		Inorder1(current);
		cout << endl;
		cout << "left: ";
		Inorder2(current);
		cout << endl;
		cout << "right: ";
		Inorder3(current);
		cout << endl;
	}

	void Inorder1(TreeNode *current) {
		if (current) {
			Inorder1(current->leftchild);
			cout << current->data << " "; // print node
			Inorder1(current->rightchild);
		}
	}

	void Inorder2(TreeNode *current) {
		if (current) {
			Inorder2(current->leftchild);
			cout << ((current->leftchild != NULL) ? current->leftchild->data : 0) << " "; // print leftchild
			Inorder2(current->rightchild);
		}
	}

	void Inorder3(TreeNode *current) {
		if (current) {
			Inorder3(current->leftchild);
			cout << ((current->rightchild != NULL)? current->rightchild->data : 0) << " "; // print rightchild
			Inorder3(current->rightchild);
		}
	}

private:
	TreeNode *Root;
};

int main() {
	int data;
	BSTree inputBST;
	while (cin >> data) {
		if (data == -1) break;
		inputBST.insertNode(data);
	}
	inputBST.printBST();
	system("pause");
	return 0;
}
