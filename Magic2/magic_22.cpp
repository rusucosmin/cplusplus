#include<fstream>
using namespace std;
int n, a[1001][1001], i, j;
ifstream cin("magic2.in");
ofstream cout("magic2.out");
int main()
{
    cin>>n;
    for(i=1;i<=n;i++) 
       for(j=1;j<=n;j++)
           cin>>a[i][j];
     for(i=1;i<=n;i++)
       {a[n+1][i]=a[n+1][i]+a[i][j];
         for(j=1;j<=n;j++)
             {  a[i][n+1]=a[i][n+1]+a[i][j];
                a[n+1][i]=a[n+1][i]+a[j][i];}}
     
      for(i=1;i<=n+1;i++) 
      { for(j=1;j<=n+1;j++)
           cout<<a[i][j]<<"   ";
           cout<<"\n";}
     
                                                                 
                                                        
    
    
    
    return 0;
}
