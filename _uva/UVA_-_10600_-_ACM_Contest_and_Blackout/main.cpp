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

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M, Father[MAXN], dad[MAXN], C[MAXN][MAXN];
bitset <MAXN> Used;
Graph G;

inline int Find(int Node) {
    if(Father[Node] != Node)
        Father[Node] = Find(Father[Node]);
    return Father[Node];
}

inline void BFs(int Source, int Sink) {
    Used.reset();
    queue <int> Q;
    Q.push(Source);
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            return ;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(!Used[*it]) {
                dad[*it] = Node;
                Q.push(*it);
                Used[*it] = 1;
            }
        }
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        vector <pair<int, pair<int, int> > > Edges;
        scanf("%d %d", &N, &M);
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            Edges.push_back(make_pair(z, make_pair(x, y)));
        }
        for(int i = 1 ; i <= N ; ++ i) {
            Father[i] = i;
            vector <int> ().swap(G[i]);
        }
        sort(Edges.begin(), Edges.end());
        int APM1 = 0, APM2 = oo;
        for(vector<pair<int, pair<int, int> > > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
            int Tx = Find(it->second. first);
            int Ty = Find(it->second.second);
            if(Tx == Ty) {
                BFs(it->second.first, it->second.second);
                int actMax = -oo;
                for(int i = it->second.second ; i != it->second.first ; i = dad[i])
                    actMax = max(actMax, C[dad[i]][i]);
                APM2 = min(APM2, it->first - actMax);
                continue;
            }
            Father[Tx] = Ty;
            G[it->second.first].push_back(it->second.second);
            G[it->second.second].push_back(it->second.first);
            C[it->second.first][it->second.second] = it->first;
            C[it->second.second][it->second.first] = it->first;
            APM1 += it->first;
        }
        APM2 += APM1;
        printf("%d %d\n", APM1, APM2);
    }
    fin.close();
    fout.close();
    return 0;
}
