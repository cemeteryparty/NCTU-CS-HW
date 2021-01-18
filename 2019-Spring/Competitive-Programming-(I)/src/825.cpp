#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/825/
struct Node { 
	int count; 
	Node *left, *right; // right, left: 1, 0 
};
Node *newNode() { 
	Node *node = (Node*)malloc(sizeof(Node)); 
	node->count = 0; 
	node->left = node->right = NULL; 
	return (node); 
} 
int main(int argc, char const *argv[]) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	Node *root = newNode();
	int n = 0, q = 0;
	std::cin >> n;
	while (n--) {
		std::string s;
		std::cin >> s;
		Node *node = root;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] - 48) {
				if (!node->right) {
					Node *newnode = newNode();
					node->right = newnode;
				}			
				node = node->right;
				node->count++;		
			}
			else {
				if (!node->left) {
					Node *newnode = newNode();
					node->left = newnode;
				}			
				node = node->left;
				node->count++;
			}
		}
	}
	std::cin >> q;
	while (q--) {
		std::string s;
		std::cin >> s;
		Node *node = root;
		for (int i = 0; i < s.length(); i++){
			if (s[i] - 48) { node = node->right; }
			else { node = node->left; }
			if (node == NULL) { break; }
		}
		if (node) { std::cout << node->count << '\n'; }
		else { std::cout << "0\n"; }
	}
	return 0;
}
