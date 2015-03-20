#include <fstream>
#define DEBUG
using namespace std;

ifstream cin("tsunami.in");
ofstream cout("tsunami.out");

int n, m, h, a[1005][1005], l[1005][1005], i, j, contor, contor_0;
const int di[]={1,-1,0,0},
          dj[]={0,0,1,-1};

void read();
void solve();
void fill(int x, int y);
void write();

int main()
{
    read();
    solve();
    write();
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
                contor_0++;
            l[i][j]=a[i][j];
           }
}
void solve()
{
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(a[i][j]==0)
                fill(i, j);
}
void fill(int x, int y)
{
     char q[3][1000000];
     int st=1, dr=0;
     q[1][dr]=x;
     q[2][st]=y;
     while(st<=dr)
     {
        int i=q[1][st], j=q[2][st];
        for(int k=0;k<=4;++k)
        {
            int ii=i+di[k], jj=j+dj[k];
            if(ii>0 && ii<=n && jj>0 && jj<=m && a[ii][jj]<=h && l[ii][jj]!=-1)
            {
                dr++;
                contor++;
                q[1][dr]=ii; q[2][dr]=jj;
                l[ii][jj]=-1;
            }
        }
        st++;
    }
         
}
void write()
{
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
    cout<<(contor-contor_0)<<"\n";

}
