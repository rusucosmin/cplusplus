#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream cin("drum-bugetat.in");
ofstream cout("drum-bugetat.out");

unsigned int n, m, b, s, t;

vector <pair <int, int> > G[1005];
vector <int> d(1005, ((1<<31)-1)), total(1005, 0);
queue <int> Q;

int cost[1005];

int main()
{
    cin>>n>>m>>b;
    cin>>s>>t;
    for( int i = 1 ; i <= n ; ++ i )
        cin >> cost[i];
    for( int i = 1 ; i <= m ; ++ i )
    {
        int x, y, c;
        cin>>x>>y>>c;
        G[x].push_back(make_pair(y, c));
        G[y].push_back(make_pair(x, c));
    }
    for( Q.push(s), d[s]=0 ; !Q.empty() ; Q.pop())
    {
        int node = Q.front();
        for( int  i = 0 ; i < G[node].size() ; ++i )
        {
            int length = G[node][i].second;
            int nod = G[node][i].first;

            if( d[nod] > d[node] + length && total[node] + cost[nod] <= b )
            {
                d[nod] = d[node] + length ;
                total[nod] = total[node] + cost[nod] ;
                Q.push ( nod ) ;
            }
            else if(d[nod] == d[node] + length && total[node] + cost[node] < total[nod])
            {
                total[nod] = total[node] + cost[nod] ;
                Q.push ( nod ) ;
            }
        }
    }
    cout<<d[t]<<" "<<total[t]<<"\n";
    cin.close();
    cout.close();
    return 0;
}
