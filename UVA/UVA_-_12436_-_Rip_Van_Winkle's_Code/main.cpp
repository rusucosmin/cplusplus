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

const long long MAXN = 250001;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct node {
    long long a1;
    long long r;
    long long sum;
    long long add;
    bool lazy, all;
};

int T;
node arb[(MAXN + 10) << 2];

inline void Refresh(long long Node, long long n, long long a1, long long r) {
    arb[Node].a1 += a1;
    arb[Node].r += r;
    arb[Node].sum += 1LL * n * (2 * a1 + 1LL * (n - 1) * r) / 2;
    arb[Node].lazy = 1;
}

void Update(long long Node, long long st, long long dr, long long a, long long b, long long z) {
    if(a <= st && dr <= b) {
        arb[Node].sum = (dr - st + 1) * z;
        arb[Node].add = z;
        arb[Node].all = 1;
        arb[Node].r = 0;
        arb[Node].a1 = 0;
        arb[Node].lazy = 0;
        return;
    }
    long long mid = ((st + dr) >> 1);
    if(arb[Node].all) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node+1, mid+1, dr, mid+1, dr, arb[Node].add);
        arb[Node].all = 0;
        arb[Node].add = 0;
    }
    if(arb[Node].lazy) {
        Refresh(2*Node, mid - st + 1, arb[Node].a1, arb[Node].r);
        Refresh(2*Node + 1, dr - mid, arb[Node].a1 + 1LL * arb[Node].r * (mid + 1 - st), arb[Node].r);
        arb[Node].lazy = 0;
        arb[Node].a1 = 0;
        arb[Node].r = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, z);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, z);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node+1].sum;
}

void UpdatePA(long long Node, long long st, long long dr, long long a, long long b, long long a1, long long r) {
    if(a <= st && dr <= b) {
        Refresh(Node, dr - st + 1, 1LL * (a1 + ((st - a) * r)), r);
        return;
    }
    long long mid = ((st + dr) >> 1);
    if(arb[Node].all) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node+1, mid+1, dr, mid+1, dr, arb[Node].add);
        arb[Node].all = 0;
        arb[Node].add = 0;
    }
    if(arb[Node].lazy) {
        Refresh(2*Node, mid - st + 1, arb[Node].a1, arb[Node].r);
        Refresh(2*Node + 1, dr - mid, arb[Node].a1 + 1LL * arb[Node].r * (mid + 1 - st), arb[Node].r);
        arb[Node].lazy = 0;
        arb[Node].a1 = 0;
        arb[Node].r = 0;
    }
    if(a <= mid)
        UpdatePA(2*Node, st, mid, a, b, a1, r);
    if(mid < b)
        UpdatePA(2*Node+1, mid+1, dr, a, b, a1, r);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
}


long long Query(long long Node, long long st, long long dr, long long a, long long b) {
    if(a <= st && dr <= b)
        return arb[Node].sum;
    long long mid = ((st + dr) >> 1);
    if(arb[Node].all) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node+1, mid+1, dr, mid+1, dr, arb[Node].add);
        arb[Node].all = 0;
        arb[Node].add = 0;
    }
    if(arb[Node].lazy) {
        Refresh(2*Node, mid - st + 1, arb[Node].a1, arb[Node].r);
        Refresh(2*Node + 1, dr - mid, arb[Node].a1 + 1LL * arb[Node].r * (mid + 1 - st), arb[Node].r);
        arb[Node].lazy = 0;
        arb[Node].a1 = 0;
        arb[Node].r = 0;
    }
    long long sum = 0;
    if(a <= mid)
        sum += Query(2*Node, st, mid, a, b);
    if(mid < b)
        sum += Query(2*Node+1, mid+1, dr, a, b);
    return sum;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    long long N = MAXN - 1;
    for(long long operat = 1 ; operat <= T ; ++ operat) {
        char op;
        long long x, y, z
        cin >> op >> x >> y;
        switch(op) {
        case 'A':
            UpdatePA(1, 1, N, x, y, 1, 1);
            break;
        case 'B':
            UpdatePA(1, 1, N, x, y, (y - x + 1), -1);
            break;
        case 'C':
            cin >> z;
            Update(1, 1, N, x, y, z);
            break;
        case 'S':
            cout << Query(1, 1, N, x, y) << '\n';
            break;
        }
    }
    return 0;
}
