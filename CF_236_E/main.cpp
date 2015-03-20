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

const int MAXN = 2005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
long long a[MAXN][MAXN];
long long aux[MAXN][MAXN], ans[MAXN][MAXN];

inline void Multiply(long long A[MAXN][MAXN], long long B[MAXN][MAXN], long long C[MAXN][MAXN]) {
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < N ; ++ j)
            for(int k = 0 ; k < N ; ++ k)
                C[i][j] = C[i][j] + 1LL * A[i][k] * B[k][j];
}

inline void lgPow(int P) {
    for(int i = 0 ; i < N ; ++ i)
        ans[i][i] = 1;
    for( ; P ; P >>= 1) {
        if(P & 1) {
            memset(aux, 0, sizeof(aux));
            Multiply(a, ans, aux);
            memcpy(ans, aux, sizeof(aux));
        }
        memset(aux, 0, sizeof(aux));
        Multiply(a, a, aux);
        memcpy(a, aux, sizeof(aux));
    }
}

inline bool check(int x) {
    lgPow(x);
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < N ; ++ j)
            if(ans[i][j] <= 0)
                return false;
    return true;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    cin.sync_with_stdio(false);
    #endif
    cin >> N;
    for(int i = 0 ; i <= N ; ++ i)
        for(int j = 0 ; j <= N ; ++ j)
            cin >> a[i][j];
    int li = 0, mid = 2;
    //while(li <= ls) {
    //    int mid = ((li + ls) >> 1);
        if(check(mid)) {
            cout << "YES\n";
            exit(0);
        }
   //     else ls = mid - 1;
    //}
    cout << "NO\n";
    fin.close();
    fout.close();
    return 0;
}
