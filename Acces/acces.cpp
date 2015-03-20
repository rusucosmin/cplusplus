#include<fstream>
#define max(A,B)	( (A) > (B) ? (A):(B))
using namespace std;
ifstream cin("acces.in");
ofstream cout("acces.out");
int a[100][100], i, j,l, c,q, x,y;

int main()
{
    cin>>l>>c;
    for(i=1;i<=l;i++)
                     for(j=1;j<=c;j++)
                                 {     cin>>a[i][j];
                                      if(a[i][j]==1)
                                        a[i][j]=0;
                                      else a[i][j]=1; }
    j=1;
    for(i=1;i<=l;i++)
      for(j=1;j<=c;j++)
      if(a[i][j]>=1)
          {if(a[i][j+1]>=1) a[i][j+1]=a[i][j]+1;
           if(a[i+1][j]>=1) a[i+1][j]=a[i][j]+1;
           if(a[i-1][j-1]==0&&i>=1&&j>=1&&a[i-1][j]>=1&&a[i][j-1]>=1)
               a[i][j]=a[i-1][j]+a[i][j-1];
                                               
                           }   
           

    for(i=1;i<=l;i++)
                   { for(j=1;j<=c;j++)
                                    cout<<a[i][j]<<" ";
                    cout<<"\n";}
    cin>>q;
    for(i=1;i<=q;i++)
                     { cin>>x>>y;
                      cout<<a[x][y]<<"\n";
                          }
             
    
    
    
    
    return 0;    
} 
