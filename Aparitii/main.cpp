#include <stdio.h>
#include <vector>
#include <bitset>
#include <string.h>
#include <string>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <math.h>


using namespace std;

const char infile[] = "aparitii.in";
const char outfile[] = "aparitii.out";

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

map <int, int> mp;
int ans, N, K;

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d", &N, &K);
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        scanf("%d", &x);
        ++ mp[x];
    }
    for(map<int, int> :: iterator it = mp.begin(), fin = mp.end(); it != fin && !ans ; ++ it)
        if(it->second % K)
            ans = it->first;
    printf("%d\n", ans);
    return 0;
}
