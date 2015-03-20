#include <fstream>

using namespace std;

ofstream cout("ksecv3.out");
unsigned long long nr, n, k, i, s, sum;
int main()
{
    ifstream cin("ksecv3.in");
   // cin.open();
    cin>>n>>k;
    for(i=1;i<=n;++i)
        cin>>nr, s+=nr;
    if(s%k!=0)
        {
            cout<<"-1\n"; return 0;
        }
    s=s/k;
    cin.close();
    cin.open("ksecv3.in");
    cin>>n>>k;
    for(i=1;i<=n;++i)
        {
            cin>>nr;
            sum+=nr;
            if(sum==s)
                sum=0;
            if(sum>s)
                {cout<<"-1\n"; return 0;}
        }
    cin.close();
    cin.open("ksecv3.in");
    cin>>n>>k;
    for(i=1;i<=n;++i)
        {
            cin>>nr;
            sum+=nr;
            if(sum==s)
                cout<<i<<" ", sum=0;
        }
    cout<<"\n";
    cin.close();
    cout.close();
    return 0;
}
