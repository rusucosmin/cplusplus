#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

const char infile[] = "atac2.in";
const char outfile[] = "atac2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 10005;
const int MAXU = 75;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, R, L, X, where[MAXU], C[2*MAXU][2*MAXU], Sink, Source, d[MAXN], Father[MAXN], Mark[MAXN], F[2*MAXU][2*MAXU], Cost[2*MAXN][2*MAXN];
vector <int> G[MAXN];
vector <int> E[2*MAXU];
queue <int> Q;
bitset <MAXN> inQ;

inline void buildDistances(const int &stNode) {
    memset(d, -1, sizeof(d));
    Q.push(stNode);
    d[stNode] = 0;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        for(vector <int> :: iterator it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
            if(d[*it] == -1) {
                d[*it] = d[Node] + 1;
                Q.push(*it);
            }
    }
}

inline void buildNetwork() {
    for(int i = 1 ; i <= R ; ++ i) {
        buildDistances(where[i]);
        for(int j = 0 ; j < L ; ++ j) {
            E[i].push_back(j + 1 + R);
            E[j + 1 + R].push_back(i);
            C[i][j + 1 + R] = 1;
            Cost[i][j + 1 + R] = d[G[X][j]];
            Cost[j + 1 + R][i] = -d[G[X][j]];
        }
    }
}

inline bool BF(const int stNode) {
    memset(d, oo, sizeof(d));
    inQ.reset();
    Q.push(stNode);
    d[stNode] = 0;
    inQ[stNode] = true;
    while(!Q.empty()) {
        int Node = Q.front();
        inQ[Node] = false;
        Q.pop();
        for(vector <int> :: iterator it = E[Node].begin(), fin = E[Node].end(); it != fin ; ++ it) {
            if(C[Node][*it] - F[Node][*it] > 0 && d[*it] > d[Node] + Cost[Node][*it]) {
                d[*it] = d[Node] + Cost[Node][*it];
                Father[*it] = Node;
                if(!inQ[*it]) {
                    Q.push(*it);
                    inQ[*it] = true;
                }
            }
        }
    }
    return (d[Sink] != oo);
}

inline void maximumMatching() {
    int Ans = 0;
    while( BF(Source) ) {
        for(int i = Sink ; i != Source ; i = Father[i]) {
            ++ F[Father[i]][i];
            -- F[i][Father[i]];
        }
        Ans += d[Sink];
    }
    fout << Ans << '\n';
}

int main() {
    fin >> N >> M >> R >> X;
    Source = 0;
    for(int i = 1 ; i <= R ; ++ i) {
        fin >> where[i];
        Mark[where[i]] = i;
        E[0].push_back(i);
        C[0][i] = 1;
    }
    for(int i = 0 ; i < M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    L = G[X].size();
    Sink = R + L + 1;
    for(int i = 0 ; i < L ; ++ i) {
        E[i + 1 + R].push_back(Sink);
        C[i + 1 + R][Sink] = 1;
    }
    buildNetwork();
    maximumMatching();
    fin.close();
    fout.close();
    return 0;
}
