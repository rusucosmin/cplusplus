#include<fstream>
#include<vector>
#include<cmath>
using namespace std;
ifstream f("petrica.in");
ofstream g("petrica.out");
int sol,x,y,nr,i1,i2,i,j,k,n,d[5],s[222],first[222],last[222],a[222];
vector<int>l[222];
int abs1(int x)
{
    if(x<0)
        return -x;
    return x;
}
void dfs(int x)
{
    first[x]=++nr;
    for(unsigned int i=0; i<l[x].size(); ++i)
        if(!first[l[x][i]])
        {
            dfs(l[x][i]);
            s[x]+=s[l[x][i]];
        }
    last[x]=++nr;
}
int main()
{
    f>>n;
    for(i=1; i<=n; ++i)
        f>>a[i],s[i]=a[i];
    for(i=1; i<n; ++i)
    {
        f>>x>>y;
        l[x].push_back(y);
        l[y].push_back(x);
    }
    dfs(1);
    sol=999999999;
    for (i=2; i<=n-2; ++i)
    {
        for (j=i+1; j<n; ++j)
        {
            for (k=j+1; k<=n; ++k)
            {
                d[1]=s[i];
                d[2]=s[j];
                d[3]=s[k];
                if(first[i]<first[j]&&last[i]>last[j])
                    d[1]-=s[j];
                if(first[i]<first[k]&&last[i]>last[k])
                    d[1]-=s[k];
                if(first[i]<first[j]&&last[i]>last[j]&&first[i]<first[k]&&last[i]>last[k])
                {
                    if(first[j]<first[k]&&last[j]>last[k])
                        d[1]+=s[k];
                    if(first[k]<first[j]&&last[k]>last[j])
                        d[1]+=s[j];
                }
                if(first[j]<first[i]&&last[j]>last[i])
                    d[2]-=s[i];
                if(first[j]<first[k]&&last[j]>last[k])
                    d[2]-=s[k];
                if(first[j]<first[i]&&last[j]>last[i]&&first[j]<first[k]&&last[j]>last[k])
                {
                    if(first[i]<first[k]&&last[i]>last[k])
                        d[2]+=s[k];
                    if(first[k]<first[i]&&last[k]>last[i])
                        d[2]+=s[i];
                }
                if(first[k]<first[i]&&last[k]>last[i])
                    d[3]-=s[i];
                if(first[k]<first[j]&&last[k]>last[j])
                    d[3]-=s[j];
                if(first[k]<first[j]&&last[k]>last[j]&&first[k]<first[i]&&last[k]>last[i])
                {
                    if(first[i]<first[j]&&last[i]>last[j])
                        d[3]+=s[j];
                    if(first[j]<first[i]&&last[j]>last[i])
                        d[3]+=s[i];
                }
                d[4]=s[1]-(d[1]+d[2]+d[3]);
                x=0;
                for(i1=1; i1<=3; ++i1)
                    for(i2=i1+1; i2<=4; ++i2)
                        x=max(x,abs1(d[i1]-d[i2]));
                sol=min(sol,x);
            }
        }
    }
    g<<sol<<'\n';
    return 0;
}
