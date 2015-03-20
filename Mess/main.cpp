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
#include <cassert>

using namespace std;

const char infile[] = "mess.in";
const char outfile[] = "mess.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, a[MAXN];
bitset <MAXN> notOnline;

struct node {
    vector <int> below;
    vector <int> aib;
} arb[MAXN << 2];

struct classComp {
    inline bool operator () (const int &aa, const int &b) {
        return a[aa] < a[b];
    }
};

inline int lsb(int x) {
    return x & (-x);
}

inline void updateAib(int Node, int st, int dr, int pos, int value) {
    int aux = dr - st + 1;
    for(int i = pos ; i <= aux ; i += lsb(i))
        arb[Node].aib[i] += value;
}

inline void buildAib(int Node, int st, int dr) {
    arb[Node].aib.resize(dr - st + 2);
    for(int i = 0 ; i < dr - st + 1 ; ++ i)
        updateAib(Node, st, dr, i + 1, +1);
}

inline int queryAib(int Node, int pos) {
    int sum = 0;
    for(int i = pos ; i > 0 ; i -= lsb(i))
        sum += arb[Node].aib[i];
    return sum;
}

inline void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].below.push_back(st);
        buildAib(Node, st, dr);
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(Node << 1, st, mid);
    Build((Node << 1) | 1, mid+1, dr);
    arb[Node].below.resize(dr - st + 1);
    merge(arb[Node << 1].below.begin(), arb[Node << 1].below.end(), arb[(Node << 1) | 1].below.begin(),
          arb[(Node << 1) | 1].below.end(), arb[Node].below.begin(), classComp());
    buildAib(Node, st, dr);
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if( ++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if( ++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
}

inline void Update(int Node, int st, int dr, int pos) {
    if(st == dr) {
        int position = upper_bound(arb[Node].below.begin(), arb[Node].below.end(), pos, classComp()) - arb[Node].below.begin();
        updateAib(Node, st, dr, position, notOnline[pos] ? -1: 1);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(Node << 1, st, mid, pos);
    else Update((Node << 1) | 1, mid+1, dr, pos);
    int position = upper_bound(arb[Node].below.begin(), arb[Node].below.end(), pos, classComp()) - arb[Node].below.begin();
    updateAib(Node, st, dr, position, notOnline[pos] ? -1: 1);
}

inline int Query(int Node, int st, int dr, int x, int y, int k) {
    if(x <= st && dr <= y) {
        int pos = upper_bound(arb[Node].below.begin(), arb[Node].below.end(), k, classComp()) - arb[Node].below.begin();
        return queryAib(Node, pos);
    }
    int mid = ((st + dr) >> 1);
    int sum = 0;
    if(x <= mid)
        sum += Query(Node << 1, st, mid, x, y, k);
    if(mid < y)
        sum += Query((Node << 1) | 1, mid+1, dr, x, y, k);
    return sum;
}

int main() {
    freopen(infile, "r", stdin);
    get(N);
    get(M);
    for(int i = 1 ; i <= N ; ++ i)
        get(a[i]);
    Build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, p, q, k;
        get(op);
        if(op == 1) {
            get(p);
            notOnline[p] = !notOnline[p];
            Update(1, 1, N, p);
        }
        if(op == 2) {
            get(p);
            get(q);
            get(k);
            int li = 0, ls = N - 1;
            int Ans = 0;
            while(li <= ls) {
                int mid = ((li + ls) >> 1);
                int ok = Query(1, 1, N, p, q, arb[1].below[mid]);
                if(ok == k)
                    Ans = mid;
                if(ok >= k)
                    ls = mid - 1;
                else li = mid + 1;
            }
            //cerr << (Ans == -1) << '\n';
            fout << a[arb[1].below[Ans]] << '\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}
