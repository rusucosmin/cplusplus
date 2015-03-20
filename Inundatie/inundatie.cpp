#include<fstream>
#include<algorithm>

using namespace std;
int a, b, n, i, e[10000001],T, t ;
ifstream cin("inundatie.in");
ofstream cout("inundatie.out");

int cautbin(int b)
{
    int li=1,ls=n,mij,fin;
    while(li<=ls)
    {
    mij=(li+ls)/2;
    if (e[mij]>=b)
    {
        fin=mij;
        ls=mij-1;
    }
    else
    li=mij+1;
    }
    return fin;
}

bool cmp(int a , int b)
{   if(a>b) return 0;
else return 1;
}

int main()
{
    cin>>a>>b;
    n=a*b;
    for(i=1;i<=n;i++)
        cin>>e[i];
    sort(e+1, e+n+1, cmp);
    cin>>T;
    for(i=1;i<=T;i++)
    {      cin>>t;
           cout<<(n-cautbin(t))<<"\n";
    }
    return 0;
}
