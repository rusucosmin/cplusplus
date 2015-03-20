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

const char infile[] = "tabara2.in";
const char outfile[] = "tabara2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 50005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, S, M, father[MAXN << 1], c[MAXN], arb[MAXN << 3], Maxim[MAXN << 1];

inline int Find(int x) {
    if(father[x] != x)
        father[x] = Find(father[x]);
    return father[x];
}

inline void Update(int node, int st, int dr, int pos, int value) {
    if(st == dr) {
        arb[node] = max(arb[node], value);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(node << 1, st, mid, pos, value);
    else
        Update((node << 1) | 1, mid + 1, dr, pos, value);
    arb[node] = max(arb[node << 1], arb[(node << 1) | 1]);
}

inline int Query(int node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[node];
    int mid = ((st + dr) >> 1);
    int ans = -oo;
    if(a <= mid)
        ans = max(ans, Query(node << 1, st, mid, a, b));
    if(mid < b)
        ans = max(ans, Query((node << 1) | 1, mid + 1, dr, a, b));
    return ans;
}

inline void Unite(int X, int Y) {
    X = Find(X);
    Y = Find(Y);
    if(X > Y)
        swap(X, Y);
    father[X] = Y;
    Maxim[Y] = max(Maxim[X], Maxim[Y]);
    if(Y > S)
        Update(1, 1, N, Y - S, Maxim[Y]);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> S >> M;
    for(int i = 1 ; i <= S ; ++ i) {
        fin >> c[i];
        father[i] = i;
        Maxim[i] = c[i];
    }
    for(int i = 1 ; i <= N ; ++ i) {
        father[i + S] = i + S;
    }
    for(int i = 1 ; i <= M ; ++ i) {
        char op;
        int type, x, y;
        fin >> op;
        if(op == 'U') {
            fin >> type >> x >> y;
            if(type == 1)
                Unite(x, y);
            else
                Unite(x + S, y);
        }
        else {
            fin >> x >> y;
            fout << Query(1, 1, N, x, y) << '\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}
