#include <fstream>
#include <queue>
#include <iostream>

using namespace std;

struct node {
	node *left, *right;
	int key;
	node(int _key, node *_left, node *_right) {
		key = _key;
		left = _left;
		right = _right;
	}
};

inline void insert(node *& n, int key) {
	if(!n)
		n = new node(key, 0, 0);
	else {
		if(n->key > key)
			insert(n->left, key);
		else
			insert(n->right, key);
	}
}

node *root;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1466.in", "r", stdin);
	freopen("uri1466.out", "w", stdout);
	#endif
	int t;
	cin >> t;
	for(int tt = 1 ; tt <= t ; ++ tt) {
		int n;
		root = 0;
		cin >> n;
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			cin >> x;
			insert(root, x);
		}
		cout << "Case " << tt << ":\n";
		queue <node *> q;
		if(root)
		q.push(root);
		while(!q.empty()) {
			node *act = q.front();
			q.pop();
			cout << act->key;
			if(act->left)
				q.push(act->left);
			if(act->right)
				q.push(act->right);
			if(!q.empty())
				cout << ' ';
		}
		cout << '\n';
		cout << '\n';
	}
}
