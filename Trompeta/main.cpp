#include<fstream>
using namespace std;
ifstream f("trompeta.in");
ofstream g("trompeta.out");
int n,m,i,c,up;
char st[1000007];
char s[1000005];
int main()
{
    f>>n>>m;
    f>>(s+1);
    up=1;
    st[1]=s[1]-'0';
    for(i=2;i<=n;++i)
    {
        c=s[i];
        while(st[up]<c&&up+n-i>=m&&up)
        --up;
        ++up;
        st[up]=c;
    }
    g<<(st+1);
    return 0;
}
