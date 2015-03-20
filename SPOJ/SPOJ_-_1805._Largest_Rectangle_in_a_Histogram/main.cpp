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
#include <stack>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

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

int N, M, st[MAXN], dr[MAXN], height[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    while(scanf("%d", &N)) {
        if(!N)
            return 0;
        for(int i = 1 ; i <= N ; ++ i)
            scanf("%d", &height[i]);
        height[0] = height[N + 1] = -1;
        stack <int> sta;
        sta.push(0);
        for(int i = 1 ; i <= N ; ++ i) {
            while(height[sta.top()] >= height[i])
                sta.pop();
            st[i] = i - sta.top();
            sta.push(i);
        }
        while(!sta.empty())
            sta.pop();
        sta.push(N + 1);
        for(int i = N ; i > 0 ; -- i) {
            while(height[sta.top()] >= height[i])
                sta.pop();
            dr[i] = sta.top() - i;
            sta.push(i);
        }
        long long Ans = 0;
        for(int i = 1 ; i <= N ; ++ i)
            Ans = max(Ans, 1LL * height[i] * (dr[i] + st[i] - 1));
        printf("%lld\n", Ans);
    }
    return 0;
}
