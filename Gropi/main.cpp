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

#define x first
#define y second

const char infile[] = "gropi.in";
const char outfile[] = "gropi.out";

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

pair<int, int> V[MAXN], X, Y;
int C, N, M, dp[MAXN];

int main() {
    fin >> C >> N;
    for(int i = 0 ; i < N ; ++ i)
        fin >> V[i].y >> V[i].x;
    V[N ++ ] = make_pair(C + 5, 0);
    sort(V, V + N);
    dp[0] = V[0].y != V[1].y;
    for(int i = 1 ; i + 1 < N ; ++ i)
        dp[i] = (V[i].y != V[i + 1].y) + dp[i - 1];
    for(fin >> M ; M ; -- M) {
        fin >> X.y >> X.x >> Y.y >> Y.x;
        if(Y < X)
            swap(X, Y);
        int ubA = upper_bound(V, V + N, make_pair(X.x, 0)) - V;
        if(Y.x <= V[ubA].x)
            fout << Y.x - X.x + 1 + (X.y != Y.y) << '\n';
        else {
            int ubB = upper_bound(V, V + N, make_pair(Y.x, 0)) - V - 1;
            fout << Y.x - X.x + 1 + dp[ubB - 1] - dp[ubA - 1] + (X.y == V[ubA].y) + (Y.y == V[ubB].y) << '\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}
