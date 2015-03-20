#include <fstream>
#include <queue>

using namespace std;

const int dx[]={-1, 1, -1,  1, 0, 1,  0, -1};
const int dy[]={-1, 1,  1, -1, 1, 0, -1,  0};

ifstream cin("rege.in");
ofstream cout("rege.out");

int n, m, l1, c1, l2, c2;
int a[1005][1005], l[1005][1005];

queue < pair <int, int> > Q;
void dfs()
{
    for( Q.push(make_pair(l1, c1)), l[l1][c1] = 0; !Q.empty(); Q.pop())
    {
        int x = Q.front().first;
        int y = Q.front().second;
        for(int i = 0 ; i < 8 ; ++ i)
        {
            int xnou = x + dx[i];
            int ynou = y + dy[i];
            if(xnou >= 1 && xnou <=n && ynou >= 1 && ynou <=m)
                if(a[xnou][ynou] > a[x][y] + 1 || a[xnou][ynou] == 0)
                {
                    a[xnou][ynou] = a[x][y] + 1;
                    l[xnou][ynou] = l[x][y];
                    Q.push(make_pair(xnou, ynou));
                }
                else if ( a[xnou][ynou] == a[x][y] + 1 )
                    ++ l[xnou][ynou];
        }
    }
}
int main()
{
    cin >> n >> m >> l1 >> c1 >> l2 >> c2;
    dfs();
  /*  for(int i = 1 ; i <= n ; ++ i)
        {for(int  j = 1 ; j <= m ; ++ j)
            cout<<l[i][j]<<" ";
        cout<<"\n";}
  */cout << l[l2][c2]+1 << "\n";
    cin.close();
    cout.close();
    return 0;
}
