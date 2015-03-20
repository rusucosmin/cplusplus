#include<iostream>
using namespace std;
int main()
{
    int a[20][30],b[20][30],i,j,n,m;
    cout<<"n=";
    cin>>n;
    cout<<"m=";
    cin>>m;
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    {cout<<"a["<<i<<"]["<<j<<"]=";
    cin>>a[i][j];}
    
    //afisez matricea a
    cout<<"matricea a: \n";
    for(i=1;i<=n;i++)
      {for(j=1;j<=m;j++)
          cout<<a[i][j]<<" ";
       cout<<endl;
       }
    
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    
    b[j][i]=a[i][j] ;
    
    
    cout<<"matricea b:\n";
    for(i=1;i<=m;i++)
    {for(j=1;j<=n;j++)
    cout<<b[i][j]<<" ";
    cout<<endl;}
    system ("pause");
    return 0;
}
