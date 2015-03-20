#include<fstream>
using namespace std;

ifstream cin("dreptunghiuri5.in");
ofstream cout("Dreptunghiuri5.out");
int D[1010][1010],m[1010][1010],n,i,j,nr[1010],x, M;
inline int mi(int a,int b)
{
    if(a<b)
        return a;
    return b;
}
int main ()
{
    cin>>n>>M;
    for(i=1;i<=n;++i)
        for(j=1;j<=M;++j)
        {
            cin>>x;
            if(!x)
            {
            m[i][j]=mi(m[i-1][j],m[i][j-1])+1;
            D[i][j]=mi(D[i-1][j-1],m[i][j]-1)+1;
            nr[D[i][j]]++;
            }
        }
    for(i=1;i<=n;++i)
        {for(j=1;j<=M;++j)
            cout<<m[i][j]<<" ";
        cout<<"\n";}
    for(i=1;i<=n;++i)
        {for(j=1;j<=M;++j)
            cout<<D[i][j]<<" ";
        cout<<"\n";}
    return 0;
}
