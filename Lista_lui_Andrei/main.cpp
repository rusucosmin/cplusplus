//Powered by me;
#include<fstream>
#define MOD 104659
using namespace std;
ifstream f("nrcuv.in");
ofstream g("nrcuv.out");
int i,s,j,k,m,n,nr[1001][40],a[40][40];
char c1,c2;
int main()
{
    f>>n>>m;
    for(i=1;i<=m;++i)
    {
        f>>c1>>c2;
        a[c1-96][c2-96]=1;
        a[c2-96][c1-96]=1;
    }
    for(i=1;i<=26;++i)
        nr[1][i]=1;
    for(i=2;i<=n;++i)
        for(j=1;j<=26;++j)
            for(k=1;k<=26;++k)
                if(!a[j][k])
                    nr[i][j]=(nr[i][j]+nr[i-1][k])%MOD;
    for(i=1;i<=26;++i)
        s+=nr[n][i],s%=MOD;
    g<<s<<'\n';
    return 0;
}
