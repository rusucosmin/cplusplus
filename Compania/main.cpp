#include<fstream>

using namespace std;

const char iname[]="comp.in";
const char oname[]="comp.out";
const int maxn=16005;

ifstream f(iname);
ofstream g(oname);

int c[maxn],s[maxn],E[maxn][4],i,n,x,y;

void get_sons(int x)
{
    if(x==0)
        return;
    get_sons(E[x][1]);
    get_sons(E[x][2]);
    s[x]=s[E[x][1]]+s[E[x][2]]+1;
}

void calc(int x,int c1,int c2,int c3)
{
    if(E[x][0]==0)
    {
        c[x]=c1;
        return;
    }
    if(E[x][0]==1)
    {
        calc(E[x][1],c2,c3,c1);
        c[x]=c1;
        return;
    }
    if(s[E[x][1]]%3==0)
    {
        calc(E[x][1],c3,c2,c1);
        calc(E[x][2],c2,c3,c1);
        c[x]=c1;
        return;
    }
    if(s[E[x][1]]%3==1)
    {
        calc(E[x][1],c2,c1,c3);
        calc(E[x][2],c3,c1,c2);
        c[x]=c1;
        return;
    }
    if(s[E[x][2]]%3==0)
    {
        calc(E[x][1],c2,c3,c1);
        calc(E[x][2],c3,c2,c1);
        c[x]=c1;
        return;
    }
    calc(E[x][1],c2,c1,c3);
    calc(E[x][2],c3,c2,c1);
    c[x]=c1;
}

int main()
{
    f>>n;
    for(i=1;i<n;++i)
        f>>x>>y,E[y][++E[y][0]]=x;
    get_sons(1);
    calc(1,1,2,3);
    for(i=1;i<=n;++i)
        g<<c[i]<<" ";
    g<<"\n";
}
