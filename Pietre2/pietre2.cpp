#include<fstream>
#include<limits.h>
using namespace std;
ifstream cin("pietre2.in");
ofstream cout("pietre2.out");
int n, m, k ,p, u, sir[3][10005], q[3][10005], a[105][105], l[105][105], i, j, maxi=INT_MIN, i_maxi, j_maxi;
void extr(int &c, int &d)
{
     u=u+1;
     if(u>10000)
          u=1;     
     c=q[1][u];
     d=q[2][u];
     }
void intr(int c, int d)
{
     p=p+1;
     if(p>10000)
        p=1;
     q[1][p]=c;
     q[2][p]=d;
     }
void lee(int x, int y, int pr, int ul)
{    p=0; 
     u=0;
     intr(x,y);
     while(p!=u)
     {
                extr(x, y);
     if(x>1)
        if(a[x-1][y]==a[x][y]+1)
           if(l[x-1][y]>l[x][y]+1 || l[x-1][y]==1)
                { l[x-1][y]=l[x][y]+1;
                  intr(x-1, y);
                  if(l[x-1][y]>maxi)
                    {maxi=l[x-1][y];
                     i_maxi=sir[1][pr];
                     j_maxi=sir[2][ul];
                     }
                  }
     if(y>1)
        if(a[x][y-1]==a[x][y]+1)
           if(l[x][y-1]>l[x][y]+1 || l[x][y-1]==1)
                { l[x][y-1]=l[x][y]+1;
                  intr(x, y-1);
                  if(l[x][y-1]>maxi)
                    {maxi=l[x][y-1];
                     i_maxi=sir[1][pr];
                     j_maxi=sir[2][ul];
                     }
                  }
     if(x<n)
        if(a[x+1][y]==a[x][y]+1)
           if(l[x+1][y]>l[x][y]+1 || l[x+1][y]==1)
                { l[x+1][y]=l[x][y]+1;
                  intr(x+1, y);
                  if(l[x+1][y]>maxi)
                    {maxi=l[x+1][y];
                     i_maxi=sir[1][pr];
                     j_maxi=sir[2][ul];
                     }
                  }
     if(y<n)
        if(a[x][y+1]==a[x][y]+1)
           if(l[x][y+1]>l[x][y]+1 || l[x][y+1]==1)
                { l[x][y+1]=l[x][y]+1;
                  intr(x, y+1);
                  if(l[x][y+1]>maxi)
                    {maxi=l[x][y+1];
                     i_maxi=sir[1][pr];
                     j_maxi=sir[2][ul];
                     }
                  } 
}
                  
                     
                    
}
void init()
{
     cin>>n;
     for(i=1;i<=n;i++)
     for(j=1;j<=n;j++)
     { cin>>a[i][j];
      l[i][j]=1;
      if(i==1||j==1||j==n||i==n)
      { k++;
       sir[1][k]=i;
       sir[2][k]=j;
      }
       }
}
int main()
{
    init();
    for(i=1;i<=k;i++)
         lee(sir[1][i],sir[2][i],i,j);
    cout<<maxi-1<<"\n"<<i_maxi<<" "<<j_maxi;

    return 0;    
}
