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

struct node {
    int value;
    node *st, *dr;
    node(const int &x) {
        value = x;
        st = 0;
        dr = 0;
    }
};

char S[30];
int N;
node *root;
vector <int> v;

void Insert(const int &a, node *&actNode) {
    if(!actNode) {
        actNode = new node(a);
        return;
    }
    if(actNode -> value < a)
        Insert(a, actNode -> st);
    else Insert(a, actNode -> dr);
}

inline string Search(const int &toSearch, node *actNode) {
    if(!actNode)
        return "nao existe";
    if(actNode -> value == toSearch)
        return "existe";
    if(actNode -> value < toSearch)
        return Search(toSearch, actNode -> st);
    return Search(toSearch, actNode -> dr);
}

inline void inOrdDFs(const node *actNode) {
    if(!actNode)
        return;
    if(actNode -> st)
        inOrdDFs(actNode -> st);
    v.push_back(actNode -> value);
    if(actNode -> dr)
        inOrdDFs(actNode -> dr);
}

inline void postOrdDFs(const node *actNode) {
    if(!actNode)
        return;
    v.push_back(actNode -> value);
    if(actNode -> st)
        postOrdDFs(actNode -> st);
    if(actNode -> dr)
        postOrdDFs(actNode -> dr);
}

inline void preOrdDFs(const node *actNode) {
    if(!actNode)
        return;
    if(actNode -> st)
        preOrdDFs(actNode -> st);
    if(actNode -> dr)
        preOrdDFs(actNode -> dr);
    v.push_back(actNode -> value);
}

inline void Remove(const int &toRemove, node *& actNode) {
    if(actNode -> value == toRemove) {
        if(actNode->dr == 0 && actNode->st == 0) {
            delete actNode;
            actNode = 0;
            return;
        }
        if(actNode->dr && actNode->st) {
            node *aux = actNode->dr;
            while(aux->st)
                aux = aux->st;

            actNode->value = aux->value;
            Remove(aux->value, actNode->dr);
            return;
        }
        if(actNode->st) {
            actNode = actNode->st;
            return;
        }
        if(actNode->dr) {
            actNode = actNode->dr;
            return;
        }
        return;
    }
    if(actNode -> value < toRemove)
        Remove(toRemove, actNode -> st);
    else
        Remove(toRemove, actNode -> dr);
}

#define fin cin
#define fout cout

int main() {
    while(fin >> (S + 1)) {
        N = strlen(S + 1);
        for(int i = 1 ; i <= N ; ++ i)
            if(S[i] >= 'a' && S[i] <= 'z')
                S[i] = S[i] - ('a' - 'A');
        if(S[1] == 'I' && N == 1) {
            int a;
            fin >> a;
            Insert(a, root);
            continue;
        }
        if(S[1] == 'P' && N == 1) {
            int a;
            fin >> a;
            fout << a << ' ' << Search(a, root) << '\n';
            continue;
        }
        if(S[1] == 'R' && N == 1) {
            int x;
            fin >> x;
            if(Search(x, root) == "existe")
                Remove(x, root);
        }
        v.clear();
        if(S[1] == 'I') {
            inOrdDFs(root);
            if(!v.size())
                continue;
            fout << v[v.size() - 1];
            for(int i = v.size() - 2 ; i >= 0 ; -- i)
                fout << ' ' << v[i];
            fout << '\n';
            continue;
        }
        if(S[1] == 'P' && S[2] == 'R') {
            preOrdDFs(root);
            if(!v.size())
                continue;
            fout << v[v.size() - 1];
            for(int i = v.size() - 2 ; i >= 0 ; -- i)
                fout << ' ' << v[i];
            fout << '\n';
            continue;
        }
        if(S[1] == 'P' && S[2] == 'O') {
            postOrdDFs(root);
            if(!v.size())
                continue;
            fout << v[v.size() - 1];
            for(int i = v.size() - 2 ; i >= 0 ; -- i)
                fout << ' ' << v[i];
            fout << '\n';
            continue;
        }
    }
    return 0;
}
