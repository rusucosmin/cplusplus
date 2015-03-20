#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <ctime>
#include <utility>

using namespace std;

ifstream cin("petrecere2.in");
ofstream cout("petrecere2.out");

const int N = 100005;

vector < pair<int, bool> > G[N];
bitset < N > colour, viz;

int n, m, fr[2];

void dfs(int node, int c)
{
    viz[node] = 1;
    ++ fr[(c==1)];
    for(vector< pair<int, bool > > :: iterator it = G[node].begin(); it != G[node].end(); ++ it)
        if(!viz[it->first])
        {
            if( it->second == 0 )
                dfs(it->first, c);
            else dfs(it->first, -c);
        }
}

int main()
{
    cin >> n;
    for(cin >> m ; m ; --m)
    {
        int x, y;
        bool op;
        cin >> op >> x >> y;
        G[x].push_back(make_pair(y, op));
        G[y].push_back(make_pair(x, op));
    }
    int sol = 0;
    for(int i = 1 ; i <= n ; ++ i)
        if(!viz[i])
        {
            fr[0] = fr[1] = 0;
            dfs(i, 1);
            sol += max(fr[1], fr[0]);
        }
    cout << sol << "\n";
    return 0;
}
