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
#include <cassert>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 1000000009;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Treap {
    Treap *left, *right;
    int subtree, key, priority, best;
    Treap(Treap *_left, Treap *_right, int _key, int _priority, int _subtree = 1) {
        left = _left;
        right = _right;
        key = _key;
        priority = _priority;
        subtree = _subtree;
        best = _key;
    }
} *Root, *NIL;

inline void updateSubtree(Treap *& Node) {
    Node->subtree = Node->left->subtree + Node->right->subtree + 1;
    Node->best = max(Node->key, max(Node->left->best, Node->right->best));
}

inline void rotateLeft(Treap *& Node) {
    Treap *aux = Node->left;
    Node->left = aux->right;
    aux->right = Node;

    updateSubtree(aux);
    updateSubtree(Node);

    Node = aux;
}

inline void rotateRight(Treap *& Node) {
    Treap *aux = Node->right;
    Node->right = aux->left;
    aux->left = Node;

    updateSubtree(aux);
    updateSubtree(Node);

    Node = aux;
}

inline void Balance(Treap *& Node) {
    if(Node->priority < Node->left->priority)
        rotateLeft(Node);
    if(Node->priority < Node->right->priority)
        rotateRight(Node);
    updateSubtree(Node);
}

inline void Insert(Treap *& Node, int pos, int key, int priority) {
    if(Node == NIL) {
        Node = new Treap(NIL, NIL, key, priority);
        Node->subtree = 1;
        return;
    }
    if(Node->left->subtree + 1 >= pos)
        Insert(Node->left, pos, key, priority);
    else Insert(Node->right, pos - Node->left->subtree - 1, key, priority);
    Balance(Node);
}

inline int Find(Treap *& Node, int pos) {
    if(Node->left->subtree + 1 == pos)
        return Node->key;
    if(Node->left->subtree + 1 >= pos)
        return Find(Node->left, pos);
    else return Find(Node->right, pos - Node->left->subtree - 1);
}

void Erase(Treap *& Node, int pos) {
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
    updateSubtree(Node);
}

inline void Split(Treap *&Node, Treap *&T1, Treap *&T2, int pos) {
    Insert(Node, pos, -oo, oo);
    T1 = Node->left;
    T2 = Node->right;
    delete Node;
    Node = NIL;
}

inline void Join(Treap *&Node, Treap *&T1, Treap *&T2) {
    Node = new Treap(T1, T2, -oo, oo);
    if(Node == NIL) {
        delete Node;
        Node = NIL;
        return;
    }
    updateSubtree(Node);
    Erase(Node, Node->left->subtree + 1); /// erase the root
}

inline int Query(int i, int j) {
    Treap *T1, *T2, *T3, *aux;
    Split(Root, aux, T3, j + 1);
    Split(aux, T1, T2, i);
    int a = T2->best;
    Join(aux, T1, T2);
    Join(Root, aux, T3);
    return a;
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    x = 0;
    char sign = '+';
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        sign = buff[pos];
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

inline void getChar(char &op) {
    while(!(buff[pos] == 'A' || buff[pos] == 'Q')) {
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    op = buff[pos];
    if(++ pos == lim) {
        pos = 0;
        fread(buff, 1, lim, stdin);
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    srand(time(NULL));
    freopen(infile, "r", stdin);

    NIL = new Treap(0, 0, -oo, 0, 0);
    NIL->left = NIL->right = NIL;
    Root = NIL;
    int N;
    getInt(N);
    for(int i = 1 ; i <= N ; ++ i) {
        char op;
        int x, y;
        getChar(op);
        getInt(x);
        getInt(y);
        switch(op) {
            case 'A':
                Insert(Root, y, x, rand() % oo + 1);
                break;
            case 'Q':
                int ans2 = Query(x, y);
                cout << ans2 << '\n';
                break;
        }
    }
    return 0;
}
