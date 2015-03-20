#include <fstream>
#include <algorithm>
using namespace std;
ifstream cin("inundatie.in");
ofstream cout("inundatie.out");
long long a[90005],sum[90005],  q, x, M, s1, s, d, dim ;
int n, i, j;
short m;
bool ok;
int main()
{
    cin>>n>>m;
    n=n*m;
    for(i=1;i<=n;++i)
        { cin>>x;
            if(x) a[++dim]=x;}
    sort(a+1, a+dim+1);
    for(i=1; i<=dim; ++i) sum[i]=a[i]+sum[i-1];
    for(cin>>q;q--;) {
        cin>>x;
        if(x==0) {
            cout<<"0\n";
            continue;
        }
        int p=upper_bound(a+1,a+dim+1,x-1)-a-1;
        cout<<sum[p]+(dim-p)*(x-1)<<'\n';
    }
    return 0;
}
