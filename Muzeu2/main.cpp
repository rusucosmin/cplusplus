#include <fstream>
using namespace std;
ifstream cin("muzeu.in");
ofstream cout("muzeu.out");
int a[251][251],i,j,ok,u,p,q[3][200001],c,d,y,sir[3][100000],maxi,l[251][251],n,k=0;
char ch;
void citire()
{
    cin>>n;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            {
                cin>>ch;
                if(ch=='.')
                {
                    a[i][j]=1;
                    l[i][j]=-1;
                }
                else if(ch=='P')
                {
                    a[i][j]=10;
                    k++;
                    sir[1][k]=i;
                    sir[2][k]=j;
                }
                else l[i][j]=-2;
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
    p=0;
    u=k;
    while(p!=u)
    {
        extr(x, y);
        if(x>1)
        {
            if(a[x-1][y]==1)
                if(l[x-1][y]>l[x][y]+1||l[x-1][y]==-1)
                {
                    l[x-1][y]=l[x][y]+1;
                    intr(x-1, y);
                }
        }
        if(x<n)
        {
            if(a[x+1][y]==1)
                if(l[x+1][y]>l[x][y]+1||l[x+1][y]==-1)
                {
                    l[x+1][y]=l[x][y]+1;
                    intr(x+1, y);
                }
        }
        if(y>1)
        {
            if(a[x][y-1]==1)
                if(l[x][y-1]>l[x][y]+1||l[x][y-1]==-1)
                {
                    l[x][y-1]=l[x][y]+1;
                    intr(x, y-1);
                }
        }
        if(y<n)
        {
            if(a[x][y+1]==1)
                if(l[x][y+1]>l[x][y]+1||l[x][y+1]==-1)
                {
                    l[x][y+1]=l[x][y]+1;
                    intr(x, y+1);
                }
        }
    }

}
int main()
{
    citire();
    for(i=1;i<=k;i++)
       {
            q[1][i]=sir[1][i];
            q[2][i]=sir[2][i];
       }
    lee();
    for(i=1;i<=n;i++)
        {for(j=1;j<=n;j++)
            cout<<l[i][j]<<" ";
        cout<<"\n";}
    return 0;
}
