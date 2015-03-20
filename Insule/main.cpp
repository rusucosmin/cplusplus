#include <fstream>
#include <string.h>
#include<ctype.h>
#include<limits.h>
//#define DEBUG
using namespace std;
ifstream cin("insule.in");
ofstream cout("insule.out");
const int dx[]={1, 0,-1,0};
const int dy[]={0,-1, 0,1};
char c;
int n, m, i, j, a[105][105],k,l[105][105], q[4][10009], contor,R, G, B, u, p, minim=INT_MAX;
void fill(int X, int Y, int s)
{
    if(a[X][Y]==s)
    {
    contor++;
    a[X][Y]=-a[X][Y];
    if(X>1)
        fill(X-1, Y, s);
    if(Y>1)
        fill(X, Y-1, s);
    if(X<n)
        fill(X+1, Y, s);
    if(Y<m)
        fill(X, Y+1, s);
    }
}
void init()
{
    cin>>n>>m;
    cin.get(c);
    for(i=1;i<=n;i++)
        for(j=1;j<=m+1;j++)
            {
                cin.get(c);
                if(c!='\n')
                {
                    a[i][j]=c-'0';
                    if(a[i][j]==1)
                    {
                        k++;
                        l[i][j]=0;
                        q[1][k]=i;
                        q[2][k]=j;
                    }
                }
            }
}
void extr(int &c, int &d)
{
    p=p+1;
    c=q[1][p];
    d=q[2][p];
}
void intr(int c, int d)
{
    u=u+1;
    q[1][u]=c;
    q[2][u]=d;
}
void lee()
{
    int x, y, xnou, ynou;
    u=k;
    p=0;
    while(p!=u)
    {
        extr(x, y);
        for(i=0;i<4;++i)
            {
                xnou=x+dx[i];
                ynou=y+dy[i];
                {

                    if(a[xnou][ynou]==0 && ((xnou>=1 && xnou<=n)&&(ynou>=1 && ynou<=m)))
                    {
                        if( l[xnou][ynou]==0)
                        {
                            l[xnou][ynou]=l[x][y]+1;
                            intr(xnou, ynou);
                        }
                    }
                    else if(a[xnou][ynou]==-2 && ((xnou>=1 && xnou<=n)&&(ynou>=1 && ynou<=m)) && l[x][y])
                            if(minim>l[x][y])
                               minim=l[x][y];
                }
            }
    }

}
void afisare()
{
    cout<<R<<" "<<G<<" "<<B<<" "<<minim<<"\n";
    #ifdef DEBUG
    for(i=1;i<=n;i++)
       {for(j=1;j<=m;j++)
            cout<<a[i][j]<<" ";
        cout<<"\n";}
    for(i=1;i<=n;i++)
       {for(j=1;j<=m;j++)
            cout<<l[i][j]<<" ";
        cout<<"\n";}
    #endif
}
int main()
{
    init();
    for(i=1;i<=n;i++)
       { for(j=1;j<=m;j++)
            if(a[i][j]==1)
                {
                    R++; fill(i, j, 1);
                }
            else if(a[i][j]==2)
                {
                    G++; fill(i, j, 2);
                }
            else if(a[i][j]==3)
                {
                    B++; fill(i, j, 3);
                }
        }
    lee();
    afisare();
    return 0;
}
