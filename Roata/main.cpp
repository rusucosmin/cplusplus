#include <fstream>

using namespace std;


long long s;
long long a[365], n, p;
long long  poz_minim;
long long intrat[100005], u, v[100005], poz[100005];
int main()
{
    ifstream cin("roata.in");
    ofstream cout("roata.out");
    cin>>n>>p;
    for(int i=1;i<=p;++i)
            {
                cin>>a[i];
                s+=a[i];
                poz[i]=i;
            }
    cout<<s<<"\n";
    int aux;
    for(int j=n+1;j<=p;++j)
    {
        int minim=(1<<31)-1;
        for(int i=1;i<=n;++i)
            if(minim>a[i])
                minim=a[i], poz_minim=i;
        for(int i=1;i<=n;++i)
                a[i]-=minim;
        cout<<poz[poz_minim]<<" ";
        a[poz_minim]=a[j];
        poz[poz_minim]=j;
    }
    cin.close();
    cout.close();
}
