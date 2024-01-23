#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

struct Node {
	int key;
	struct Node* left;
	struct Node* right;
};

Node* createNode(int key) {
	Node* node = new Node;
	node->key = key;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

int find(vector<int> inorder, int start, int end, int key) {
	for (int i = start; i <= end; i++) {
		if (inorder.at(i) == key) {
			return i;
		}
	}
	return -1;
}

Node* createTree(vector<int> inorder, vector<int> levelorder, int start, int end, int size) {
	if (start > end) {
		return nullptr;
	}
	
	Node* root = createNode(levelorder.at(0));
	
	if (start == end) {
		return root;
	}

	int index = find(inorder, start, end, root->key);
	
	vector<int> leftBit;
	vector<int> rightBit;

	for (int i = 0; i < levelorder.size(); i++) {
		for (int j = start; j < index; j++) {
			if (levelorder.at(i) == inorder.at(j)) {
				leftBit.push_back(levelorder.at(i));
			}
		}
	}

	for (int i = 0; i < levelorder.size(); i++) {
		for (int j = index + 1; j <= end; j++) {
			if (levelorder.at(i) == inorder.at(j)) {
				rightBit.push_back(levelorder.at(i));
			}
		}
	}
	
	root->left = createTree(inorder, leftBit, start, index - 1, index - start);
	root->right = createTree(inorder, rightBit, index + 1, end, end - index);
	return root;
}

int main(int argc, char* argv[]) {

	ifstream inFS1;
	ifstream inFS2;

	inFS1.open(argv[1]);
	inFS2.open(argv[2]);

	vector<int> invect;
	vector<int> levelvect;
	int temp;

	while (!inFS1.eof()) {
		inFS1 >> temp;
		invect.push_back(temp);
		temp = 0;
	}
	invect.pop_back();
	while (!inFS2.eof()) {
		inFS2 >> temp;
		levelvect.push_back(temp);
		temp = 0;
	}
	levelvect.pop_back();

	int size = invect.size();

	Node* huffmanRoot = createTree(invect, levelvect, 0, size - 1, size);

	ifstream inFS3;
	inFS3.open(argv[3]);
	char traverse;
	vector<char> traversal;
	Node* current = huffmanRoot;

	while (inFS3 >> traverse) {
		traversal.push_back(traverse);
	}

	for (int i = 0; i < traversal.size(); i++) {
		if (traversal.at(i) == '0') {
			if (current->left == nullptr) {
				cout << char(current->key);
				current = huffmanRoot;
			}
			current = current->left;
		}
		else if (traversal.at(i) == '1') {
			if (current->right == nullptr) {
				cout << char(current->key);
				current = huffmanRoot;
			}
			current = current->right;
		}
	}
	cout << char(current->key);

	inFS1.close();
	inFS2.close();
	inFS3.close();

	return 0;
}