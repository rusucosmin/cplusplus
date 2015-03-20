#include <fstream>
#include <vector>
using namespace std;

ifstream cin("grarb.in");
ofstream cout("grarb.out");

vector<int> G[100005];
int n, m, sol;
bool viz[100005];

void dfs(int node)
{
    viz[node] = 1;
    for(vector <int> :: iterator it = G[node].begin(); it != G[node].end(); ++ it)
        if(!viz[ *it ])
            dfs(*it);
}
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m ; ++ i)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for(int i = 1 ; i <= n ;++ i)
        if(!viz[i])
        {
            ++sol;
            dfs(i);
        }
    cout << m - n + sol << "\n";
    cout << sol - 1 <<'\n';
    cin.close();
    cout.close();
    return 0;
}
