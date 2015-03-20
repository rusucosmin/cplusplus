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

const char infile[] = "numerex.in";
const char outfile[] = "numerex.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

struct node {
    long long a1, r;
    bool lazy;
    long long sum;
};

node arb[MAXN << 2];
int N, M;

void Update(int Node, int st, int dr, int a, int b, long long beg, long long k, bool ok = false) {
    if(a <= st && dr <= b) {
        arb[Node].lazy = 1;
        if(ok)
            arb[Node].a1 += 1LL * beg;
        else
            arb[Node].a1 += 1LL * (st - a + 1) * k;
        arb[Node].r += 1LL * k;
        int n = dr - st + 1;
        arb[Node].sum = 1LL * n * (2LL * arb[Node].a1 + arb[Node].r * (n - 1)) / 2LL;
        if(st == dr)
            return;
        arb[Node].sum += arb[2*Node].sum + arb[2*Node + 1].sum;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, st, mid, st, mid, arb[Node].a1, arb[Node].r, true);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].a1 + 1LL * (mid + 1 - st) * arb[Node].r, arb[Node].r, true);
        arb[Node].lazy = 0;
        arb[Node].a1 = 0LL;
        arb[Node].r = 0LL;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, beg, k);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, beg, k);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
}

long long Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node].sum;
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, st, mid, st, mid, arb[Node].a1, arb[Node].r, true);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].a1 + (mid + 1 - st) * arb[Node].r, arb[Node].r, true);
        arb[Node].lazy = 0;
        arb[Node].a1 = 0LL;
        arb[Node].r = 0LL;
    }
    long long sum = 0;
    if(a <= mid)
        sum += Query(2*Node, st, mid, a, b);
    if(mid < b)
        sum += Query(2*Node + 1, mid + 1, dr, a, b);
    return sum;
}

int main() {
    fin >> N >> M;
    for(int i = 1; i <= M ; ++ i) {
        int op, x, y, l;
        long long k;
        fin >> op;
        switch(op) {
            case 0:
                fin >> x >> l >> k;
                Update(1, 1, N, x, x + l - 1, k, k);
                break;
            case 1:
                fin >> x >> y;
                fout << Query(1, 1, N, x, y) << '\n';
                break;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
