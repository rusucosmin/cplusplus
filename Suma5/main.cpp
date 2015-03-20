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

const char infile[] = "suma5.in";
const char outfile[] = "suma5.out";

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

int N, M, a[MAXN];

struct aint {
    long long sum, query, lazy;
    int st, dr;
    aint() {
        sum = query = lazy = 0;
    }
    void update(aint left, aint right) {
        sum = left.sum  + right.sum;
        query = left.query + right.query + right.sum * (left.dr - left.st + 1);
        st = left.st;
        dr = right.dr;
    }
    void sendlazy(int z, int st, int dr) {
        lazy += z;
        sum += (1LL * (dr - st + 1) * z);
        query += (z * (1LL * (dr - st + 1) * (dr - st + 2)) / 2);
    };
} arb[MAXN << 2];

inline void build(int node, int st, int dr) {
    if(st == dr) {
        arb[node].sum = arb[node].query = a[st];
        arb[node].lazy = 0;
        arb[node].st = st;
        arb[node].dr = dr;
        //cerr << st << ' ' << dr << ' ' << arb[node].sum << ' ' << arb[node].query << '\n';

        return ;
    }
    int mid = ((st + dr) >> 1);

    build(node << 1, st, mid);
    build(((node << 1) | 1), mid + 1, dr);

    arb[node].update(arb[node << 1], arb[(node << 1) | 1]);
    arb[node].dr = dr;
    //cerr << st << ' ' << dr << ' ' << arb[node].sum << ' ' << arb[node].query << '\n';
}

inline void update(int node, int st, int dr, int a, int b, int z) {
    if(a <= st && dr <= b) {
        arb[node].sendlazy(z, st, dr);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[node].lazy) {
        arb[node << 1].sendlazy(arb[node].lazy, st, mid);
        arb[(node << 1) | 1].sendlazy(arb[node].lazy, mid + 1, dr);
        arb[node].lazy = 0;
    }
    if(a <= mid)
        update(node << 1, st, mid, a, b, z);
    if(mid < b)
        update((node << 1) | 1, mid + 1, dr, a, b, z);
    arb[node].update(arb[node << 1], arb[(node << 1) | 1]);
}

inline aint query(int node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[node];
    int mid = ((st + dr) >> 1);
    if(arb[node].lazy) {
        arb[node << 1].sendlazy(arb[node].lazy, st, mid);
        arb[(node << 1) | 1].sendlazy(arb[node].lazy, mid + 1, dr);
        arb[node].lazy = 0;
    }
    aint ret, left, right;
    left.st = -1;
    right.st = -1;
    if(a <= mid)
        left = query((node << 1), st, mid, a, b);
    if(mid < b)
        right = query((node << 1) | 1, mid + 1, dr, a, b);
    if(left.st == -1)
        return right;
    if(right.st == -1)
        return left;
    ret.update(left, right);
    return ret;
}

int main() {
    cin.sync_with_stdio(false);
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> a[i];
    build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y, z;
        fin >> op >> x >> y;
        if(!op) {
            fin >> z;
            update(1, 1, N, x, y, z);
        }
        else
            fout << query(1, 1, N, x, y).query << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
