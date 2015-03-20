#include <fstream>

using namespace std;

ifstream cin("bursa.in");
ofstream cout("bursa.out");
long long n, s, v[100000], i, actiuni, castig, aux;
int main()
{
    cin>>n>>s;
    for(i=1;i<=n;++i)
        cin>>v[i];
    aux=s;
    for(i=2;i<n;++i)
        if(v[i]<=v[i-1] && v[i]<=v[i+1])
            actiuni+=(s/v[i]), s=(s-s/v[i]);
        else if(v[i]>=v[i-1] && v[i]>=v[i+1])
            s+=(actiuni*v[i]), actiuni=0;
    s+=(actiuni*v[n]);
    cout<<s-aux<<" ";
    cin.close();
    cout.close();
    return 0;
}
