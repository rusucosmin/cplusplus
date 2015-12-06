#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int maxn = 1000005;
const int mod = 666013;

int n;
vector <int> g[mod];

inline void solve_unordered_set() {
	ifstream fin("hashuri.in");
	ofstream fout("hashuri.out");
	unordered_set<int> _hash;
	fin >> n;
	while(n -- ) {
		int op, x;
		fin >> op >> x;
		if(op == 1) {
			_hash.insert(x);
		}
		if(op == 2) {
			_hash.erase(x);
		}
		if(op == 3)
			fout << (_hash.find(x) != _hash.end()) << "\n";
	}
}

inline bool find(int x) {
	for(auto it : g[x % mod])
		if(it == x)
			return 1;
	return 0;
}

inline void insert(int x) {
	if(find(x))
		return;
	g[x % mod].push_back(x);
}

inline void erase(int x) {
	if(!find(x))
		return ;
	for(vector <int> :: iterator it = g[x % mod].begin() ; it != g[x % mod].end() ; ++ it)
		if(*it == x) {
			g[x % mod].erase(it);
			return ;
		}
}

inline void solve_vector() {
	ifstream fin("hashuri.in");
	ofstream fout("hashuri.out");
	fin >> n;
	while(n -- ) {
		int op, x;
		fin >> op >> x;
		if(op == 1)
			insert(x);
		if(op == 2)
			erase(x);
		if(op == 3)
			fout << find(x) << '\n';
	}
}

struct treap {
	treap *left, *right;
	int key, priority;
	treap(treap *_left, treap *_right, int _key, int _priority) {
		left = _left;
		right = _right;
		key = _key;
		priority = _priority;
	}
	treap() {
	}
} *root, *nil;

inline void init() {
	srand(time(NULL));
	nil = new treap();
	nil->left = nil->right = nil;
	nil->key = 0;
	nil->priority = 0;
	root = nil;
}

inline void rotateleft(treap *&x) {
	treap *y = x->left;
	x->left = y->right;
	y->right = x;
	x = y;
}

inline void rotateright(treap *&x) {
	treap *y = x->right;
	x->right = y->left;
	y->left = x;
	x = y;
}

inline void balance(treap *&node) {
	if(node->left->priority > node->right->priority)
		rotateleft(node);
	else if(node->right->priority > node->left->priority)
		rotateright(node);
}

inline void insert(treap *&node, int key, int priority) {
	if(node == nil) {
		node = new treap(nil, nil, key, priority);
		return;
	}
	if(node->key > key)
		insert(node->left, key, priority);
	else
		insert(node->right, key, priority);
	balance(node);
}

inline bool find(treap *&node, int key) {
	if(node == nil)
		return 0;
	if(node->key == key)
		return 1;
	if(node->key > key)
		return find(node->left, key);
	else
		return find(node->right, key);
}

inline void erase(treap *&node, int key) {
	if(node == nil)
		return ;
	if(node->key == key) {
		if(node->left == nil && node->right == nil) {
			delete node;
			node = nil;
			return ;
		}
		if(node->left->priority > node->right->priority) {
			rotateleft(node);
			erase(node->right, key);
		}
		else {
			rotateright(node);
			erase(node->left, key);
		}
		return  ;
	}
	if(node->key > key)
		erase(node->left, key);
	else
		erase(node->right, key);
}

inline void solve_treap() {
	ifstream fin("hashuri.in");
	ofstream fout("hashuri.out");
	init();
	fin >> n;
	if(n > 200000) {
		solve_vector();
		return ;
	}
	while(n -- ) {
		int op, x;
		fin >> op >> x;
		if(op == 1)
			insert(root, x, rand() + 1);
		if(op == 2)
			erase(root, x);
		if(op == 3)
			fout << find(root, x) << '\n';
	}
}

int main() {
	//solve_unordered_set();
	//solve_vector();
	solve_treap();

}
