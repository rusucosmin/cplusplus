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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char A[MAXN];
int Pi[MAXN];
int N, K;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(scanf("%s", A + 1)) {
        if(A[1] == '*')
            return 0;
        K = 0;
        N = strlen(A + 1);
        Pi[1] = 0;
        for(int i = 2 ; i <= N ; ++ i) {
            while(K > 0 && A[K + 1] != A[i])
                K = Pi[K];
            if(A[K + 1] == A[i])
                ++ K;
            Pi[i] = K;
        }
        int s = N - Pi[N], ans = 1;
        if(s < N && N % s == 0)
            ans = N / s;
        printf("%d\n", ans);
    }
    return 0;
}
