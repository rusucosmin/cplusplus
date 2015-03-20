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
    int add;
    int nr[4];
    bool lazy;
};

int N, M;
node arb[MAXN << 2];

void Refresh(int Node) {
    int aux0 = arb[Node].nr[0];
    int aux1 = arb[Node].nr[1];
    int aux2 = arb[Node].nr[2];
    arb[Node].nr[0] = aux2;
    arb[Node].nr[1] = aux0;
    arb[Node].nr[2] = aux1;
}

void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].nr[0] = 1;
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid);
    Build(2*Node + 1, mid + 1, dr);
    arb[Node].nr[0] = arb[2*Node].nr[0] + arb[2*Node + 1].nr[0];
    arb[Node].nr[1] = arb[2*Node].nr[1] + arb[2*Node + 1].nr[1];
    arb[Node].nr[2] = arb[2*Node].nr[2] + arb[2*Node + 1].nr[2];
}

void Update(int Node, int st, int dr, int a, int b, int howMuch) {
    if(a <= st && dr <= b) {
        arb[Node].add += howMuch;
        arb[Node].add %= 3;
        for(int i = 1 ; i <= howMuch ; ++ i)
            Refresh(Node);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].add) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].add);
        arb[Node].add = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, howMuch);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, howMuch);
    arb[Node].nr[0] = arb[2*Node].nr[0] + arb[2*Node + 1].nr[0];
    arb[Node].nr[1] = arb[2*Node].nr[1] + arb[2*Node + 1].nr[1];
    arb[Node].nr[2] = arb[2*Node].nr[2] + arb[2*Node + 1].nr[2];
}

int Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node].nr[0];
    int mid = ((st + dr) >> 1);
    if(arb[Node].add) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].add);
        arb[Node].add = 0;
    }
    int Ans = 0;
    if(a <= mid)
        Ans += Query(2*Node, st, mid, a, b);
    if(mid < b)
        Ans += Query(2*Node + 1, mid + 1, dr, a, b);
    return Ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d%d", &N, &M);
    Build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int ope, x, y;
        scanf("%d%d%d", &ope, &x, &y);
        ++ x; ++ y;
        if(ope == 0)
            Update(1, 1, N, x, y, 1);
        if(ope == 1)
            printf("%d\n", Query(1, 1, N, x, y));
    }
    return 0;
}
