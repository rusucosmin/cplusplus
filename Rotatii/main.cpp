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

const char infile[] = "rotatii.in";
const char outfile[] = "rotatii.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

// parsing
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
    if(sign == '-')
        x = -x;
}
// end of parsing

struct Treap {
    Treap *left, *right;
    int key, size, priority;
    long long sum, minsum;
    Treap(Treap *_left, Treap *_right, int _key, int _priority, int _size = 1) {
        left = _left;
        right = _right;
        key = _key;
        priority = _priority;
        size = _size;
    }
} *Root, *NIL;

int M, N;

inline void update(Treap *& Node) {
    Node->size = 1 + Node->left->size + Node->right->size;
    Node->sum = Node->left->sum + Node->right->sum + Node->key;
    Node->minsum = Node->left->minsum;
    if(Node->left->sum + Node->key < Node->minsum)
        Node->minsum = Node->left->sum + Node->key;
    if(Node->left->sum + Node->key + Node->right->minsum < Node->minsum)
        Node->minsum = Node->left->sum + Node->key + Node->right->minsum;
}

inline void rotateLeft(Treap *& Node) {
    Treap *aux = Node->left;
    Node->left = aux->right;
    aux->right = Node;

    Node = aux;
    update(Node->right);
    update(Node);
}

inline void rotateRight(Treap *& Node) {
    Treap * aux = Node->right;
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
    if(pos <= Node->left->size + 1)
        Insert(Node->left, key, pos, priority);
    else
        Insert(Node->right, key, pos - 1 - Node->left->size, priority);
    balance(Node);
    update(Node);
}

inline void Erase(Treap *& Node, int pos) {
    if(Node == NIL)
        return;
    if(Node->left->size + 1 == pos) {
        if(Node->right == NIL && Node->left == NIL) {
            delete Node;
            Node = NIL;
            return;
        } else {
            if(Node->left->priority > Node->right->priority) {
                rotateLeft(Node);
                Erase(Node->right, pos - 1 - Node->left->size);
            }
            else {
                rotateRight(Node);
                Erase(Node->left, pos);
            }
        }
    } else if(Node->left->size + 1 >= pos)
        Erase(Node->left, pos);
    else Erase(Node->right, pos - 1 - Node->left->size);
    update(Node);
}

inline int Query(Treap *& Node) {
    if(Node == NIL)
        return 0;
    else if(Node->left->sum + Node->key == Node->minsum)
        return Node->left->size + 1;
    else if(Node->left->minsum == Node->minsum)
        return Query(Node->left);
    else if(Node->left->sum + Node->key + Node->right->minsum == Node->minsum)
        return Node->left->size + 1 + Query(Node->right);
    //else assert(false);
}

inline void printTree(Treap *& Node) {
    if(Node == NIL)
        return;
    printTree(Node->left);
    fout << Node->key << ' ';
    printTree(Node->right);
}

int main() {
    freopen(infile, "r", stdin);
    srand(time(NULL));
    NIL = new Treap(0, 0, 0, -1, 0);
    NIL->minsum = 0;
    NIL->sum = 0;
    NIL->left = NIL->right = NIL;
    Root = NIL;
    getInt(N);
    getInt(M);
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        getInt(x);
        Insert(Root, x, i, rand() % oo + 1);
    }
    //#define debug
    #ifdef debug
    fout << "Print tree : ";
    printTree(Root);
    fout << '\n';
    #endif
    for(int q = 1 ; q <= M ; ++ q) {
        int op, x, y;
        getInt(op);
        if(op == 0) {
            getInt(x);
            getInt(y);
            Insert(Root, y, x + 1, rand() + 1);
        } else if(op == 1) {
            getInt(x);
            Erase(Root, x);
        } else {
            if(Root->sum < 0)
                fout << "-1\n";
            else fout << Query(Root) % Root->size << '\n';
        }
        #ifdef debug
        fout << q << ' ' << "Print tree : ";
        printTree(Root);
        fout << '\n';
        #endif
    }
    fin.close();
    fout.close();
    return 0;
}
