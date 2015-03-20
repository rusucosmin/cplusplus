#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;

#define MAXN 50005
#define pb push_back
vector<int> graf[MAXN];
vector<int> rgraf[MAXN];
vector<vector<int> > sol;
bitset<MAXN> viz;
bitset<MAXN> viz2;

struct elem
{
    int nod;
    int h;
}term[MAXN];

bool operator<(const elem &a,const elem &b)
{
    if(a.h>b.h)
        return 1;
    return 0;
}

bool cmp(vector<int> a,vector<int> b)
{
    return a<b;
}

int n;
int t;

void rdfs(int nod)
{
    vector<int>::iterator it;
    for(it=rgraf[nod].begin();it!=rgraf[nod].end();it++)
        if(!viz[*it])
        {
            viz[*it]=1;
            rdfs(*it);
        }

    term[nod].h=t++;
}

vector<int> curent;
void dfs(int nod)
{
    curent.push_back(nod);
    vector<int>::iterator it;
    for(it=graf[nod].begin();it!=graf[nod].end();it++)
        if(!viz2[*it])
        {
            viz2[*it]=1;
            dfs(*it);
        }
}

int main()
{
    int m,i,a,b;
    cin>>n>>m;

    for(i=1;i<=m;i++)
    {
        cin>>a>>b;
        graf[a].pb(b);
        rgraf[b].pb(a);
    }

    for(i=1;i<=n;i++)
    {
        term[i].nod=i;
        if(!viz[i])
        {
            viz[i]=1;
            rdfs(i);
        }
    }

    sort(term+1,term+n+1);
    for(i=1;i<=n;i++)
    {
        if(!viz2[term[i].nod])
        {
            curent.clear();
            viz2[term[i].nod]=1;
            dfs(term[i].nod);
            sort(curent.begin(),curent.end());
            sol.push_back(curent);
        }
    }
    cout<<sol.size()<<'\n';
    vector<vector<int> >::iterator it;
    vector<int>::iterator it2;
    for(it=sol.begin();it!=sol.end();it++) {
        cout<<it->size()<<' ';
        sort(it->begin(),it->end());
        for(it2=it->begin();it2!=it->end();it2++)
            cout<<*it2<<' ';
        cout<<'\n';
    }

    return 0;
}
