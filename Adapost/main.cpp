#include <fstream>
#include <vector>
#include <bitset>
#include <math.h>
#include <cstdio>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <queue>

using namespace std;

const char infile[] = "adapost.in";
const char outfile[] = "adapost.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 405;
const double eps = 0.0001;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, per[MAXN], lef[MAXN], Source, Sink;
double d[MAXN][MAXN], length[MAXN], Capacity[2*MAXN][2*MAXN];
int Father[MAXN], C[2*MAXN][2*MAXN];
bitset <MAXN> used;
pair <double, double> soldier[MAXN], shelter[MAXN];
Graph G;
vector <int> E[MAXN >> 1];
bitset <MAXN> inQ;
queue <int> Q;

inline double euclidianDistance(pair<double, double> a, pair<double, double> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

inline bool buildGraph(const double & x) {
    memset(lef, 0, sizeof(lef));
    memset(per, 0, sizeof(per));
    for(int i = 1 ; i <= N ; ++ i)
        G[i].clear();
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(d[i][j] <= x)
                G[i].push_back(j);
}

bool pairUp(const int & a) {
    if(used[a])
        return false;
    used[a] = true;
    for(It it = G[a].begin(), fin = G[a].end(); it != fin ; ++ it)
        if(!per[*it] || pairUp(per[*it])) {
            per[*it] = a;
            lef[a] = *it;
            return true;
        }
    return false;
}

inline int maximumMatching() {
    int ret = 0;
    for(bool ok = true ; ok ; ) {
        ok = false;
        used.reset();
        for(int i = 1 ; i <= N ; ++ i)
            if(!lef[i] && pairUp(i))
                ok = 1, ++ ret;
    }
    return ret;
}

inline bool Check(const double &x) {
    buildGraph(x);
    return maximumMatching() == N;
}

inline bool bellmanFord() {
    memset(length, oo, sizeof(length));
    inQ.reset();
    for(Q.push(Source), inQ[Source] = 1, length[Source] = 0 ; !Q.empty() ; Q.pop() ) {
        int Node = Q.front();
        inQ[Node] = 0;
        if(Node == Sink)
            continue;
        for(It it = E[Node].begin(), fin = E[Node].end(); it != fin ; ++ it)
            if(C[Node][*it] && length[Node] + Capacity[Node][*it] < length[*it]) {
                length[*it] = length[Node] + Capacity[Node][*it];
                Father[*it] = Node;
                if(!inQ[*it]) {
                    Q.push(*it);
                    inQ[*it] = 1;
                }
            }
    }
    return length[Sink] != oo;
}

inline double minCostFlow() {
    double maxFlow = 0;
    for( ; bellmanFord() ; ) {
        fout << "Da\n";
        for(int i = Sink ; i != Source ; i = Father[i])
            -- C[Father[i]][i] , ++ C[i][Father[i]];
        maxFlow += length[Sink];
    }
    return maxFlow;
}

inline void buildNetwork(const int &maxdistance) {
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(d[i][j] <= maxdistance) {
                E[i].push_back(j + N);
                E[Source].push_back(i);
                E[j + N].push_back(Sink);
                Capacity[i][j + N] = d[i][j];
                Capacity[j + N][i] = -d[i][j];
                C[i][j + N] = 1;
                C[Source][i] = 1;
                C[j + N][Sink] = 1;
            }
}

int main() {
    srand(time(NULL));
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> soldier[i].first >> soldier[i].second;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> shelter[i].first >> shelter[i].second;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            d[i][j] = euclidianDistance(soldier[i], shelter[j]);
    double li = 0, ls = 2000;
    while(ls - li > eps) {
        double mid = (li + ls) / 2;
        if(Check(mid))
            ls = mid;
        else li = mid;
    }
    Source = 0;
    Sink = 2*N + 1;
    buildNetwork(ls);
    fout << fixed << setprecision(5) << ls << ' ' << minCostFlow() << '\n';
    fin.close();
    fout.close();
    return 0;
}
