#include <fstream>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

const int oo = (1 << 30);

struct Treap {
    Treap *left, *right;
    int key, priority;
    int prefix, suffix, bestsum;
    int sum;
    int subtree;
    Treap(Treap *_left, Treap *_right, int _key, int _priority, int _subtree = 1) {
        left = _left;
        right = _right;
        key = _key;
        priority = _priority;
        subtree = _subtree;
    }
} *Root, *NIL;

inline void update(Treap *& Node) {
        if(Node == NIL)
            return;
		Node->subtree = 1 + Node->left->subtree + Node->right->subtree;
		Node->sum = Node->key + Node->left->sum + Node->right->sum;
		Node->bestsum = max(max(Node->left->bestsum, Node->right->bestsum), Node->key + max(Node->right->prefix, 0) + max(Node->left->suffix, 0));
		Node->prefix = max(Node->left->prefix, Node->left->sum + Node->key + max(Node->right->prefix, 0));
		Node->suffix = max(Node->right->suffix, Node->right->sum + Node->key + max(Node->left->suffix, 0));
    }

inline void rotateLeft(Treap *& Node) {
    Treap * aux = Node->left;
    Node->left = aux->right;
    aux->right = Node;
    Node = aux;

    update(Node->right);
    update(Node);
}

inline void rotateRight(Treap *& Node) {
    Treap *aux = Node->right;
    Node->right = aux->left;
    aux->left = Node;
    Node = aux;

    update(Node->left);
    update(Node);
}

inline void balance(Treap *& Node) {
    if(Node->left->priority > Node->priority)
        rotateLeft(Node);
    if(Node->right->priority > Node->priority)
        rotateRight(Node);
}

inline void Insert(Treap *& Node, int key, int pos, int priority) {
    if(Node == NIL) {
        Node = new Treap(NIL, NIL, key, priority, 1);
        update(Node);
        return;
    }
    if(pos <= 1 + Node->left->subtree)
        Insert(Node->left, key, pos, priority);
    else Insert(Node->right, key, pos - 1 - Node->left->subtree, priority);
    balance(Node);
    update(Node);
}

inline void Replace(Treap *& Node, int key, int pos) {
    if(pos == 1 + Node->left->subtree) {
        Node->key = key;
        update(Node);
        return;
    }
    if(pos <= 1 + Node->left->subtree)
        Replace(Node->left, key, pos);
    else Replace(Node->right, key, pos - 1 - Node->left->subtree);
    update(Node);
}

inline void Delete(Treap *& Node, int pos) {
    if(pos == Node->left->subtree + 1) {
        if(Node->left == NIL && Node->right == NIL) {
            delete Node;
            Node = NIL;
            return;
        }
        else {
            if(Node->right->priority > Node->left->priority) {
                rotateRight(Node);
                Delete(Node->left, pos);
            }
            else {
                rotateLeft(Node);
                Delete(Node->right, pos - 1 - Node->left->subtree);
            }
        }
    } else {
        if(pos <= 1 + Node->left->subtree)
            Delete(Node->left, pos);
        else Delete(Node->right, pos - 1 - Node->left->subtree);
    }
    update(Node);
}

inline void Split(Treap *& Node, Treap *& T1, Treap *& T2, int pos) {
    Insert(Node, -oo, pos, oo);
    T1 = Node->left;
    T2 = Node->right;
    delete Node;
}

inline void Merge(Treap *& Node, Treap *& T1, Treap *& T2) {
    Node = new Treap(T1, T2, oo, oo, T1->left->subtree + T2->right->subtree + 1);
    Delete(Node, Node->left->subtree + 1);
}

inline int Query(Treap *& Node, int x, int y) {
    Treap * A, *B, *C, *D;

    Split(Node, A, B, y + 1);
    Split(A, C, D, x);

    int ans = D->bestsum;

    Merge(A, C, D);
    Merge(Node, A, B);

    return ans;
}

char buf1[1<<22];
int pos1;

inline char nextChar(){
	while (buf1[pos1] <= ' ') ++pos1;
	return buf1[pos1++];
}

inline int nextInt() {
	while (buf1[pos1] <= ' ') ++pos1;
	bool sign = false;
	if(buf1[pos1] == '-') {
		sign = true;
		++pos1;
	}
	int res = 0;
	while (buf1[pos1] > ' ')
		res = res*10+(buf1[pos1++]&15);
	return sign ? -res : res;
}

char buf2[1<<22];
int pos2;

inline void writeInt(int x) {
	if(x<0){
		buf2[pos2++]='-';
		x=-x;
	}
	char d[10];
	int c=0;
	while(true){
		d[c++] = x%10 + '0';
		x/=10;
		if(x==0)break;
	}
	while(--c>=0)buf2[pos2++]=d[c];
}

inline void writeChar(char x) {
	buf2[pos2++]=x;
}


int main() {
    //freopen(infile, "r", stdin);

    srand(time(NULL));

    fread(buf1, 1, sizeof(buf1), stdin);

    NIL = new Treap(0, 0, 0, -1, 0);
    NIL->suffix = -oo;
    NIL->prefix = -oo;
    NIL->bestsum = -oo;
    NIL->sum = 0;
    NIL->left = NIL->right = NIL;
    Root = NIL;
    int N, M;
    //cin >> N;
    N = nextInt();
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        //cin >> x;
        x = nextInt();
        Insert(Root, x, i, rand() % oo);
    }
    //cin >> M;
    M = nextInt();
    for(int i = 1 ; i <= M ; ++ i) {
        char op;
        int x, y;
        op = nextChar();
        switch(op) {
            case 'I':
                //cin >> x >> y;
                x = nextInt();
                y = nextInt();
                Insert(Root, y, x, rand() % oo + 1);
                break;
            case 'D':
                //cin >> x;
                x = nextInt();
                Delete(Root, x);
                break;
            case 'R':
                //cin >> x >> y;
                x = nextInt();
                y = nextInt();
                Replace(Root, y, x);
                break;
            case 'Q':
                //cin >> x >> y;
                x = nextInt();
                y = nextInt();
                writeInt(Query(Root, x, y));
				writeChar('\n');
                break;
        }
    }
    fwrite(buf2, 1, pos2, stdout);
    return 0;
}
