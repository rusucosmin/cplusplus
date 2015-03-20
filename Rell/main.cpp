#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <string>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;

const char infile[] = "rell.in";
const char outfile[] = "rell.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int A1, A2, A3, T1, T2, T3, dp[MAXN], finish[4], N, A[4], T[4], ind[4];

struct tupl {
    int a, b;
    tupl(int _a, int _b) {
        a = _a;
        b = _b;
    }
    inline bool operator < (tupl &altu) {
        return a < altu.a;
    }
};

queue < pair<int, tupl>  > Q;
bitset <MAXN> use;

#define mp make_pair

inline void build() {
    memset(dp, oo, sizeof(dp));
    dp[0] = 0;
    Q.push(mp(0, tupl(0, 0)));
    while(!Q.empty()) {
        int cost = Q.front().first;
        int a = Q.front().second.a;
        int b = Q.front().second.b;
        Q.pop();
        if(cost > dp[a] || cost > 100)
            continue;
        for(int i = 1 ; i <= N ; ++ i) {
            if(use[ind[i]])
                continue;
            int newTime = b + 1 + T[ind[i]];
            int newa = a + A[ind[i]];
            for(int j = b + 1 ; j <= newTime ; ++ j)
                use[j] = true;
            if(dp[newa] > newTime) {
                dp[newa] = newTime;
                Q.push(make_pair(newTime, tupl(newa, newTime)));
            }
        }
    }
}

struct classComp {
    inline bool operator () (const int &a, const int &b) const {
        return A[a] < A[b];
    }
};

int main() {
    N = 3;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> A[i], ind[i] = i;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> T[i];
    sort(ind + 1, ind + N + 1, classComp());
    build();
    int Q;
    fin >> Q;
    for(int i = 1 ; i <= Q ; ++ i) {
        int x;
        fin >> x;
        fout << dp[x] << '\n';
    }
    return 0;
}
