#include <fstream>
#include <vector>
using namespace std;

ifstream cin ( "berarii2.in" );
ofstream cout ( "berarii2.out" );

vector<int> G[1000005];
int n, m, p, sol;
bool viz[1000005];

void dfs(int nod)
{
        viz[nod] = true;
        --sol;
        for(vector<int>::iterator it = G[nod].begin(), fin = G[nod].end(); it != fin ; ++it)
            if(!viz[*it])
                dfs(*it);
}
int main()
{
    cin >> n >> m >> p;
    sol = n;
    for(int i = 1 ; i <= m ; ++ i)
    {
        int x, y;
        cin >> x >> y;
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= p ; ++ i)
    {
        int x;
        cin >> x;
        if(!viz[x])
            dfs(x);
    }
    cout << sol <<"\n";
    for(int i = 1 ; i <= n ;++ i)
        if(!viz[i])
            cout << i << "\n";
    return 0;
}
