#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <map>

using namespace std;

const int maxi = 50005;

int n;

struct treap {
	treap *left, *right;
	string label;
	int pri;
	treap() {
		
	}
	treap(treap *_left, treap *_right, string _label, int _pri) {
		left = _left;
		right = _right;
		label = _label;
		pri = _pri;
	}
} *root, *nil;

inline void rotateleft(treap *& node) {
	treap *aux = node->left;
	node->left = aux->right;
	aux->right = node;
	node = aux;
}

inline void rotateright(treap *& node) {
	treap *aux = node->right;
	node->right = aux->left;
	aux->left = node;
	node = aux;
}

inline void balance(treap *& node) {
	if(node->left->pri > node->pri)
		rotateleft(node);
	if(node->right->pri > node->pri)
		rotateright(node);
}

inline void insert(treap *& node, string label, int pri) {
	if(node == nil) {
		node = new treap(nil, nil, label, pri);
		return;
	}
	if(label < node->label)
		insert(node->left, label, pri);
	else
		insert(node->right, label, pri);
	balance(node);
}

inline void print(treap *& node) {
	if(node == nil)
		return ;
	cout << "(";
	if(node->left != nil) {
		print(node->left);
	}
	cout << node->label << '/' << node->pri;
	if(node->right != nil) {
		print(node->right);
	}
	cout << ")";
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1675.in", "r", stdin);
	freopen("uri1675.out", "w", stdout);
	#endif
	while(cin >> n) {
		if(n == 0)
			return 0;
		nil = new treap(0, 0, "ZZZZZZZZZ", 0);
		nil->left = nil->right = nil;
		root = nil;
		
		for(int i = 0 ; i < n ; ++ i) {
			string s, label = "";
			int prio = 0;
			bool slash = false;
			cin >> s;
			for(int i = 0 ; i < s.size() ; ++ i) {
				if(s[i] == '/') {
					slash = true;
					continue;
				}
				if(slash)
					prio = prio * 10 + s[i] - '0';
				else
					label += s[i];
			}
			insert(root, label, prio);
		}
		print(root);
		cout << '\n';
	}
}
