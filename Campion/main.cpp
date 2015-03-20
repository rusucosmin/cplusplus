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

const char infile[] = "secvnumber.in";
const char outfile[] = "secvnumber.out";

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

struct node {
    int value;
    int last;
} arb[MAXN << 2];

int iPow[MAXN], sum[MAXN], N, M, R;
int A[MAXN];
int Ans;

inline void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].value = A[st];
        arb[Node].last = -1;
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid);
    Build(2*Node+1, mid+1, dr);
    arb[Node].value = (((1LL * arb[2*Node].value * iPow[dr - mid]) % R) + arb[2*Node + 1].value) % R;
    arb[Node].last = -1;
}

inline void Update(int Node, int st, int dr, int a, int b, int value) {
    if(a <= st && dr <= b) {
        arb[Node].last = value;
        arb[Node].value = (1LL * sum[dr - st + 1] * value) % R;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].last != -1) {
        Update(2*Node, st, mid, st, mid, arb[Node].last);
        Update(2*Node+1, mid+1, dr, mid+1, dr, arb[Node].last);
        arb[Node].last = -1;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, value);
    if(mid < b)
        Update(2*Node+1, mid+1, dr, a, b, value);
    arb[Node].value = (((1LL * arb[2*Node].value * iPow[dr - mid]) % R) + arb[2*Node + 1].value) % R;
}

inline void Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b) {
        Ans = (Ans + ((1LL * iPow[b - dr] * arb[Node].value) % R)) % R;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].last != -1) {
        Update(2*Node, st, mid, st, mid, arb[Node].last);
        Update(2*Node+1, mid+1, dr, mid+1, dr, arb[Node].last);
        arb[Node].last = -1;
    }
    if(a <= mid)
        Query(2*Node, st, mid, a, b);
    if(mid < b)
        Query(2*Node+1, mid+1, dr, a, b);
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d", &N, &M, &R);
    iPow[0] = 1;
    sum[1] = 1;
    for(int i = 1 ; i <= N ; ++ i) {
        iPow[i] = (1LL * iPow[i - 1] * 10) % R;
        sum[i + 1] = (sum[i] + iPow[i]) % R;
        scanf("%d", &A[i]);
    }
    Build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y, z;
        scanf("%d %d %d", &op, &x, &y);
        if(op == 1) {
            scanf("%d", &z);
            Update(1, 1, N, x, y, z);
        }
        if(op == 2) {
            Ans = 0;
            Query(1, 1, N, x, y);
            printf("%d\n", Ans);
        }
    }
    return 0;
}
