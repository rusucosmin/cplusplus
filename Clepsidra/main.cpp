#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <stack>

using namespace std;

const char infile[] = "clepsidra.in";
const char outfile[] = "clepsidra.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int n, m;
int dflevel[MAXN];
int lowlink[MAXN];
stack <pair <int, int> > st;
Graph G;
int bcc[MAXN];
int pow2[MAXN];
bitset <MAXN> critic;

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

inline void extractBCC(int x, int y) {
    int Tx, Ty;
    set<int> actBCC;
    do {
        Tx = st.top().first;
        Ty = st.top().second;
        st.pop();
        actBCC.insert(Tx);
        actBCC.insert(Ty);
    } while(x != Tx || y != Ty);
    for(set <int> :: iterator it = actBCC.begin(), fin = actBCC.end() ; it != fin ; ++ it)
        ++ bcc[*it];
}

void dfs(int node, int father, int actlevel) {
    dflevel[node] = lowlink[node] = actlevel;
    int sons = 0;
    bool critical = false;
    for(It it = G[node].begin(), fin = G[node].end(); it != fin ; ++ it) {
        if(*it == father)
            continue;
        if(!dflevel[*it]) {
            ++ sons;
            st.push(make_pair(node, *it));
            dfs(*it, node, actlevel + 1);
            lowlink[node] = min(lowlink[node], lowlink[*it]);
            if(lowlink[*it] >= dflevel[node]) {
                extractBCC(node, *it);
                critical = true;
            }
        }
        else
            lowlink[node] = min(lowlink[node], dflevel[*it]);
    }
    if(father == -1)
        if(sons < 2)
            critical = false;
        else critical = true;
    critic[node] = critical;
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= m ; i ++ ) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1, -1, 1);
    pow2[0] = 1;
    for(int i = 1 ; i <= n ; i ++ )
        pow2[i] = (pow2[i - 1] * 2) % 666013;
    for(int i = 1 ; i <= n ; i ++ )
        if(!critic[i])
            fout << "0\n";
        else
            fout << pow2[bcc[i]] - 2 << '\n';
    fin.close();
    fout.close();
    return 0;
}
