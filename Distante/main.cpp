#include <fstream>
#include <vector>
#include <queue>
#include <string.h>

#define MAXN 50005
#define inf ((1<<31)-1)

using namespace std;

ifstream cin("distante.in");
ofstream cout("distante.out");

int T;
int n, m, s, D[MAXN];

vector < pair<int, int> > G[MAXN];
int d[MAXN];
queue <int> Q;

void dijkstra()
{
    for(int i = 1 ; i <= n ; ++ i)
        d[i]=inf;
    for( Q.push(s), d[s] = 0 ; !Q.empty(); Q.pop() )
    {
        int node = Q.front();
        for(int i = 0 ; i < G[node].size() ; ++ i)
        {
            int cost = G[node][i].second;
            int nod = G[node][i].first;
            if(d[nod]>d[node] + cost)
            {
                d[nod]=d[node]+cost;
                Q.push(nod);
            }
        }
    }
}
int main()
{
    for( cin>>T; T ; -- T )
    {
        cin>>n>>m>>s;
        for( unsigned int i = 1 ; i <= n ; ++ i)
            cin>>D[i];
        for( unsigned int i = 1 , a, b, c ; i <= m ; ++ i)
        {
            cin>>a>>b>>c;
            G[a].push_back(make_pair(b, c));
        }
        dijkstra();
        bool ok = 0;
        for(int i = 1 ; i <= n; ++ i)
        {
            if(d[i] != D[i])
            {
                cout<<"NU\n";
                ok = 1 ;
                i=n+1;
            }
        }

        if( !ok )
        cout<<"DA\n";
    }
    cin.close();
    cout.close();
    return 0;
}
