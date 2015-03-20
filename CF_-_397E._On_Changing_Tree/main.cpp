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

const int MAXN = 300005;
const int MOD = 1000000007;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, M, Level[MAXN], in[MAXN], out[MAXN], K;

class Bit {
public:
    int a[2 * MAXN];
    inline int lsb(int x) {
        return x & (-x);
    }
    inline void Init() {
        memset(a, 0, sizeof(a));
    }
    inline void Update(int x, int value) {
        for(int pos = x ; pos <= K ; pos += lsb(pos)) {
            a[pos] = (1LL *a[pos] + 1LL *value + 1LL *MOD) % MOD;
        }
    }
    inline int Query(int x) {
        int sum = 0;
        for(int pos = x ; pos > 0 ; pos -= lsb(pos)) {
            sum = (1LL * sum + 1LL * a[pos] + 1LL * MOD) % MOD;
        }
        return sum;
    }
};

Bit aib[2];

void DFs(int Node, int actLevel) {
    in[Node] = ++ K;
    Level[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        DFs(*it, actLevel + 1);
    out[Node] = ++ K;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    for(int i = 2 ; i <= N ; ++ i) {
        int x;
        cin >> x;
        G[x].push_back(i);
    }
    DFs(1, 1);
    cin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int op, v, x, k;
        int temp;
        cin >> op;
        switch(op) {
        case 1:
            cin >> v >> x >> k;
            temp = (x + 1LL * Level[v] * k) % MOD;
            aib[0].Update(in[v], temp);
            aib[0].Update(out[v], -temp);
            aib[1].Update(in[v], k);
            aib[1].Update(out[v], -k);
            break;
        case 2:
            cin >> v;
            int Ans = (1LL * aib[0].Query(in[v])) % MOD;
            temp = (1LL * Level[v] * aib[1].Query(in[v])) % MOD;
            Ans = Ans - temp;
            while(Ans < 0)
                Ans += MOD;
            Ans %= MOD;
            cout << Ans << '\n';
            break;
        }
    }
    return 0;
}
