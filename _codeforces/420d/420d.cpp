#include <iostream>
#include <bitset>
#include <vector>
#include <string.h>
#include <set>
#include <time.h>
#include <unordered_map>
#include <stdlib.h>

using namespace std;

const int maxn = 1000005;

struct treap {
	treap *left, *right;
	int k, p, s;
	treap(treap *_left, treap *_right, int _k, int _p) {
		left = _left;
		right = _right;
		k = _k;
		p = _p;
	}
} *nil, *root;

int n, m;

inline void updatesubtree(treap *&node) {
	if(node == nil) {
		node->s = 0;
		return ;
	}
	node->s = 1 + node->left->s + node->right->s;	
}

inline void rotateleft(treap *&node) {
	treap *aux = node->left;
	node->left = aux->right;
	aux->right = node;

	updatesubtree(aux);
	updatesubtree(node);
	
	node = aux;
}

inline void rotateright(treap *&node) {
	treap *aux = node->right;
	node->right = aux->left;
	aux->left = node;

	updatesubtree(aux);
	updatesubtree(node);

	node = aux;
}

inline void balance(treap *& node) {
	if(node->left->p > node->p)
		rotateleft(node);
	if(node->right->p > node->p)
		rotateright(node);
	updatesubtree(node);
}

inline void insert(treap *&node, int pos, int key, int pri) {
	if(node == nil) {
		node = new treap(nil, nil, key, pri);
		updatesubtree(node);
		return ;
	}
	if(pos <= 1 + node->left->s)
		insert(node->left, pos, key, pri);
	else
		insert(node->right, pos - node->left->s - 1, key, pri);
	updatesubtree(node);
	balance(node);
	updatesubtree(node);
}

inline int erase(treap *& node, int pos) {
	if(pos == 1 + node->left->s) {
		if(node->left == nil && node->right == nil) {
			int ret = node->k;
			delete node;
			node = nil;
			return ret;
		}
		if(node->left->p > node->right->p) {
			rotateleft(node);
			int aux = erase(node->right, pos - 1 - node->left->s);
			updatesubtree(node);
			return aux;
		}
		else {
			rotateright(node);
			int aux = erase(node->left, pos);
			updatesubtree(node);
			return aux;
		}
	}
	if(pos <= 1 + node->left->s) {
		int aux = erase(node->left, pos);		
		updatesubtree(node);
		return aux;
	}
	else {
		int aux = erase(node->right, pos - 1 - node->left->s);
		updatesubtree(node);
		return aux;
	}
}

inline void print(treap *node) {
	if(node == nil)
		return;
	print(node->left);
	cout << node->k << ' ' << node->s << ' ' << node->left->k << ' ' << node->right->k << '\n';
	print(node->right);
}

unordered_map<int, int> mark;
bitset <maxn> have;

inline int getrand() {
	int ret = rand() * rand();
	if(ret < 0)
		ret = -ret;
	if(ret == 0)
		return 1;
	return ret;
}

int main() {
	nil = new treap(0, 0, 0, 0);
	nil->left = nil->right = nil;
	nil->s = 0;
	root = nil;
	srand(time(NULL));

	cin.sync_with_stdio(false);

	cin >> n >> m;

	for(int i = 1 ; i <= n ; ++ i)
		insert(root, i, i, getrand());
	
	bool fake = false;


	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		int which = erase(root,  y);
		insert(root, 1, which, getrand());
		if(!mark[which] || mark[which] == x)
			mark[which] = x;
		else
			fake = true;
	}

	set<int> s;
	
	for(int i = 1 ; i <= n ; ++ i) {
		if(mark[i] == 0)
			continue;
		if(have[mark[i]])
			fake = true;
		have[mark[i]] = 1;
	}

	for(int i = 1 ; i <= n ; ++ i)
		if(!have[i])
			s.insert(i);
	
	if(fake) {
		cout << "-1\n";
		return 0;
	}

	for(int i = 1 ; i <= n ; ++ i) {
		if(!mark[i]) {
			cout <<  *s.begin() << ' ';
			s.erase(s.begin());
			continue;
		}
		cout << mark[i] << ' ';	
	}
}
