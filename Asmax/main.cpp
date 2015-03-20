#include <fstream>
#include <vector>

#define MAXN 16002

using namespace std;

vector <int> G[MAXN] , value(MAXN) ;
bool viz[MAXN];
int n, sol=-((1<<31)-1), bst[MAXN];

void dfs(int node)
{
    viz[node] = true ;
    bst[node] = value[node];
    for(vector<int>::iterator it = G[node].begin(); it!=G[node].end(); ++ it)
    {
        if( !viz[*it] )
        {
            dfs (*it);
            bst[node] = max ( bst[node], bst[node] + bst[*it]);
        }
    }
    sol = max(sol, bst[node]);
}
int main()
{
    ifstream cin( "asmax.in" );
    ofstream cout( "asmax.out" );
    //read
    cin >> n ;
    for(int i = 1 ; i <= n ; ++ i)
        cin>>value[i];
    for(int i = 1, a, b ; i <= n - 1 ; ++ i)
    {
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1);
    cout<<sol<<"\n";
    cin.close();
    cout.close();
    return 0;
}
