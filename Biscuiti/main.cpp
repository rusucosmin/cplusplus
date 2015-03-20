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

const char infile[] = "biscuiti.in";
const char outfile[] = "biscuiti.out";

ofstream fout(outfile);

const int MAXN = 100005;
const long long oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A[MAXN];

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
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

struct node {
    long long _min;
    int _posmin;
    long long _lazy;
} arb[MAXN << 2];

inline void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node]._min = 1LL * A[st];
        arb[Node]._posmin = st;
        arb[Node]._lazy = 0;
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(Node << 1, st, mid);
    Build((Node << 1) | 1, mid + 1, dr);
    arb[Node]._min = min(arb[Node << 1]._min, arb[(Node << 1) | 1]._min);
    if(arb[Node]._min == arb[Node << 1]._min)
        arb[Node]._posmin = arb[Node << 1]._posmin;
    else arb[Node]._posmin = arb[(Node << 1) | 1]._posmin;
    arb[Node]._lazy = 0;
}

inline void lazyUpdate(int Node, int st, int dr, long long value) {
    arb[Node]._min += value;
    arb[Node]._lazy += value;
}

inline void Update(int Node, int st, int dr, int a, int b, long long value) {
    if(a <= st && dr <= b) {
        lazyUpdate(Node, st, dr, value);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node]._lazy) {
        lazyUpdate(Node << 1, st, mid, arb[Node]._lazy);
        lazyUpdate((Node << 1) | 1, mid+1, dr, arb[Node]._lazy);
        arb[Node]._lazy = 0;
    }
    if(a <= mid)
        Update(Node << 1, st, mid, a, b, value);
    if(mid < b)
        Update((Node << 1) | 1, mid+1, dr, a, b, value);
    arb[Node]._min = min(arb[Node << 1]._min, arb[(Node << 1) | 1]._min);
    if(arb[Node]._min == arb[Node << 1]._min)
        arb[Node]._posmin = arb[Node << 1]._posmin;
    else arb[Node]._posmin = arb[(Node << 1) | 1]._posmin;
}

int main() {
    freopen(infile, "r", stdin);
    long long ans = 0;
    get(N);
    for(int i = 1 ; i <= N ; ++ i) {
        get(A[i]);
        ans -= A[i];
    }
    Build(1, 1, N);
    for(int i = 1 ; i <= N ; ++ i) {
        ans += arb[1]._min;
        //cerr << arb[1]._min << '\n';
        int aux = arb[1]._posmin;
        Update(1, 1, N, aux, aux, 1LL * oo * oo);
        //if(aux - 1 == 0)
        //    continue;
        Update(1, 1, N, 1, aux, 1LL * i); /// lol
    }
    fout << ans << '\n';
    fout.close();
    return 0;
}
