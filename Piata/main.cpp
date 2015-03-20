#include <fstream>

using namespace std;

ifstream cin("piata.in");
ofstream cout("piata.out");
int n, iT, jT, iM, jM, s, i, su[40005], j, s1, e1, e2;
int suma_cifre(int x)
{
    int suma=0;
    while(x>=0)
    {
        suma+=x%10;
        x=x/10;
    }
    return suma;
}
int main()
{
    cin>>n;
    cin>>iT>>jT>>iM>>jM;
    s=0;
    for(i=1;i<=n;i++)
        if(i<=9) su[i]=i;
        else su[i]=suma_cifre(i);
    for (j=jT; j<=jM; ++j)
        if (j>=iT) s=s+su[j-iT+1];
            else s=s+su[n+j-iT+1];
    s1=s;
    for(i=iT+1 ; i<=iM ; ++i)
       {
        if (jM>=i-1) e1=su[jM-(i-1)+1];
            else e1= su[n+jM-(i-1)+1];
        if (jT>=i) e2=su[jT-i+1];
            else e2= su[n+jT-i+1];
        s=s+s1-e1+e2;
        s1=s1-e1+e2;
       }
    cout<<s<<"\n";
    cin.close();
    cout.close();
    return 0;
}
