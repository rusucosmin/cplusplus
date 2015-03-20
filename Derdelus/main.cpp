#include <fstream>
using namespace std;
ifstream cin("derdelus.in");
ofstream cout("derdelus.out");
int n, m, p, x, y, i, j, k, a[1055][1055], sum[1055][1055], sum2[1055][1055];
int main()
{
    cin>>n>>m>>p;
    for(i=1;i<=p;i++)
       {
           cin>>x>>y;
           a[x][y]=-1;
        }
   a[1][1]=1;
   for(i=1;i<=n;i++)
                    for(j=1;j<=i;j++)
                         for(k=1;k<=m;k++)
                                          if(a[i][j]!=-1)
        {
           sum[i][j]=(sum[i][j]+sum[i+k][j]+1)%666013;

           // sum2[i+k][j]=(sum2[i-1][j-1] + a[i][j])%666013;
            }
    for(i=1;i<=n;i++)
        {for(j=1;j<=i;j++)
                cout<<sum[i][j];
            cout<<"\n";}
    for(i=2;i<=n;i++)
       for(j=1;j<=i;j++)
         if(a[i][j]!=-1)
         for(k=1;k<=m;k++)
            {
                if(a[i-k][j]!=-1 && i-k>0) a[i][j]=(a[i][j]+a[i-k][j])%666013;

                if(a[i-k][j-k]!=-1 && i-k>0 && j-k>0) a[i][j]=(a[i][j]+a[i-k][j-k])%666013;

            }

    for(i=1;i<=n;i++)
      if(a[n][i]==-1)
        cout<<0<<" ";
      else
        cout<<a[n][i]<<" ";
    cout<<"\n";


    return 0;
}
