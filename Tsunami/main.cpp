#include <fstream>
//#define DEBUG
#include <queue>
using namespace std;

ifstream cin("tsunami.in");
ofstream cout("tsunami.out");
const int dx[]={1, 0, -1, 0};
const int dy[]={0, 1,  0,-1};
int n, m, h, a[1005][1005], i, j, contor, contor_0;
int l[1005][1005];
queue<pair<int, int> > q;
void read();
void solve();
void fill();

int main()
{
    read();
    solve();
    fill();
    cout<<contor<<"\n";
    return 0;
}
void read()
{
    cin>>n>>m>>h;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
           {
            cin>>a[i][j];
            if(a[i][j]==0)
                {
                    contor_0++;
                    l[i][j]=1;
                }
           }
}
void solve()
{
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(a[i][j]==0)
                q.push(make_pair(i, j));
}
void fill()
{
    int xnou, ynou, x, y;
    while(!q.empty())
    {
        x=q.front().first;
        y=q.front().second;
        q.pop();
        for(i=0;i<4;++i)
        {
            xnou=x+dx[i];
            ynou=y+dy[i];
            if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=m)
            if(a[xnou][ynou]<h)
                if(l[xnou][ynou]>l[x][y]+1 || l[xnou][ynou]==0)
                {
                    contor++;
                    l[xnou][ynou]=l[x][y]+1;
                    q.push(make_pair(xnou, ynou));
                }
        }
    }
}
