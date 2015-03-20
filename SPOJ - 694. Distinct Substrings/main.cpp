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

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct suff {
    int nr[2], ind;
} L[MAXN];

struct classComp {
    inline bool operator() (const suff &a, const suff&b) const {
        return a.nr[0] < b.nr[0] || (a.nr[0] == b.nr[0] && a.nr[1] < b.nr[1]);
    }
};

int P[20][MAXN], N, i, stp, cnt;

inline int LCP(int x, int y) {
    int ans = 0;
    if(x == y)
        return N - x;
    for(int i = stp - 1 ; i >= 0  && x < N && y < N ; -- i)
        if(P[i][x] == P[i][y]) {
            x += (1 << i);
            y += (1 << i);
            ans += (1 << i);
        }
    return ans;
}

int T;
char s[MAXN];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    cin.get();
    for(int test = 1 ; test <= T ; ++ test) {
        cin.getline(s, MAXN);
        N = strlen(s);
        //memset(P, 0, sizeof(P));
        for(int i = 0 ; i < N ; ++ i)
            P[0][i] = (int)s[i];
        for(stp = 1, cnt = 1; (cnt >> 1) < N ; ++ stp, cnt <<= 1) {
            for(int i = 0 ; i < N ; ++ i) {
                L[i].nr[0] = P[stp - 1][i];
                L[i].nr[1] = i + cnt < N ? P[stp - 1][i + cnt] : -1;
                L[i].ind = i;
            }
            sort(L, L + N, classComp());
            for(int i = 0 ; i < N ; ++ i) {
                P[stp][L[i].ind] = (i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1]) ? P[stp][L[i - 1].ind] : i;
            }
        }
        long long ans = N - L[0].ind;
        for(int i = 1 ; i < N ; ++ i) {
            int lcp = LCP(L[i - 1].ind, L[i].ind);
            ans += (N - L[i].ind - lcp);
        }
        cout << ans << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
