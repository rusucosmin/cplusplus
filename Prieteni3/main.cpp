#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream cin("prieteni3.in");
ofstream cout("prieteni3.out");

short n, a, k, nr;
vector <int> Graph[105], rang(105, -1);
int sol;
queue <int> Q;

void bfs( int node )
{
    for( Q.push(node), rang[node] = 0; !Q.empty(); Q.pop() )
    {
        int nod = Q.front();
        for(int i = 0 ; i < Graph[nod].size(); ++ i)
            if( rang[Graph[nod][i]] == -1)
            {
                rang[Graph[nod][i]] = rang[nod] + 1;
                if(rang[Graph[nod][i]] == k)
                    ++sol;
                Q.push( Graph[nod][i] );
            }
    }
}
int main()
{
    cin >> n >> a >> k;
    for(int i = 1 ; i <= n ; ++ i)
    {
        cin >> nr;
        for(int j = 1 , x ; j <= nr ; ++ j)
        {
            cin >> x ;
            Graph[i].push_back(x);
            Graph[x].push_back(i);
        }
    }

    if(k == 0)
    {
        cout<<1<<"\n"<<a<<"\n";
        return 0;
    }

    bfs ( a );
    cout << sol << "\n" ;
    for(int i = 1 ; i <= n ; ++ i)
        if(rang[i] == k)
            cout<<i<<" ";

    cin.close();
    cout.close();
    return 0;
}
