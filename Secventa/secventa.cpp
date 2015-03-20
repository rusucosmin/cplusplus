#include<fstream>
using namespace std;
ifstream cin("secventa.in");
ofstream cout("secventa.out");

int main()
{
    int a[500005],i;
    long long n, k;
    cin>>n>>k;
    for( i=1;i<=n;i++)
       cin>>a[i];
    int maxim, inceput;
    maxim=a[1];
    for(i=1;i<=(n-k)+1;i++)
       if(a[i]>maxim)
          { maxim=a[i];
            inceput=i;
            }
    cout<<inceput<<" "<<(inceput+k-1)<<" "<<maxim<<"\n";    
    
    return 0;
}
