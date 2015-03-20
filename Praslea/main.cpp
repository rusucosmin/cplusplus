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

const char infile[] = "praslea.in";
const char outfile[] = "praslea.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 515;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct zmeu {
    int a, b, f, r;
} A[MAXN];

int N, R, force[MAXN], dp[MAXN], risk[MAXN];
vector <int> V;

inline int doDp(const int &t1, const int &t2) {
    int M = 0;
    for(int i = 1 ; i <= N ; ++ i)
        if(A[i].a <= t1 && t2 <= A[i].b) {
            force[++ M] = A[i].f;
            risk[M] = A[i].r;
        }
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for(int i = 1 ; i <= M ; ++ i)
        for(int j = R - risk[i] ; j >= 0 ; -- j)
            if(dp[j] >= 0 && dp[j] + force[i] > dp[j + risk[i]])
                dp[j + risk[i]] = dp[j] + force[i];
    int ret = 0;
    for(int i = 0 ; i <= R ; ++ i)
        ret = max(ret, dp[i]);
    return ret;
}

int main() {
    cin.sync_with_stdio(false);
    fin >> N >> R;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> A[i].a >> A[i].b >> A[i].f >> A[i].r;
        ++ A[i].b;
        V.push_back(A[i].a);
        V.push_back(A[i].b);
    }
    sort(V.begin(), V.end());
    long long Ans = 0;
    for(int i = 0 ; i + 1 < V.size() ; ++ i)
        if(V[i] < V[i + 1])
            Ans += 1LL * doDp(V[i], V[i + 1]) * (V[i + 1] - V[i]);
    fout << Ans << "\n";
    fin.close();
    fout.close();
    return 0;
}
