#include <stdio.h>
#include <vector>
#include <bitset>

/// de dragul unui comentariu
using namespace std;

const char infile[] = "pufarina.in";
const char outfile[] = "pufarina.out";

const int MAXN = 50000;
const int BASE = 1000;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int GCD(const int &a, const int &b) {
    if(b == 0)
        return a;
    return GCD(b, a % b);
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    int T, N;
    for(scanf("%d", &T) ; T ; -- T) {
        scanf("%d", &N);
        int x, y;
        scanf("%d.%d", &x, &y);
        int gcd = x * BASE + y;
        for(int i = 2 ; i <= N ; ++i) {
            scanf("%d.%d", &x, &y);
            gcd = GCD(gcd, x * BASE + y);
        }
        int Ans = 100 * BASE / gcd;
        if(Ans > MAXN)
            printf("ALEGERI FRAUDATE\n");
        else
            printf("%d\n", Ans);
    }
    return 0;
}
