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

const char infile[] = "pairs.in";
const char outfile[] = "pairs.out";

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, nrdiv[MAXN], sieve[MAXN], maxi, pr[MAXN];
bitset<MAXN> is, only;
long long Ans = 0;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        scanf("%d", &x);
        is[x] = 1;
        maxi = max(maxi, x);
    }
    ///Ans = 1LL * N * (N - 1) / 2;
    for(int i = 2 ; i <= maxi ; ++ i)
        if(!pr[i])
            for(int j = i ; j <= maxi ; j += i)
                ++ pr[j];
    for(int i = 2 ;i * i <= maxi ; ++ i)
        if(pr[i] == 1)
            for(int j = i * i ; j <= maxi ; j += i * i)
                only[j] = 1;
    for(int i = 2 ; i <= maxi ; ++ i)
        if(!only[i])
            for(int j = i ; j <= maxi ; j += i)
                if(is[j])
                    ++ nrdiv[i];
    for(int i = 2 ; i <= maxi ; ++ i)
        if(pr[i] % 2 == 0)
            Ans -= 1LL * nrdiv[i] * (nrdiv[i] - 1) / 2;
        else Ans += 1LL * nrdiv[i] * (nrdiv[i] - 1) / 2;
    printf("%lld\n", 1LL * N * (N - 1) / 2 - Ans);
    return 0;
}
