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

const char infile[] = "hashuri.in";
const char outfile[] = "hashuri.out";

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

/// parsing
const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    x = 0;
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}
/// end of parsing

struct AVL {
    AVL *left, *right;
    int key;
    int maxH;
    AVL(AVL *_left, AVL *_right, int _key) {
        left = _left;
        right = _right;
        key = _key;
        maxH = 1;
    }
} *Root, *NIL;

inline void updateHeight(AVL *& Node) {
    if(Node == NIL) {
        Node->maxH = 0;
        return;
    }
    Node->maxH = 1 + max(Node->left->maxH, Node->right->maxH);
}

inline void rotateLeft(AVL *& Node) {
    AVL * aux = Node->left;
    Node->left = aux->right;
    aux->right = Node;
    Node = aux;

    updateHeight(Node->right);
    updateHeight(Node);
}

inline void rotateRight(AVL *& Node) {
    AVL * aux = Node->right;
    Node->right = aux->left;
    aux->left = Node;
    Node = aux;

    updateHeight(Node->left);
    updateHeight(Node);
}
/**
 *  x
 *   \
 *    y
 *   /
 *  z
 *bug, does not maintain the AVL property
 */
inline void Balance(AVL *& Node) {
    if(Node->left->maxH - Node->right->maxH > 1) {
        if(Node->left->right->maxH > Node->left->left->maxH)
            rotateRight(Node);
        rotateLeft(Node);
    }
    else if(Node->right->maxH - Node->left->maxH > 1) {
        if(Node->right->left->maxH > Node->right->right->maxH)
            rotateLeft(Node);
        rotateRight(Node);
    }
}

inline void Insert(AVL *& Node, int key) {
    if(Node == NIL) {
        Node = new AVL(NIL, NIL, key);
        return;
    }
    if(key == Node->key)
        return;
    else if(key < Node->key)
        Insert(Node->left, key);
    else Insert(Node->right, key);
    updateHeight(Node);
    Balance(Node);
}

inline void Erase(AVL *& Node, int key) {
    if(Node == NIL)
        return;
    if(Node->key == key) {
        if(Node->left == NIL || Node->right == NIL) {
            AVL * aux = (Node->left == NIL) ? Node->right: Node->left;
            delete Node;
            Node = aux;
        }
        else {
            AVL * aux;
            for(aux = Node->right ; aux->left != NIL ; aux = aux->left);
            Node->key = aux->key;
            Erase(Node->right, aux->key);
        }
    }
    else if(key < Node->key)
        Erase(Node->left, key);
    else Erase(Node->right, key);
    updateHeight(Node);
    Balance(Node);
}

inline bool Find(AVL *& Node, int key) {
    if(Node == NIL)
        return false;
    if(Node->key == key)
        return true;
    if(key < Node->key)
        return Find(Node->left, key);
    else return Find(Node->right, key);
}

int main() {
    freopen(infile, "r", stdin);

    NIL = new AVL(NULL, NULL, 0);
    NIL->maxH = 0;
    NIL->left = NIL->right = NIL;
    Root = NIL;
    int M;
    getInt(M);
    for(int q = 1 ; q <= M ; ++ q) {
        int op, x, y;
        getInt(op);
        getInt(x);
        switch(op) {
            case 1:
                Insert(Root, x);
                break;
            case 2:
                Erase(Root, x);
                break;
            case 3:
                fout << Find(Root, x) << '\n';
                break;
        }
    }
    fout.close();
    return 0;
}
