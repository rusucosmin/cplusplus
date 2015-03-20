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

const int MAXN = 10000002;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

bitset <MAXN> enter, exi;
int T, N;

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d", &N);
        int _min = MAXN, _max = 0;
        for(int i = 1 ; i <= N ; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            enter[x] = 1;
            exi[y] = 1;
            _min = min(_min, x);
            _max = max(_max, y);
        }
        int _count = 0;
        int ans = 0;
        for(int i = _min ; i <= _max ; ++ i) {
            if(enter[i]) {
                ++ _count;
                enter[i] = 0;
            }
            if(exi[i]) {
                -- _count;
                exi[i] = 0;
            }
            ans = max(ans, _count);
        }
        printf("%d\n", ans);
    }
    return 0;
}
