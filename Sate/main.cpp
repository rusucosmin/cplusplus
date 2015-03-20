#include <fstream>
#include <vector>
#include <stdio.h>
#include <queue>

#define limit 30005

using namespace std;

vector < pair< int, int> > G[limit];
vector < int > d(limit, -1);
queue < int > Q;
int n, m, x, y, z;
int a, b, c;

void bfs()
{
    Q.push(x);
    d[x]=0;
    for( ; !Q.empty() ; Q.pop())
    {
        int aux=Q.front();
        for(int i = 0 ; i < G[aux].size(); ++ i)
        {
            int node = G[aux][i].first;
            int cost= G[aux][i].second;
            if(d[node] == -1)
            {
                d[node]=d[aux]+cost;
                Q.push(node);
            }
        }
    }

}

int main()
{
    //READ
    freopen("sate.in", "r", stdin);
    freopen("sate.out", "w", stdout);
    scanf("%d %d %d %d", &n, &m, &x, &y);
    for(unsigned int i = 1 ; i <= m ; ++ i)
    {
        scanf("%d %d %d", &a, &b, &c);
        G[a].push_back(make_pair(b, c));
        G[b].push_back(make_pair(a, -c));
    }
    //BFS
    bfs();
    printf("%d ", d[y]);
    return 0;
}
