#include <iostream>
#include <fstream>
#include <vector>
#include <tr1/unordered_map>
#include <algorithm>
#define DN 100005
using namespace std;
using namespace tr1;
 
typedef vector<int>::iterator it;
 
unordered_map<int, int> hs[DN];
int n,k,poz[DN],r[DN],cont[DN],c[DN];
vector<int> gi[DN],gf[DN];
 
void dfs(int s, int t) {
    for(it i=gi[s].begin(); i!=gi[s].end(); ++i) if( *i != t ) {
        gf[s].push_back(*i);
        dfs(*i, s);
    }
    if(!gf[s].size()) {
        cont[s]=1;
        r[s]=c[s];
        poz[s]=++k;
        hs[k][c[s]]=1;
        return;
    }
    int fr=gf[s].front();
    r[s]=r[fr]; cont[s]=cont[fr]; poz[s]=poz[fr]; fr=poz[fr];
 
    it i=gf[s].begin();
    for(++i;i!=gf[s].end(); ++i) {
        int f=poz[*i],v;
        for(unordered_map<int,int>::iterator j=hs[f].begin(); j!=hs[f].end(); ++j)
            if((v=(hs[fr][j->first]+=j->second))>cont[s]) {
                cont[s]=v;
                r[s]=j->first;
            }else if(v==cont[s] && j->first<r[s])
                r[s]=j->first;
    }
    if(++hs[fr][c[s]]>cont[s] || (hs[fr][c[s]]==cont[s] && c[s]<r[s])) {
        cont[s]=hs[fr][c[s]];
        r[s]=c[s];
    }
}
 
int main()
{
    ifstream f("egal.in");
    ofstream g("egal.out");
    f>>n;
    for(int i=1; i<n; ++i) {
        int a,b;
        f>>a>>b;
        gi[a].push_back(b);
        gi[b].push_back(a);
    }
    for(int i=1; i<=n; ++i) f>>c[i];
    dfs(1, 0);
    for(int i=1; i<=n; ++i) g<<r[i]<<' '<<cont[i] <<'\n';
    return 0;
}
