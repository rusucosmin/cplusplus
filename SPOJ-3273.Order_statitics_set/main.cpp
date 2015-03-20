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

const char infile[] = "input.in";
const char outfile[] = "output.out";

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

struct Treap {
    Treap *left, *right;
    int key, priority, subTree;
    Treap(Treap *_left, Treap *_right, int _key, int _priority, int _subTree = 1) {
        left = _left;
        right = _right;
        key = _key;
        priority = _priority;
        subTree = _subTree;
    }
} *Root, *NIL;

inline void updateSubTree(Treap *& Node) {
    if(Node == NIL) {
        Node->subTree = 0;
        return ;
    }
    Node->subTree = Node->left->subTree + Node->right->subTree + 1;
}

inline void rotateLeft(Treap *& Node) {
    Treap *aux = Node->left;
    Node->left = aux->right;
    aux->right = Node;

    updateSubTree(Node);
    updateSubTree(aux);

    Node = aux;
}

inline void rotateRight(Treap *& Node) {
    Treap *aux = Node->right;
    Node->right = aux->left;
    aux->left = Node;

    updateSubTree(Node);
    updateSubTree(aux);

    Node = aux;
}

inline void Balance(Treap *& Node) {
    if(Node->left->priority > Node->priority)
        rotateLeft(Node);
    if(Node->right->priority > Node->priority)
        rotateRight(Node);
    updateSubTree(Node);
}

inline void Insert(Treap *& Node, int key, int priority) {
    if(Node == NIL) {
        Node = new Treap(NIL, NIL, key, priority);
        return;
    }
    if(Node->key == key)
        return ;
    if(Node->key > key)
        Insert(Node->left, key, priority);
    else Insert(Node->right, key, priority);
    updateSubTree(Node);
    Balance(Node);
}

inline void Erase(Treap *& Node, int key) {
    if(Node == NIL) {
        return;
    }
    if(Node->key > key)
        Erase(Node->left, key);
    else if(Node->key < key)
        Erase(Node->right, key);
    else {
        if(Node->left == NIL && Node->right == NIL) {
            delete Node;
            Node = NIL;
        }
        else {
            if(Node->left->priority > Node->right->priority) {
                rotateLeft(Node);
                Erase(Node->right, key);
            }
            else {
                rotateRight(Node);
                Erase(Node->left, key);
            }
        }
    }
    updateSubTree(Node);
}

inline int findGreatest(Treap *& Node, int key) {
    if(Node == NIL)
        return 0;
    int sum = Node->left->subTree;
    if(key == Node->key)
        return sum + 1;
    else
        if(key < Node->key)
            return findGreatest(Node->left, key);
    else
        return sum + 1 + findGreatest(Node->right, key);
}

inline int kthElement(Treap *& Node, int k) {
    if(Node->left->subTree + 1 == k)
        return Node->key;
    else
        if(Node->left->subTree + 1 > k)
            return kthElement(Node->left, k);
        else return kthElement(Node->right, k - 1 - Node->left->subTree);
}

inline void printTreap(Treap *& Node) {
    if(Node == NIL)
        return;
    cerr << Node->key << ' ' << Node->subTree << ' ' << Node->left->key << ' ' << Node->right->key << '\n';
    printTreap(Node->left);
    printTreap(Node->right);
}

int main() {
    int M;
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif

    srand(time(NULL));
    NIL = new Treap(0, 0, 0, 0, 0);
    Root = NIL;
    NIL->left = NIL->right = NIL;

    scanf("%d", &M);
    for(int t = 1 ; t <= M ; ++ t) {
        char op; int x;
        scanf(" %c %d", &op, &x);
        switch(op) {
            case 'I':
                Insert(Root, x, rand());
                break;
            case 'D':
                Erase(Root, x);
                break;
            case 'K':
                if(x > Root->subTree)
                    puts("invalid");
                else
                    printf("%d\n", kthElement(Root, x));
                 break;
            case 'C':
                printf("%d\n", findGreatest(Root, x - 1));
                break;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
