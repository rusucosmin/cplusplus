#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

ifstream fin("srevni.in");
ofstream fout("srevni.out");

const int MAX_N = 1000005;

vector<int> G[MAX_N], F(MAX_N);
vector<pair<int, int > > cost;

int n, m;

void dfs(int node, int bst)
{
    F[node] = bst;
    for( vector<int> :: iterator it = G[node].begin(); it != G[node].end(); ++ it )
    {
        if( !F[*it] || F[*it] > bst )
            dfs(*it, bst);
    }
}
int main()
{
    fin >> n >> m;
    for(int i = 1; i <= n ;++ i)
    {
        pair<int, int> p;
        p.second = i;
        fin >> p.first;
        cost.push_back(p);
    }
    for (int i = 1 ; i <= m ; ++ i)
    {
        int X, Y;
        fin >> X >> Y;
        G[Y].push_back(X);
    }
    sort(cost.begin(), cost.end());
    for(int i = 0 ; i < n ; ++ i)
    {
        //fout << cost[i].first << " " << cost[i].second << "\n";
        if( F[cost[i].second] == 0 )
            dfs(cost[i].second, cost[i].first);
        //fout << F[i+1] << " ";
    }
    for(int i = 0 ; i < n ; ++ i)
    {
        //fout << cost[i].first << " " << cost[i].second << "\n";
    //    if(!F[cost[i].second])
      //      dfs(i, cost[i].first);
        fout << F[i+1] << " ";
    }
    fin.close();
    fout.close();
    return 0;
}
