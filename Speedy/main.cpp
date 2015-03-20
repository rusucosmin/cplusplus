#include <fstream>

using namespace std;

ifstream cin("speedy.in");
ofstream cout("speedy.out");
int a[105][105], l[105][105], q[3][10025], u, p, i, j, n, m, i_st, j_st, v, xnou, ynou;
const int dy[]={1, 0, -1, 0};
const int dx[]={0, 1,  0,-1};
void init()
{
    cin>>n>>m>>i_st>>j_st>>v;
    for(i=1;i<=n;++i)
        for(j=1;j<=n;++j)
            {cin>>a[i][j];l[i][j]=-1;}
    l[i_st][j_st]=v;
    q[1][1]=i_st;
    q[2][1]=j_st;
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
    u=1;
    p=0;
    while(p!=u)
        {
            extr(x, y);
            for(i=0;i<4;++i)
            {
                xnou=x+dx[i];
                ynou=y+dy[i];
                if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=m)
                    {
                        if(a[xnou][ynou]>a[x][y])
                            {
                                if(l[xnou][ynou]<l[x][y]-2*(a[xnou][ynou]-a[x][y])||l[xnou][ynou]==-1)
                                    l[xnou][ynou]=l[x][y]-2*(a[xnou][ynou]-a[x][y])-1, intr(xnou, ynou);
                            }
                        else {  if(l[xnou][ynou]<l[x][y]+(a[xnou][ynou]-a[x][y])||l[xnou][ynou]==-1)
                                    l[xnou][ynou]=l[x][y]+(a[x][y]-a[xnou][ynou])-1, intr(xnou, ynou);
                            }
                    }

            }
        }
}
int main()
{
    init();
    lee();
    for(i=1;i<=n;++i)
        {for(j=1;j<=n;++j)
            cout<<l[i][j]<<" ";
        cout<<"\n";}
    cin.close();
    cout.close();
    return 0;
}
