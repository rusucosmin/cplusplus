#include <fstream>
#include <algorithm>
using namespace std;

ifstream cin("filme.in");
ofstream cout("filme.out");
long long n, m, nr, a[100005], i, s, ct;
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;++i)
    {
        cin>>a[i];
        cin>>nr;
        nr+=a[i];
    }
    sort(a+1, a+n+1);
    for(i=n;i>=1;--i)
        if(s+a[i]<=m)
            s+=a[i], ct++;
    cout<<ct<<"\n";
    cin.close();
    cout.close();
    return 0;
}
