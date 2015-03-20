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

const char infile[] = "traseu3.in";
const char outfile[] = "traseu3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int dk[] = {-1, 0, 0, 0, 0, 1};
const int dl[] = { 0,-1, 0, 0, 1, 0};
const int dc[] = { 0, 0,-1, 1, 0, 0};

short dp[MAXN][MAXN][MAXN];
short kf[MAXN][MAXN][MAXN];
short lf[MAXN][MAXN][MAXN];
short cf[MAXN][MAXN][MAXN];
bool full[MAXN][MAXN][MAXN];

inline bool isBetter(int k1, int l1, int c1, int k2, int l2, int c2) {
    int k3 = kf[k2][l2][c2];
    int l3 = lf[k2][l2][c2];
    int c3 = cf[k2][l2][c2];
    if(k1 < k3)
        return true;
    if(k1 > k3)
        return false;
    if(l1 < l3)
        return true;
    if(l1 > l3)
        return false;
    if(c1 < c3)
        return true;
    if(c1 > c3)
        return false;
    return false;
}

int N, M, K1, K2, L1, L2, C1, C2;

void Write(int k, int l, int c) {
    if(k == K1 && l == L1 && c == C1) {
        fout << k << ' ' << l << ' ' << c << '\n';
        return;
    }
    Write(kf[k][l][c], lf[k][l][c], cf[k][l][c]);
    fout << k << ' ' << l << ' ' << c << '\n';
}

inline bool inside(int k, int l, int c) {
    if(k >= 1 && k <= N && l >= 1 && l <= N && c >= 1 && c <= N)
        return 1;
    return 0;
}

int main() {
    fin >> N >> M;
    fin >> K1 >> L1 >> C1 >> K2 >> L2 >> C2;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        full[x][y][z] = 1;
    }
    queue <pair<int, pair<int, int> > > Q;
    memset(dp, oo, sizeof(dp));
    dp[K1][L1][C1] = 1;
    Q.push(make_pair(K1, make_pair(L1, C1)));
    while(!Q.empty()) {
        int k = Q.front().first;
        int l = Q.front().second.first;
        int c = Q.front().second.second;
        Q.pop();
        for(int i = 0 ; i < 6 ; ++ i) {
            int newk = k + dk[i];
            int newl = l + dl[i];
            int newc = c + dc[i];
            if(inside(newk, newl, newc))
            if(!full[newk][newl][newc] && (dp[newk][newl][newc] > dp[k][l][c] + 1)) {
                dp[newk][newl][newc] = dp[k][l][c] + 1;
                kf[newk][newl][newc] = k;
                lf[newk][newl][newc] = l;
                cf[newk][newl][newc] = c;
                Q.push(make_pair(newk, make_pair(newl, newc)));
            }
        }
    }
    fout << dp[K2][L2][C2] << '\n';
    Write(K2, L2, C2);
    fin.close();
    fout.close();
    return 0;
}
