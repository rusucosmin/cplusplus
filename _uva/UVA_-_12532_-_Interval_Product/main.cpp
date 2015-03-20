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

int N, M;
int arb[MAXN << 2];

void Update(int Node, int st, int dr, int pos, int value) {
    if(st == dr) {
        arb[Node] = value;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node + 1, mid + 1, dr, pos, value);
    arb[Node] = arb[2*Node] * arb[2*Node + 1];
}

int Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid = ((st + dr) >> 1);
    int prod = 1;
    if(a <= mid)
        prod *= Query(2*Node, st, mid, a, b);
    if(mid < b)
        prod *= Query(2*Node + 1, mid + 1, dr, a, b);
    return prod;
}

inline int sgn(int x) {
    if(x > 0)
        return 1;
    if(x < 0)
        return -1;
    return 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    while(scanf("%d%d", &N, &M) == 2) {
        for(int i = 1 ; i <= N ; ++ i) {
            int x;
            scanf("%d", &x);
            x = sgn(x);
            Update(1, 1, N, i, x);
        }
        for(int i = 1 ; i <= M ; ++ i) {
            char c;
            int x, y;
            scanf(" %c %d %d", &c, &x, &y);
            if(c == 'C') {
                y = sgn(y);
                Update(1, 1, N, x, y);
            }
            else {
                int ans = Query(1, 1, N, x, y);
                if(ans == 0)
                    printf("0");
                else if(ans == -1)
                    printf("-");
                else printf("+");
            }
        }
        printf("\n");
    }
    return 0;
}
