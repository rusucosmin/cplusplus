#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ifstream cin("shop.in");
ofstream cout("shop.out");
vector < pair<long long, long long> > a;
long long A, B[35], n, c, l, f[35], cont;
long long power(long long a, long long b)
{
    long long x=1;
    for(int i=1;i<=b;++i)
        x*=a;
    return x;
}
int main()
{
    cin>>n>>c>>l;
    for(long long i=1;i<=n;++i)
        {
            cin>>A>>B[i];
            a.push_back(make_pair((power(c,A)), i));
        }
    sort(a.begin(), a.end());
    for(int i=n;i>=1, l>0; )
    {
        if(l-a[i].first>=0 && B[a[i].second]>0)
            l-=a[i].first,   f[a[i].second]++, B[a[i].second]--,  cont++;
        else --i;
    }
    cout<<cont<<"\n";
    for(long long i=1;i<=n;++i)
        cout<<f[i]<<" ";
    cin.close();
    cout.close();
    return 0;
}
