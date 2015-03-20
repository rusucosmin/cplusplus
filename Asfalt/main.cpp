#include <fstream>
#include <vector>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

const char infile[] = "asfalt.in";
const char outfile[] = "asfalt.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, S, D;
Graph G;
set <int> nb[MAXN];
int c[MAXN][MAXN];
int f[MAXN][MAXN];
vector <int> dist(MAXN, oo), Gr[MAXN];
bitset<MAXN> Used, inQ;
int Father[MAXN], criticEdges;
queue <int> Q;

inline void BuildGraph() {
    for(Q.push(S), dist[S] = 0, inQ[S] = 1 ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(dist[it->first] > dist[Node] + it->second) {
                dist[it->first] = dist[Node] + it->second;
                nb[it->first].clear();
                nb[it->first].insert(Node);
                if(!inQ[it->first]) {
                    Q.push(it->first);
                    inQ[it->first] = 1;
                }
            }
            else if(dist[it->first] == dist[Node] + it->second)
                    nb[it->first].insert(Node);
        inQ[Node] = 0;
    }
    #ifdef debug
    for(int i = 1 ; i <= N ; ++ i)
        fout << dist[i] << ' ';
    #endif
    for(Q.push(D), Used[D] = 1 ; !Q.empty() ; Q.pop()){
        int Node = Q.front();
        for(set<int> :: iterator it = nb[Node].begin(), fin = nb[Node].end() ; it != fin ; ++ it) {
            Gr[Node].push_back(*it);
            Gr[*it].push_back(Node);
            c[*it][Node] = 1;
            if(!Used[*it])
                Q.push(*it), Used[*it] = 1;
        }
    }
}

inline bool BFs() {
    for(Q.push(S), Used.reset(), Used[S] = 1 ; !Q.empty() ; Q.pop() ) {
        int Node = Q.front();
        for(vector<int> :: iterator it = Gr[Node].begin(), fin = Gr[Node].end() ; it != fin ; ++ it)
            if(!Used[*it] && c[Node][*it] - f[Node][*it] > 0) {
                Q.push(*it);
                Father[*it] = Node;
                Used[*it] = 1;
            }
    }
    return Used[D];
}

inline void MaxFlow() {
    for( ; BFs() ; ) {
        ++ criticEdges;
        for(int i = D ; i != S ; i = Father[i])
            -- f[i][Father[i]],
            ++ f[Father[i]][i];
    }
}

inline void PrintResults() {
    fout << criticEdges << '\n';
    for(int i = 1 ; i <= N ; ++ i) {
        for(vector<int> :: iterator it = Gr[i].begin(), fin = Gr[i].end(); it != fin ; ++ it)
        if(Used[i] && !Used[*it] && dist[i] < dist[*it])
            fout << i << ' ' << *it << '\n';
    }

}

int main() {
    fin >> N >> M >> S >> D;
    for(int i = 1 ; i <= M ; ++ i) {
        int a, b, c;
        fin >> a >> b >> c;
        G[a].push_back(make_pair(b, c));
        G[b].push_back(make_pair(a, c));
    }
    BuildGraph();
    MaxFlow();
    PrintResults();
    fin.close();
    fout.close();
    return 0;
}
