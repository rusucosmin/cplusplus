#include <fstream>
#include <limits.h>
//#define DEBUG
using namespace std;
ifstream cin("energii.in");
ofstream cout("energii.out");
int n, w[5005], W, j, i, m[5005][10005], v[5005];
int main()
{
    cin>>n;
    cin>>W;
    for(i=1;i<=n;i++)
       cin>>w[i]>>v[i];
    for(i=0;i<=n;i++)
      for(j=0;j<=W;j++)
       m[i][j]=100000000;
    for (i=1;i<=n;++i)
        for (j=1;j<=W;++j)
            if (j >= w[i])
                    m[i][j] = min(m[i-1][j], m[i-1][j-w[i]] + v[i]);
            else
                    m[i][j] = min(m[i-1][j], v[i]);
  #ifdef DEBUG
    for(i=1;i<=n;i++)
     {for(j=1;j<=W;++j)
        cout<<m[i][j]<<" ";

    cout<<"\n";}
  #endif
  if(m[n][W]!=100000000)
        cout<<m[n][W];
   else cout<<"-1\n";
    return 0;
}

