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
    int sum;
    bool lazy;
};

node arb[MAXN << 2];
int N, M;

void Update(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b) {
        arb[Node].sum = (dr - st + 1) - arb[Node].sum;
        arb[Node].lazy ^= 1;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(a <= mid)
        Update(2*Node, st, mid, a, b);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
    if(arb[Node].lazy)
        arb[Node].sum = (dr - st + 1) - arb[Node].sum;
}

int Query(int Node, int st, int dr, int a, int b, bool flag) {
    if(a <= st && dr <= b) {
        if(!flag)
            return arb[Node].sum;
        return (dr - st + 1) - arb[Node].sum;
    }
    int mid = ((st + dr) >> 1);
    int sum = 0;
    if(a <= mid)
        sum += Query(2*Node, st, mid, a, b, flag ^ arb[Node].lazy);
    if(mid < b)
        sum += Query(2*Node + 1, mid + 1, dr, a, b, flag ^ arb[Node].lazy);
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d%d", &N, &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        switch(op) {
        case 0:
            Update(1, 1, N, x, y);
            break;
        case 1:
            printf("%d\n", Query(1, 1, N, x, y, 0));
            break;
        }
    }
    return 0;
}
