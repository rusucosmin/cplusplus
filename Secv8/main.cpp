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

const char infile[] = "secv8.in";
const char outfile[] = "secv8.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = (1 << 30) + 1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
bool rev;

struct Treap {
    Treap *left, *right;
    int key, priority, subTree;
    bool rev;
    Treap(Treap *_left, Treap *_right, int _key, int _priority) {
        left = _left;
        right = _right;;
        key = _key;
        priority = _priority;
    }
} *Root, *NIL;

inline void updateSubTree(Treap *&Node) {
    Node->subTree = 1 + Node->left->subTree + Node->right->subTree;
}

inline void lazyReverse(Treap *&Node) {
    if(Node->rev) {
        swap(Node->left, Node->right);
        Node->rev = 0;
        Node->left->rev ^= 1;
        Node->right->rev ^= 1;
    }
}

inline void rotateLeft(Treap *&Node) {
    lazyReverse(Node);
    lazyReverse(Node->left);
    lazyReverse(Node->right);

    Treap *aux = Node->left;
    Node->left = aux->right;
    aux->right = Node;

    updateSubTree(aux);
    updateSubTree(Node);

    Node = aux;
}

inline void rotateRight(Treap *&Node) {
    lazyReverse(Node);
    lazyReverse(Node->left);
    lazyReverse(Node->right);

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
        updateSubTree(Node);
        return;
    }
    lazyReverse(Node);
    if(pos <= 1 + Node->left->subTree)
        Insert(Node->left, pos, key, priority);
        else Insert(Node->right, pos - 1 - Node->left->subTree, key, priority);
    updateSubTree(Node);
    Balance(Node);
    updateSubTree(Node);
}

inline void Erase(Treap *&Node, int pos) {
    lazyReverse(Node);
    if(Node->left->subTree + 1 == pos) {
        if(Node->left == NIL && Node->right == NIL) {
            delete Node;
            Node = NIL;
            return;
        }
        if(Node->left->priority > Node->right->priority) {
            rotateLeft(Node);
            Erase(Node->right, pos - Node->left->subTree - 1);
        }
        else {
            rotateRight(Node);
            Erase(Node->left, pos);
        }
    }
    else {
        if(Node->left->subTree + 1 > pos)
            Erase(Node->left, pos);
        else Erase(Node->right, pos - Node->left->subTree - 1);
    }
    updateSubTree(Node);
}

inline int Access(Treap *&Node, int k) { /// guarantee it exist
    lazyReverse(Node);
    if(Node == NIL)
        return -1;
    if(Node->left->subTree + 1 == k)
        return Node->key;
    if(Node->left->subTree + 1 > k)
        return Access(Node->left, k);
    else return Access(Node->right, k - Node->left->subTree - 1);
}

inline void Split(Treap *&Node, Treap *&T1, Treap *&T2, int x) {
    Insert(Node, x, 0, oo);
    T1 = Node->left;
    T2 = Node->right;
    delete Node;
    Node = NIL;
}

inline void Join(Treap *&Node, Treap *&T1, Treap *&T2) {
    Node = new Treap(T1, T2, 0, oo);
    updateSubTree(Node);
    Erase(Node, Node->left->subTree + 1);
}

inline void reverseSeq(int i, int j) {
    Treap *A, *B, *C, *D;

    Split(Root, A, B, j + 1);
    Split(A, C, D, i);

    D -> rev ^= 1;

    Join(A, C, D);
    Join(Root, A, B);
}

inline void EraseSequence(Treap *&Node, int x, int y) {
    Treap *A, *B, *C, *D;

    Split(Node, A, B, y + 1);

    Split(A, C, D, x);

    Join(Node, C, B);
}

inline void WriteTreap(Treap *&Node) {
    if(Node == NIL)
        return;
    lazyReverse(Node);
    WriteTreap(Node->left);
    fout << Node->key << ' ';
    WriteTreap(Node->right);
}

int main() {
    srand(time(NULL));
    NIL = new Treap(0, 0, 0, 0);
    NIL -> left = NIL -> right = NIL;
    Root = NIL;

    for(fin >> N >> rev ; N -- ; ) {
        char op;
        int x, y;
        fin >> op;
        switch(op) {
            case 'I':
                fin >> x >> y;
                Insert(Root, x, y, rand() % oo + 1);
                break;
            case 'A':
                fin >> x;
                fout << Access(Root, x) << '\n';
                break;
            case 'R':
                fin >> x >> y;
                reverseSeq(x, y);
                break;
            case 'D':
                fin >> x >> y;
                EraseSequence(Root, x, y);
                break;
        }
    }
    WriteTreap(Root);

    fin.close();
    fout.close();

    return 0;
}
