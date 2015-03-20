#include <fstream>
#define Nmax 9005
#define Vmax 7005
using namespace std;

ifstream cin("medie.in");
ofstream cout("medie.out");
int v[Nmax], sol, aux[Vmax],bux[Vmax], n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>v[i], aux[v[i]]++;
    cin.close();
    for(int i=1;i<n;++i)
        for(int j=i+1;j<=n;++j)
            if(((v[i]+v[j])%2)==0)
                bux[(v[i]+v[j])/2]++;
    for(int j=1;j<=n;++j)
            sol+=(bux[v[j]]-aux[v[j]]+1);
    cout<<sol<<"\n";
    cout.close();
    return 0;
}
