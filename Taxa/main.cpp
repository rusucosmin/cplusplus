#include <fstream>
#include <queue>
#define DIM 1010
#define INF 40040

using namespace std;

int n, m, i1, i2, j1, j2, i, j, ok, dir, iv, jv;

int di[] = { 0 , 0,-1, 1,-1, 1,-1, 1};
int dj[] = {-1 , 1, 0, 0, 1, 1,-1,-1};
queue<pair<int, int> >Q[6];

int a[DIM][DIM];
int d[DIM][DIM];

int main()
{
    ifstream fin("taxa.in");
    ofstream fout("taxa.out");

    fin>>n>>m>>i1>>j1>>i2>>j2;

    for (i=1; i<=n; i++)
    {
        for (j=1; j<=m; j++)
        {
            fin >> a[i][j];
            d[i][j] = INF;
        }
    }

    for(int i = 1 ; i <= 5; ++ i)
        if( i == a[i1][j1] )
        {
            Q[i].push(make_pair(i1, j1));
            break;
        }
    int cosmin = 0;
    for( d[i1][j1] = 0 ;  ;++cosmin )
    {
        int x, y;
        for(j = 1; j <= 5 ; ++ j)
        {
            if(!Q[j].empty())
                break;
        }
        if(j == 6)
            break;
        x = Q[j].front().first;
        y = Q[j].front().second;
        Q[j].pop();
        for(int i = 0 ; i < 8 ; ++ i)
        {
            int xnou = x + di[i];
            int ynou = y + dj[i];
            if(xnou >= 1 && xnou<=n && ynou >=1 && ynou <= m)
                if(a[x][y] == a[xnou][ynou] && d[xnou][ynou] > d[x][y])
                {
                    d[xnou][ynou] = d[x][y];
                    Q[j].push(make_pair(xnou, ynou));
                }
                else if(a[x][y] != a[xnou][ynou] && d[xnou][ynou] > d[x][y] + a[x][y]*a[xnou][ynou])
                {
                    d[xnou][ynou] = d[x][y] + a[x][y] * a[xnou][ynou];
                    Q[a[xnou][ynou]].push(make_pair(xnou, ynou));
                }

        }
    }
    fout<<d[i2][j2]<<"\n";
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=m; j++)
        {
            fout<<d[i][j]<<" ";
        }
        fout << "\n";
    }
    return 0;
}
