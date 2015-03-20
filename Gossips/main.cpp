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

const char infile[] = "gossips.in";
const char outfile[] = "gossips.out";

ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char parse[1 << 15];
int pos;

Graph G;
int N, M, Q, K, out[MAXN], in[MAXN];
set <int> S[MAXN << 3], T[MAXN << 3];
bool Ans;
bitset <MAXN> notRoot;

const int DIM = 10000;
char buff[DIM];
int poz=0;

#define parse

inline int get() {
     int numar = 0;
     while (buff[poz] < '0' || buff[poz] > '9')
        if (++poz == DIM) {
            fread(buff,1,DIM,stdin);
            poz=0;
        }
     while ('0'<=buff[poz] && buff[poz]<='9') {
        numar = numar*10 + buff[poz] - '0';
        if (++poz == DIM) {
            fread(buff,1,DIM,stdin);
            poz=0;
        }
     }
     return numar;
}

inline void DFs(int Node) {
    in[Node] = ++ K;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        DFs(*it);
    out[Node] = ++ K;
}

inline void Update(int Node, int st, int dr, int a, int b, int c) {
    T[Node].insert(c);
    if(a <= st && dr <= b) {
        S[Node].insert(c);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(a <= mid)
        Update(Node << 1, st, mid, a, b, c);
    if(mid < b)
        Update((Node << 1) | 1, mid+1, dr, a, b, c);
}

inline void Query(int Node, int st, int dr, int a, int b, int c, int d) {
    set <int> :: iterator it = S[Node].lower_bound(c);
    if(it != S[Node].end() && *it <= d) {
        Ans = 1;
        return;
    }
    if(st == dr || T[Node].lower_bound(c) == T[Node].end() || (*T[Node].lower_bound(c) > d))
        return ;
    int mid = ((st + dr) >> 1);
    if(a <= mid)
        Query(Node << 1, st, mid, a, b, c, d);
    if(mid < b)
        if(!Ans)
            Query((Node << 1) | 1, mid+1, dr, a, b, c, d);
}

int main() {
    #define parse
    #ifndef parse
    fin >> N >> M >> Q;
    #endif // parse
    #ifdef parse
    freopen(infile, "r", stdin);
    N = get();
    M = get();
    Q = get();
    #endif
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        #ifndef parse
        fin >> x >> y;
        #endif // parse
        #ifdef parse
        x = get();
        y = get();
        #endif
        notRoot[y] = 1;
        G[x].push_back(y);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!notRoot[i])
            DFs(i);
    for(int i = 1 ; i <= Q ; ++ i) {
        int op, x, y;
        #ifdef parse
        op = get();
        x = get();
        y = get();
        #endif
        #ifndef parse
        fin >> op >> x >> y;
        #endif // parse
        if(op == 1) {
            Ans = false;
            Query(1, 1, K, in[x], out[x], in[y], out[y]);
            if(Ans)
                fout << "YES\n";
            else fout << "NO\n";
        }
        else
            Update(1, 1, K, in[x], out[x], in[y]);
    }
    fout.close();
    return 0;
}
