/*
    Please implement Presentation Error, infoarena :D
*/
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

const char infile[] = "euclid.in";
const char outfile[] = "euclid.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 405;
const int MAXL = 10;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int Log[MAXN];

int GCD(int x, int y) {
    if(y == 0)
        return x;
    return GCD(y, x % y);
}

inline void buildLog(int N) {
    for(int i = 2 ; i < N ; ++ i)
        Log[i] = Log[i >> 1] + 1;
}

inline void buildRMQonLine(int A[MAXN], int RMQ[MAXL][MAXN], int N, int W, int B[MAXN]) {
    for(int i = 1 ; i <= N ; ++ i)
        RMQ[0][i] = A[i];
    for(int i = 1 ; (1 << i) <= N ; ++ i) {
        for(int j = 1 ; j + (1 << i) - 1 <= N ; ++ j) {
            int l = (1 << (i - 1));
            RMQ[i][j] = GCD(RMQ[i - 1][j], RMQ[i - 1][j + l]);
        }
    }
    for(int i = 1 ; i + W - 1 <= N ; ++ i) {
        int lg = Log[W];
        B[i] = GCD(RMQ[lg][i], RMQ[lg][i + W - (1 << lg)]);
    }
}

int T, N, M, H, W;
int RMQ[MAXN][MAXL][MAXN], A[MAXN][MAXN], B[MAXN][MAXN];
int rmqC[MAXL][MAXN], Ans;

inline int buildRMQonColumns(int column, int M, int H) {
    for(int i = 1 ; i <= M ; ++ i)
        rmqC[0][i] = B[i][column];
    for(int i = 1 ; (1 << i) <= M ; ++ i)
        for(int j = 1 ; j + (1 << i) - 1 <= M ; ++ j) {
            int l = (1 << (i - 1));
            rmqC[i][j] = GCD(rmqC[i - 1][j], rmqC[i - 1][j + l]);
        }
    for(int i = 1 ; i + H - 1 <= M ; ++ i) {
        int lg = Log[H];
        Ans = max(Ans, GCD(rmqC[lg][i], rmqC[lg][i + H - (1 << lg)]));
    }
}

inline void Solve(int tst) {
    fin >> M >> N >> H >> W;
    for(int i = 1 ; i <= M ; ++ i) {
        for(int j = 1 ; j <= N ; ++ j)
            fin >> A[i][j];
        buildRMQonLine(A[i], RMQ[i], N, W, B[i]);
    }
    Ans = 0;
    for(int i = 1 ; i <= N ; ++ i)
        buildRMQonColumns(i, M, H);
    fout << "Case #" << tst << ": " << Ans << '\n';
}

int main() {
    buildLog(MAXN);
    fin >> T;
    for(int test = 1 ; test <= T; ++ test)
        Solve(test);
    fin.close();
    fout.close();
    return 0;
}
