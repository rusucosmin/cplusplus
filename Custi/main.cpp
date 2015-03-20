#include<fstream>
using namespace std;

ifstream cin("custi.in");
ofstream cout("custi.out");
int D[1010][1010],m[1010][1010],n,i,j,nr[1010],x;
inline int mi(int a,int b)
{
    if(a<b)
        return a;
    return b;
}
int main ()
{
    cin>>n;
    for(i=1;i<=n;++i)
        for(j=1;j<=n;++j)
        {
            cin>>x;
            if(x)
            {
            m[i][j]=mi(m[i-1][j],m[i][j-1])+1;
            D[i][j]=mi(D[i-1][j-1],m[i][j]-1)+1;
            nr[D[i][j]]++;
            }
        }
    for(i=n-1;i>=1;--i)
        {
        nr[i]+=nr[i+1];
        }
    for(i=1;i<=n;++i)
        cout<<nr[i]<<"\n";
    return 0;
}
