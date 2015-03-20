#include<fstream>
using namespace std;
ifstream cin("ksecv2.in");
ofstream cout("ksecv2.out");
int n, k, i, contor, sacosa, nr;
long long a[3005], b[300005] ;
int main()
{
    cin>>n>>k;
    sacosa=1;
    for(i=1;i<=n;i++)
        cin>>a[i];
    for(i=1;i<=n;i++)
      {if(a[i-1]<=a[i])
           b[sacosa]++;
      else { sacosa++; 
             b[sacosa]=b[sacosa-1]+1;
             }}
    if(b[k])  cout<<b[k]<<"\n";       
           else cout<<"-1\n";
}
