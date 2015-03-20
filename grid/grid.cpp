/* 
	Grid with treaps;
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;


class treap {
public:
	struct node {
		int subtree;
		int priority;
		int key;
		node *left, *right;
		node(int _key, int _priority, node *__left, node *__right, int _subtree = 0) {
			priority = _priority;
			key = _key;
			left = __left;
			right = __right;
			subtree = _subtree;
		}
		void updatesubtree() {
			subtree = 1 + left->subtree + right->subtree;
		}
	};
	void Insert(int where, int key) {
		insert(root, where, rand() + 1, key);	
	}
	void Erase(int where) {
		erase(root, where);	
	}
	void Traverse(ofstream &fout) {
		dfs(root, fout);
		fout << '\n';
	}
	int Access(int pos) {
		return access(root, pos);
	}
	treap() {
		nil = new node(0, 0, 0, 0);
		nil->left = nil->right = nil;
		nil->subtree = 0;
		root = nil;		
	}
private:
	node *root, *nil;
	void rotateleft(node *&x) {
		node *y = x->left;

		x->left = y->right;
		y->right = x;
		x = y;

		x->right->updatesubtree();
		x->updatesubtree();
	}
	void rotateright(node *&x) {
		node *y = x->right;

		x->right = y->left;
		y->left = x;
		x = y;

		x->left->updatesubtree();
		x->updatesubtree();
	}
	void balance(node *&x) {
		if(x->priority < x->left->priority)
			rotateleft(x);
		if(x->priority < x->right->priority)
			rotateright(x);
		x->updatesubtree();
	}
	void insert(node *&x, int where, int priority, int key) {
		if(x == nil) {
			x = new node(key, priority, nil, nil);
			x->updatesubtree();
			return;
		}
		if(where <= 1 + x->left->subtree) 
			insert(x->left, where, priority, key);
		else
			insert(x->right, where - 1 - x->left->subtree, priority, key);
		balance(x);
	}
	int access(node *&x, int where) {
		if(1 + x->left->subtree == where)
			return x->key;
		if(x->left->subtree + 1 > where)
			return access(x->left, where);
		else
			return access(x->right, where - 1 - x->left->subtree);
	}
	void dfs(node *&x, ofstream &fout) {
		if(x == nil)
			return ;
		dfs(x->left, fout);
		fout << x->key << ' ';
		dfs(x->right, fout);
	}
	void erase(node *&x, int where) {
		if(x->left->subtree + 1 == where) {
			if(x->left == nil && x->right == nil) {
				delete x;
				x = nil;
				return;
			}
			if(x->left->priority > x->right->priority) {
				rotateleft(x);
				erase(x->right, where - 1 - x->left->subtree);
			}
			else {
				rotateright(x);
				erase(x->left, where);
			}
		}
		else 
			if(x->left->subtree + 1 > where)
				erase(x->left, where);	
			else
				erase(x->right, where - 1 - x->left->subtree);
		x->updatesubtree();
	}
};

int main() {
	ifstream fin("grid.in");
	ofstream fout("grid.out");

	srand(time(NULL));
	treap t[3];
	int n, k;
	fin >> n >> k;

	for(int i = 0 ; i < 3 ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			t[i].Insert(j, i * n + j);
		}
	
	while(k --) {
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		++ y1;
		++ y2;
		int keytomove = t[x1].Access(y1);
		t[x1].Erase(y1);
		t[x2].Insert(y2, keytomove);
	}
	t[0].Traverse(fout);
	t[1].Traverse(fout);
	t[2].Traverse(fout);

}

