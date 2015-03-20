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

const int MAXN = 100;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char inord[MAXN], postord[MAXN];
string Ans;
int poz[MAXN], M, sz;

struct node {
    char value;
    node *_left;
    node *_right;
    node(const char &_value) {
        value = _value;
        _left = 0;
        _right = 0;
    }
};

void solve(const int &st, const int &dr, node * & nod) {
    if(st > dr)
        return;
    int mid = poz[postord[++ M]];
    nod = new node(inord[mid]);
    solve(st, mid - 1, nod -> _left);
    solve(mid + 1, dr, nod -> _right);
}

void DFs(const node * Node) {
    if(Node -> _left)
        DFs(Node -> _left);
    if(Node -> _right)
        DFs(Node -> _right);
    Ans += Node -> value;
}

#define fin cin
#define fout cout

int main() {
    cin.sync_with_stdio(false);
    int c;
    fin >> c;
    int X;
    while(fin >> X >> (postord + 1) >> (inord + 1)) {
        M = 0;
        sz = strlen(inord + 1);
        for(int i = 1 ; i <= sz ; ++ i)
            poz[inord[i]] = i;
        node *root;//t = new node('0');
        solve(1, sz, root);
        Ans = "";
        DFs(root);
        fout << Ans << '\n';
    }
    return 0;
}
