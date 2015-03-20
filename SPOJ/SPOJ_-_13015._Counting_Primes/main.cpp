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
    int all;
    bool lazy;
    int sum;
};

node arb[MAXN << 2];
bitset <1000005> Sieve;
int a[MAXN];
int N, T, M;

void Build(int Node, int st, int dr) {
    if(st == dr) {
        if(Sieve[a[st]])
            arb[Node].sum = 0;
        else arb[Node].sum = 1;
        arb[Node].lazy = 0;
        arb[Node].all = 0;
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid);
    Build(2*Node + 1, mid + 1, dr);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
    arb[Node].lazy = 0;
}

void BuildSiveOfErathosthenes() {
    for(int i = 2 ; i <= 1000000 ; ++ i)
        if(!Sieve[i])
            for(int j = i + i ; j <= 1000000 ; j += i)
                Sieve[j] = true;
}

void Update(int Node, int st, int dr, int a, int b, int value) {
    if(a <= st && dr <= b) {
        arb[Node].lazy = 1;
        arb[Node].all = value;
        if(Sieve[value])
            arb[Node].sum = 0;
        else arb[Node].sum = (dr - st + 1);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, st, mid, st, mid, arb[Node].all);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].all);
        arb[Node].lazy = 0;
        arb[Node].all = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, value);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, value);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
}

int Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node].sum;
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, st, mid, st, mid, arb[Node].all);
        Update(2*Node +1 , mid + 1, dr, mid + 1, dr, arb[Node].all);
        arb[Node].all = 0;
        arb[Node].lazy = 0;
    }
    int ret = 0;
    if(a <= mid)
        ret += Query(2*Node, st, mid, a, b);
    if(mid < b)
        ret += Query(2*Node + 1, mid + 1, dr, a, b);
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    BuildSiveOfErathosthenes();
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d %d", &N, &M);
        printf("Case %d:\n", test);
        for(int i = 1 ; i <= N ; ++ i)
            scanf("%d", &a[i]);
        Build(1, 1, N);
        for(int i = 1 ; i <= M ; ++ i) {
            int op, x, y, z;
            scanf("%d", &op);
            if(op == 0) {
                scanf("%d %d %d", &x, &y, &z);
                Update(1, 1, N, x, y, z);
            }
            if(op == 1) {
                scanf("%d %d", &x, &y);
                printf("%d\n", Query(1, 1, N, x, y));
            }
        }
    }
    return 0;
}
