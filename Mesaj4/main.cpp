#include <fstream>
#include <vector>
#include <bitset>
#define NMAX 100005

using namespace std;

ifstream cin("mesaj4.in");
ofstream cout("mesaj4.out");

vector< int > G[NMAX];
vector< pair<int, int> > sol;

int n, m;

bitset <NMAX> viz;
void dfs(int nod)
{
    viz[nod] = 1;
    for(vector<int> :: iterator it = G[nod].begin(), fin = G[nod].end(); it!=fin; ++ it)
        if(!viz[*it])
        {
            sol.push_back(make_pair(nod, *it));
            dfs(*it);
        }
}
int main()
{
    cin >> n >> m;
    for(int i = 1; i  <= m ; ++i )
    {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs (1);
    for(int i = 1 ; i <= n ; ++ i)
        if(!viz[i])
        {
            cout<<"-1\n";
            return 0;
        }
    cout << ((n-1)<<1) <<"\n";
    for(vector<pair<int, int > > :: iterator it = sol.end() - 1 , fin = sol.begin()-1 ; it != fin ; -- it)
        cout << it->second << " " << it->first << "\n";
    for(vector<pair<int, int > > :: iterator it = sol.begin(), fin = sol.end() ; it != fin ; ++ it)
        cout << it->first << " " << it->second << "\n";
    cin.close();
    cout.close();
    return 0;
}
