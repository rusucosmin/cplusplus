//tren
#include<fstream>
#define k 3
using namespace std;
ifstream cin("tren.in");
ofstream cout("tren.out");
int j,n,m, v[50005],i; 
int sum[1001],s[1001][4];    

int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    { cin>>v[i]; sum[i]=sum[i-1]+v[i]; }
    cin>>m;
    for(i=1;i<=n;i++)
                     for(j=1;j<=k;j++)
                                      { s[i][j]=s[i-1][j];
                                        if(s[i][j]<(s[i-m][j-1]+(sum[i]-sum[i-m])) ) 
                                        s[i][j]=s[i-m][j-1]+(sum[i]-sum[i-m]);}
    cout<<s[n][k];   
    
    
    return 0;
}
