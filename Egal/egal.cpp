#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
 
using namespace std;
 
const int maxn = 100005;
 
int n, m, heavy[maxn], leaf[maxn], ansnr[maxn], ansfr[maxn], key[maxn];
vector <int> g[maxn];
unordered_map<int, int> fr[maxn];
 
inline void dfs(int node, int father) {
    int heaviest = -1;
    heavy[node] = 1;
    for(vector <int> :: iterator it = g[node].begin(), fin = g[node].end() ; it != fin ; ++ it) {
        if(*it == father)
            continue;
        dfs(*it, node);
        heavy[node] += heavy[*it];
        if(heaviest == -1)
            heaviest = *it;
		else if(heavy[heaviest] < heavy[*it])
			heaviest = *it;
    }
    if(heaviest == -1) {
        leaf[node] = ++ m;
        ++ fr[leaf[node]][key[node]];
        ansnr[node] = key[node];
        ansfr[node] = 1;
        return ;
    }

    leaf[node] = leaf[heaviest];
 
    ++ fr[leaf[node]][key[node]];
    ansfr[node] = fr[leaf[node]][key[node]];
    ansnr[node] = key[node]; 
     
    for(vector <int> :: iterator it = g[node].begin(), fin = g[node].end() ; it != fin ; ++ it) {
        if(*it == father || *it == heaviest)
            continue;
        for(unordered_map<int, int> :: iterator k = fr[leaf[*it]].begin(), fk = fr[leaf[*it]].end() ; k != fk ; ++ k)
            fr[leaf[node]][k->first] += k->second;
   } 
   for(vector <int> :: iterator it = g[node].begin(), fin = g[node].end() ; it != fin ; ++ it) {
        if(*it == father)
            continue;
        for(unordered_map<int, int> :: iterator k = fr[leaf[*it]].begin(), fk = fr[leaf[*it]].end() ; k != fk ; ++ k)
			if(fr[leaf[node]][k->first] > ansfr[node] ||  (fr[leaf[node]][k->first] == ansfr[node] && k->first < ansnr[node])) {
                ansnr[node] = k->first;
                ansfr[node] = fr[leaf[node]][k->first];
            }
   } 
}
 
int main() {
    ifstream fin("egal.in");
    ofstream fout("egal.out");
    fin >> n;
    for(int i = 1 ; i < n ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 1 ; i <= n ; ++ i)
        fin >> key[i];
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i)
        fout << ansnr[i] << ' ' << ansfr[i] << '\n';
}
