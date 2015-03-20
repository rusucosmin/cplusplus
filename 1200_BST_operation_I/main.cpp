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
    char value;
    node *st, *dr;
    node(const char &x) {
        value = x;
        st = 0;
        dr = 0;
    }
};

char S[30];
int N;
node *root;
vector <char> v;

void Insert(const char &a, node *&actNode) {
    if(!actNode) {
        actNode = new node(a);
        return;
    }
    if(actNode -> value < a)
        Insert(a, actNode -> st);
    else Insert(a, actNode -> dr);
}

inline string Search(const char &toSearch, node *actNode) {
    if(!actNode)
        return "nao existe";
    if(actNode -> value == toSearch)
        return "existe";
    if(actNode -> value < toSearch)
        return Search(toSearch, actNode -> st);
    return Search(toSearch, actNode -> dr);
}

inline void inOrdDFs(const node *actNode) {
    if(actNode -> st)
        inOrdDFs(actNode -> st);
    v.push_back(actNode -> value);
    if(actNode -> dr)
        inOrdDFs(actNode -> dr);
}

inline void postOrdDFs(const node *actNode) {
    v.push_back(actNode -> value);
    if(actNode -> st)
        postOrdDFs(actNode -> st);
    if(actNode -> dr)
        postOrdDFs(actNode -> dr);
}

inline void preOrdDFs(const node *actNode) {
    if(actNode -> st)
        preOrdDFs(actNode -> st);
    if(actNode -> dr)
        preOrdDFs(actNode -> dr);
    v.push_back(actNode -> value);
}

#define fin cin
#define fout cout

int main() {
    while(fin >> (S + 1)) {
        N = strlen(S + 1);
        if(S[1] == 'I' && N == 1) {
            char a;
            fin >> a;
            Insert(a, root);
            continue;
        }
        if(S[1] == 'P' && N == 1) {
            char a;
            fin >> a;
            fout << a << ' ' << Search(a, root) << '\n';
            continue;
        }
        v.clear();
        if(S[1] == 'I') {
            inOrdDFs(root);
            fout << v[v.size() - 1];
            for(int i = v.size() - 2 ; i >= 0 ; -- i)
                fout << ' ' << v[i];
            fout << '\n';
            continue;
        }
        if(S[1] == 'P' && S[2] == 'R') {
            preOrdDFs(root);
            fout << v[v.size() - 1];
            for(int i = v.size() - 2 ; i >= 0 ; -- i)
                fout << ' ' << v[i];
            fout << '\n';
            continue;
        }
        if(S[1] == 'P' && S[2] == 'O') {
            postOrdDFs(root);
            fout << v[v.size() - 1];
            for(int i = v.size() - 2 ; i >= 0 ; -- i)
                fout << ' ' << v[i];
            fout << '\n';
            continue;
        }
    }
    return 0;
}
