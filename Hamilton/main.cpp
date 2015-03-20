#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string.h>

using namespace std;

ifstream fin("hamilton.in");
ofstream fout("hamilton.out");

const int maxn = 18;
const int oo = 0x3f3f3f3f;

int n, m, dp[1 << maxn][maxn];
vector <pair<int, int> > gt[maxn];

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        gt[y].push_back(make_pair(x, z));
    }
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    int lim = (1 << n);
    for(int mask = 0 ; mask < lim ; ++ mask)
        for(int i = 0 ; i < n ; ++ i)
            if(mask & (1 << i))
                for(auto it : gt[i])
                    if(mask & (1 << it.first))
                        dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][it.first] + it.second);
    int ans = oo;
    for(auto it : gt[0])
        ans = min(ans, dp[lim - 1][it.first] + it.second);
    if(ans == oo)
        fout << "Nu exista solutie\n";
    else
        fout << ans << '\n';
}
