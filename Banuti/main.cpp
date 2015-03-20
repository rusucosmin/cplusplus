#include <stdio.h>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>
#include <algorithm>
#include <set>

using namespace std;

const char infile[] = "banuti.in";
const char outfile[] = "banuti.out";

const int MAXN = 5001;
const int oo = 0x3f3f3f3f;

const inline void Get_min(int &a, const int b) {
    if(a > b)
        a = b;
}

int N, minValue = oo, dp[MAXN], value[50001];
int minVal[MAXN];
set <pair<int, int> > Q;
bitset <MAXN> Used;

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d", &N);
    for(int i = 0 ; i < N ; ++ i) {
        scanf("%d", &value[i]);
        if(minValue > value[i])
            minValue = value[i];
    }
    for(int i = 0 ; i < minValue ; ++ i)
        minVal[i] = oo, dp[i] = oo;
    for(int i = 0 ; i < N ; ++ i)
        Get_min(minVal[value[i] % minValue], value[i]);
    Q.insert(make_pair(0, 0));
    dp[0] = 0;
    while(!Q.empty()) {
        int Node = (*Q.begin()).second;
        int cost = (*Q.begin()).first;
        Q.erase(Q.begin());
        if(cost > dp[Node])
            continue;
        for(int i = 0 ; i < minValue ; ++ i) {
            int son = Node + i;
            if(son >= minValue)
                son -= minValue;
            int newcost = cost + minVal[i];
            if(dp[son] > newcost) {
                dp[son] = newcost;
                Q.insert(make_pair(newcost, son));
            }
        }
    }
    int maxi = dp[0];
    for(int i = 1 ; i < minValue ; ++ i)
        if(maxi < dp[i])
            maxi = dp[i];
    if(maxi == oo)
        printf("-1");
    else printf("%d", maxi - minValue);
    return 0;
}
