#include <fstream>

using namespace std;

ifstream cin("lac.in");
ofstream cout("lac.out");
bool a[105][105];
int i, j, n, m, q[3][10025],l[105][105], k, u, p, xnou, ynou;
const int dx[]={1, 0, 0, 1, 1};
const int dy[]={0, 1,-1, 1,-1};
void read()
{
    cin>>n>>m;
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j)
            cin>>a[i][j], l[i][j]=-1;
    for(i=1;i<=m;i++)
        if(a[1][i]==0)
            {
                k++;
                q[1][k]=1;
                q[2][k]=i;
            }
}
void intr(int c, int d)
{
    u=u+1;
    q[1][u]=c;
    q[2][u]=d;
}
void extr(int &c, int &d)
{
    p=p+1;
    c=q[1][p];
    d=q[2][p];
}
void lee()
{
    int x, y;
    u=1
    p=0;
    while(p!=u)
    {
        extr(x, y);
        for(i=0;i<5;++i)
            {
                xnou=x+dx[i];
                ynou=y+dy[i];
                if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=m)
                    if(l[xnou][ynou]<l[x][y]+1 || l[xnou][ynou]==-1)
                    {
                        l[xnou][ynou]=l[x][y]+1;
                        intr(xnou, ynou);
                    }
            }

    }


}
int main()
{
    read();
    lee();
    cin.close();
    cout.close();
    return 0;
}
}
