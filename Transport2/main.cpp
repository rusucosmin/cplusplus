#include <fstream>
#include <vector>
#include <queue>

#define LIMIT 100005
#define inf ((1<<31)-1)

using namespace std;

vector< pair<int, int> > G[LIMIT];
vector<int> d(LIMIT);
queue <int> Q;
int n, m;

ifstream cin("transport2.in");
ofstream cout("transport2.out");

char parse[10005], *now;

inline void verify()
{
    if( *now == 0 )
    {
        cin.get(parse, sizeof(parse), '\0');
        now = parse;
    }
}
int get()
{
    while (*now < '0' || *now > '9')
    {
        ++now;
        verify();
    }
    int num = 0;
    while (*now >= '0' && *now <= '9')
    {
        num = num * 10 + (*now - '0');
        ++now;
        verify();
    }
    return num;
}

void dijkstra()
{
    for( Q.push(1), d[1] = inf; !Q.empty(); Q.pop() )
    {
        int nod = Q.front();
        for(int i = 0 ; i < G[nod].size(); ++ i)
        {
            int current = G[nod][i].first;
            int cost = G[nod][i].second;
            if( d[current] < min(d[nod], cost) )
            {
                d[current] = min(d[nod], cost);
                Q.push(current);
            }
        }
    }
}
int main()
{
    now = parse;
    verify();
    n = get();
    m = get();
    for (int i = 1, x, y, z ; i <= m  ; ++ i)
    {
        x = get();
        y = get();
        z = get();
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    dijkstra();
    cout << d[n] << " " ;
    cin.close();
    cout.close();
    return 0;
}
