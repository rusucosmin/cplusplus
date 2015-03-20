#include<fstream>
using namespace std;
long long hal_mai_mare;
long long numarator;
long long numitor=1;
long long nf, ni, intreg=0, zecimal=0, b=1, aux, a, r, i,bux,cifra;
int cmmdc(int a,int b)
{   int r;
    while(a%b!=0)
     {  r=a%b;
        a=b;
        b=r;}
    return b;
}
int cate_cifre(int x)
{
   if (x==0) return 0;
   else
     return 1+cate_cifre(x/10);
     }

int main()
{
    ifstream cin("numar4.in");
    ofstream cout("numar4.out");
    cin>>ni;
    cin>>nf;

    intreg=0;
    for(i=1;i<=ni;i++)
    {
        cin>>cifra;
        intreg=intreg*10+cifra;
    }
    for(i=1;i<=nf;i++)
    {
        cin>>cifra;
        zecimal=zecimal*10+cifra;
    }
    for(i=1;i<=nf;i++)
        numitor=numitor*10;
    numarator=intreg*numitor+zecimal;

    hal_mai_mare=cmmdc(numarator,numitor);
    intreg=numarator/hal_mai_mare;
    zecimal=numitor/hal_mai_mare;
    cout<<cate_cifre(intreg)<<"\n"<<intreg<<"\n";
    cout<<cate_cifre(zecimal)<<"\n"<<zecimal;
    return 0;
}
