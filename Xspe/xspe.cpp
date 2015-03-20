#include<fstream>
using namespace std; 

      ifstream cin("xspe.in");
    ofstream cout("xspe.out");
int main()
{
    cin.sync_with_stdio(false);
    long long n, a[1000005], i,j ;
    cin>>n;
    for(i=1;i<=n;i++)
      cin>>a[i];
    for(i=1;i<n;i++)
       for(j=i+1;j<=n+1;j++)
          if(a[i]>a[j])
              {cout<<(a[i]+a[j])<<" ";
               break;}
       cout<<a[n];
    return 0;
}
