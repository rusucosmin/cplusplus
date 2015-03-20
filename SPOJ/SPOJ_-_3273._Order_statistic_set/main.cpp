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
    Treap(Treap *_left, Treap *_right, int _key, int _priority) {
        left = _left;
        right = _right;
        key = _key;
        priority = _priority;
        subTree = 0;
    }
} *Root, *NIL;

inline bool Find(Treap *& Node, int key) {
    if(Node == NIL)
        return false;
    if(Node->key == key)
        return true;
    if(Node->key > key)
        return Find(Node -> left, key);
    return Find(Node->right, key);
}

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
    Node = aux;
}

inline void rotateRight(Treap *& Node) {
    Treap *aux = Node->right;
    Node->right = aux->left;
    aux->left = Node;
    Node = aux;
}

inline void Balance(Treap *& Node) {
    if(Node->left->priority > Node->priority)
        rotateLeft(Node);
    if(Node->right->priority > Node->priority)
        rotateRight(Node);
}

inline void Insert(Treap *& Node, int key, int priority) {
    if(Node == NIL) {
        Node = new Treap(NIL, NIL, key, priority);
        return;
    }
    if(Node->key > key)
        Insert(Node->left, key, priority);
    else Insert(Node->right, key, priority);
    Balance(Node);
    updateSubTree(Node->left);
    updateSubTree(Node->right);
    updateSubTree(Node);
}

inline void Erase(Treap *& Node, int key) {
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
    updateSubTree(Node->left);
    updateSubTree(Node->right);
    updateSubTree(Node);
}

inline int findGreatest(Treap *& Node, int key) {
    if(Node == NIL)
        return 0;
    int sum = 0;
    if(Node->key >= key)
        return Node->left->subTree;
    else sum += findGreatest(Node->left, key);
    sum += findGreatest(Node->right, key);
    return sum;
}

inline int kthElement(Treap *& Node, int k) {
    if(Node->left->subTree + 1 == k)
        return Node->key;
    if(Node->left->subTree + 1 >= k)
        return kthElement(Node->left, k);
    return kthElement(Node->right, k - 1 - Node->left->subTree);
}


int main() {
    int M;
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif

    srand(time(NULL));
    NIL = new Treap(0, 0, 0, 0);
    NIL->left = NIL->right = NIL;
    Root = NIL;

    cin >> M;
    for(int t = 1 ; t <= M ; ++ t) {
        char op;
        int x;
        cin >> op >> x;
        switch(op) {
            case 'I':
                if(!Find(Root, x))
                    Insert(Root, x, rand() % oo);
                break;
            case 'D':
                if(Find(Root, x))
                    Erase(Root, x);
                break;
            case 'K':
                if(x > Root->subTree)
                    cout << "invalid\n";
                else
                    cout << kthElement(Root, x) << '\n';
                 break;
            case 'C':
                cout << findGreatest(Root, x) << '\n';
                break;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
