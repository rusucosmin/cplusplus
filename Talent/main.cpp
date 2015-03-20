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

const char infile[] = "talent.in";
const char outfile[] = "talent.out";

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector <pair<int, int> > v;
int T, N;

struct classComp {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.second < b.second || (a.second == b.second && a.first < b.first);
    }
};

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d", &N);
        vector <pair<int, int> > ().swap(v);
        for(int i = 1 ; i <= N ; ++ i) {
            int h1, m1, h2, m2;
            scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);
            if(h2 < h1 || (h2 == h1 && m2 <= m1))
                h2 += 24;
            v.push_back(make_pair(h1 * 60 + m1, h2 * 60 + m2));
        }
        sort(v.begin(), v.end(), classComp());
        int Previous = -oo;
        long long Ans = 0;
        for(vector<pair<int, int> > :: iterator it = v.begin(), fin = v.end(); it != fin ; ++ it) {
            int x = it->first;
            int y = it->second;
            if(x >= Previous) {
                Previous = y;
                Ans += 1LL * (y - x);
            }
        }
        printf("%lld\n", Ans);
    }
    return 0;
}
