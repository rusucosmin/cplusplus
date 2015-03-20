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

struct Node {
    int mfreq, lfreq, rfreq;
    void Update(int value) {
        mfreq = value;
        lfreq = value;
        rfreq = value;
    }
    void Update(int st, int dr, int mid, node Left, node Right) {
        if(a[mid] == a[mid + 1]) {
            lfreq = Left.lfreq + arb[2*Node+1].lfreq * (a[st] == a[mid]);
            rfreq = arb[2*Node + 1].rfreq + Left.rfreq * (a[mid + 1] == a[dr]);
            int temp = Left.rfreq + arb[2*Node + 1].lfreq;
            arb[Node].mfreq = max(temp, max(Left.rfreq, Right.lfreq));
            /// Aici am ramas!
        }
        else {
            arb[Node].lfreq = arb[2*Node].lfreq;
            arb[Node].rfreq = arb[2*Node + 1].rfreq;
            arb[Node].mfreq = max(arb[2*Node].mfreq, arb[2*Node + 1].mfreq);
        }
    }
};

Node arb[MAXN << 2];

void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].Update(1);
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st mid,);
    Build(2*Node +1, mid + 1, dr);

}

node Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid = ((st + dr) >> 1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d %d", &N, &M);
    for(int i = 1 ; i <= N ; ++ i)
        scanmf("%d", &a[i]);
    Build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", Query(1, 1, N, x, y).mfreq);
    }
    return 0;
}
