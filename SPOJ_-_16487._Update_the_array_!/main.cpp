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

const int MAXN = 10005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, U, Q;
long long aib[MAXN];

inline int lsb(int conf) {
    return conf & (-conf);
}

inline void Update(int pos, long long value) {
    for(int i = pos ; i <= N ; i += lsb(i))
        aib[i] += value;
}

inline long long Query(int pos) {
    long long sum = 0;
    for(int i = pos ; i > 0 ; i -= lsb(i))
        sum += aib[i];
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d %d", &N, &U);
        for(int i = 1 ; i <= U ; ++ i) {
            int x, y;
            long long z;
            scanf("%d %d %lld", &x, &y, &z);
            Update(x + 1, z);
            Update(y + 2, -z);
        }
        scanf("%d", &Q);
        for(int i = 1 ; i <= Q ; ++ i) {
            int x;
            scanf("%d", &x);
            printf("%lld\n", Query(x + 1));
        }
        memset(aib, 0, sizeof(aib));
    }
    return 0;
}
