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

const char infile[] = "perioada2.in";
const char outfile[] = "perioada2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 10000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char S[MAXN];
int Pi[MAXN], N;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N;
    fin >> (S + 1);
    int K = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        while(K > 0 && S[K + 1] != S[i])
            K = Pi[K];
        if(S[K + 1] == S[i])
            ++ K;
        Pi[i] = K;
    }
    int period = Pi[N];
    int ans = 0;
    while(period) {
        if(N % (N - period) == 0)
            ++ ans;
        period = Pi[period];
    }
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
