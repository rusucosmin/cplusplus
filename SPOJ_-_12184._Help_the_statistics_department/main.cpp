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

const int MAXN = 100000;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int arb[(MAXN << 2) + 10];

int T, Q;

void Update(int Node, int st, int dr, int pos, int value) {
    if(st == dr) {
        arb[Node] = value;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node + 1, mid + 1, dr, pos, value);
    arb[Node] = arb[2*Node] + arb[2*Node + 1];
}

int QueryKth(int Node, int st, int dr, int k) {
    if(st == dr)
        return st;
    int mid = ((st + dr) >> 1);
    if(arb[2*Node] >= k)
        return QueryKth(2*Node, st, mid, k);
    else return QueryKth(2*Node + 1, mid + 1, dr, k - arb[2*Node]);
}

int QueryRank(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid = ((st + dr) >> 1);
    int sum = 0;
    if(a <= mid)
        sum += QueryRank(2*Node, st, mid, a, b);
    if(mid < b)
        sum += QueryRank(2*Node + 1, mid + 1, dr, a, b);
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        memset(arb, 0, sizeof(arb));
        scanf("%d", &Q);
        /***
            If K = 1 then perform Add(x)
            If K = 2 then perform Delete(x)
            If K = 3 then perform ReportKth(x)
            If K = 4 then perform ReportRank(x)
        ***/
        for(int i = 1 ; i <= Q ; ++ i) {
            int op, x;
            scanf("%d %d", &op, &x);
            switch(op) {
            case 1:
                Update(1, 1, MAXN, x, 1);
                break;
            case 2:
                Update(1, 1, MAXN, x, 0);
                break;
            case 3:
                printf("%d\n", QueryKth(1, 1, MAXN, x));
                break;
            case 4:
                printf("%d\n", QueryRank(1, 1, MAXN, 1, x));
                break;
            }
        }
    }
    return 0;
}
