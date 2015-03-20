#include<fstream>
using namespace std;
ifstream f("joctv.in");
ofstream g("joctv.out");
int i,j,k,maxi,n,x,s2,mini,s1,s[110],a[110][110];
int main()
{
    f>>n;
    for(i=1;i<=n;++i)
    {
        for(j=1;j<=n;++j)
        {
            f>>x;
            a[i][j]=a[i-1][j]+x;
        }
    }
    maxi=-1000000000;
    for(i=1;i<=n;++i)
    for(j=1;j<=i;++j)
    {
        s1=0;
        s2=0;
        mini=1000000000;
        for(k=1;k<=n;++k)
        {
            s[k]=a[i][k]-a[j-1][k];
            s1+=s[k];
            if(mini>s2)
            mini=s2;
            if(maxi<s1-mini)
            maxi=s1-mini;
            s2+=s[k];
        }
    }
    g<<maxi<<'\n';
    return 0;
}
