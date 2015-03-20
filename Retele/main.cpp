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
#include <deque>

using namespace std;

const char infile[] = "retele.in";
const char outfile[] = "retele.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G, Gt;
int N, M;
vector <int> dicovered;
bitset <MAXN> Used;
set <set <int> > CTC;
set <int> act;

inline void DFsPlus(int Node) {
    Used[Node] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFsPlus(*it);
    dicovered.push_back(Node);
}

inline void DFsMinus(int Node) {
    act.insert(Node);
    Used[Node] = 0;
    for(It it = Gt[Node].begin(), fin = Gt[Node].end(); it != fin ; ++ it)
        if(Used[*it])
            DFsMinus(*it);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        Gt[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFsPlus(i);
    reverse(dicovered.begin(), dicovered.end());
    for(auto i: dicovered) {
        if(Used[i]) {
            DFsMinus(i);
            CTC.insert(act);
            act.clear();
        }
    }
    fout << CTC.size() << '\n';
    for(auto comp : CTC) {
        fout << comp.size() << ' ';
        for(auto it : comp)
            fout << it << ' ';
        fout << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}
