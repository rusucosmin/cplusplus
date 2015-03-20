#include<fstream>
using namespace std;
ifstream cin("pescari.in");
ofstream cout("pescari.out");
int n, m,p, i, j, contor,c,  u, d,y, maxi, l[10005][10005], k=0;
bool ok[10005][10005];
int a[1005][1005];
void init()
{
     //citim datele
     cin>>n>>m>>p;
     for(i=1 ; i<=n ; i++)
            for(j=1 ; j<=m ; j++)
                   { cin>>a[i][j]; 
                     if(a[i][j]==2)
                     { k++;
                     //  sir[1][k]=i;
                      // sir[2][k]=j;
                       l[i][j]=-1; }
                    else { l[i][j]=0; ok[i][j]=0;}
                       }
}
void fill(int X, int Y)
{
     if(l[X][Y]!=-1 && ok[X][Y]==0)
        { l[X][Y]++; ok[X][Y]=1;}

if(Y<m) fill(X, Y + 1);
if(X<n) fill(X + 1, Y);
//if(Y>1) fill(X, Y - 1);
if(X>1) fill(X - 1, Y);
     }
void scriere()
{
     for(i=1;i<=n;i++)
     { cout<<"\n \n";
      for(j=1;j<=m;j++)
       cout<<l[i][j]<<" ";} 
}
int main()
{   
          init();
          scriere();
        ////  for(i=1;i<=n;i++)
            // for(j=1;j<=m;j++)
              // if(l[i][j]==-1) { cout<<"a"<<" "; fill(i, j); }
          fill(1,1);
          return 0;
}
