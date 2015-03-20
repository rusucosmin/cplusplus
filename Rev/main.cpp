#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "rev.in";
const char outfile[] = "rev.out";

ofstream fout(outfile);

const int MAXN = 100005;
const int oo = (1 << 30);

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

struct Treap {
    Treap *left, *right;
    int key, priority, subtree;
    bool rev;
    Treap(Treap *_left, Treap *_right, int _key, int _priority, int _subtree = 1) {
        left = _left;
        right = _right;
        key = _key;
        priority = _priority;
        subtree = _subtree;
        rev = false;
    }
};

Treap *Root, *NIL;
int N, M;

inline void lazyRev(Treap *&Node) {
    if(Node->rev) {
        swap(Node->left, Node->right);
        Node->rev = 0;
        Node->left->rev ^= 1;
        Node->right->rev ^= 1;
    }
}

inline void updateSubTree(Treap *&Node) {
    Node->subtree = Node->left->subtree + Node->right->subtree + 1;
}

inline void rotateLeft(Treap *&Node) {
    lazyRev(Node);
    lazyRev(Node->left);
    lazyRev(Node->right);

    Treap *aux = Node->left;
    Node->left = aux->right;
    aux->right = Node;

    updateSubTree(aux);
    updateSubTree(Node);

    Node = aux;
}

inline void rotateRight(Treap *&Node) {
    lazyRev(Node);
    lazyRev(Node->left);
    lazyRev(Node->right);

    Treap *aux = Node->right;
    Node->right = aux->left;
    aux->left = Node;


    updateSubTree(aux);
    updateSubTree(Node);

    Node = aux;
}

inline void Balance(Treap *&Node) {
    if(Node->priority < Node->left->priority)
        rotateLeft(Node);
    if(Node->priority < Node->right->priority)
        rotateRight(Node);
    updateSubTree(Node);
}

void Insert(Treap *& Node, int pos, int key, int priority) {
    if(Node == NIL) {
        Node = new Treap(NIL, NIL, key, priority);
        Node->subtree = 1;
        return;
    }
    lazyRev(Node);
    if(pos <= 1 + Node->left->subtree)
        Insert(Node->left, pos, key, priority);
        else Insert(Node->right, pos - 1 - Node->left->subtree, key, priority);
    Balance(Node);
}

void Erase(Treap *& Node, int pos) {
    lazyRev(Node);
    if(Node->left->subtree >= pos)
        Erase(Node->left, pos);
    else if(1 + Node->left->subtree < pos)
        Erase(Node->right, pos - 1 - Node->left->subtree);
    else {
        if(Node->left == NIL && Node->right == NIL) {
            delete Node;
            Node = NIL;
            return;
        }
        if(Node->left->priority > Node->right->priority) {
            rotateLeft(Node);
            Erase(Node->right, pos - Node->left->subtree - 1);
        }
        else {
            rotateRight(Node);
            Erase(Node->left, pos);
        }
    }
    updateSubTree(Node);
}

inline void ShowTree(Treap *&Node) {
    if(Node == NIL) {
        return;
    }
    cerr << Node->key << ' ' << Node->left->key << ' ' << Node->right->key << "\n";
    ShowTree(Node->left);
    ShowTree(Node->right);
}

inline void Split(Treap *&Node, Treap *&T1, Treap *&T2, int pos) {
    Insert(Node, pos, 0, oo);
    T1 = Node->left;
    T2 = Node->right;
    delete Node;
    Node = NIL;
}

inline void Join(Treap *&Node, Treap *&T1, Treap *&T2) {
    Node = new Treap(T1, T2, 0, oo);
    updateSubTree(Node);
    Erase(Node, Node->left->subtree + 1); /// erase the root
}

inline void reverseSeq(int i, int j) {
    Treap *T1, *T2, *T3, *aux;
    Split(Root, aux, T3, j + 1);
    Split(aux, T1, T2, i);
    T2->rev = true;
    Join(aux, T1, T2);
    Join(Root, aux, T3);
}

inline int getKthElement(Treap *&Node, int k) {
    lazyRev(Node);
    if(Node->left->subtree + 1 == k)
        return Node->key;
    if(k <= Node->left->subtree)
        return getKthElement(Node->left, k);
        else return getKthElement(Node->right, k - Node->left->subtree - 1);
}

int main() {
    freopen(infile, "r", stdin);

    Root = NIL = new Treap(0, 0, 0, 0, 0);
    NIL->left = NIL->right = NIL;
    srand(time(NULL));

    getInt(N);
    getInt(M);

    for(int i = 1 ; i <= N ; ++ i)
        Insert(Root, i, i, rand() % oo + 1);

    for(int x = 1 ; x <= M ; ++ x) {
        int i, j, k;
        getInt(i);
        getInt(j);
        getInt(k);
        reverseSeq(i, j);
        fout << getKthElement(Root, k) << '\n';
    }
    fout.close();
    return 0;
}
