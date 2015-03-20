#include <fstream>

using namespace std;

ifstream cin("flori.in");
ofstream cout("flori.out");
int n, st[100];
int pval, contor=0;
void afisare(int p)
{
    for(int i=1;i<=p;++i)
        cout<<st[i]<<" ";
    cout<<"\n";
}
void back(int p)
{
    int pval;
    for(pval=st[p-1]+2; pval<=n; pval++)
    {
        st[p]=pval;
        contor++;
    //    afisare(p);
        back(p+1);
    }
}
int main()
{
    st[0]=-1;
    cin>>n;
    back(1);
    cout<<contor;
    cin.close();
    cout.close();
    return 0;
}
