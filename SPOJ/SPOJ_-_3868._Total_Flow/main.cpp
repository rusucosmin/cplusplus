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

const int MAXN = 60;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int Father[MAXN], N;
int C[MAXN][MAXN];
bitset <MAXN> Used;
queue <int> Q;
Graph G;

inline int getKey(char a) {
    if(isupper(a))
        return a - 'A' + 1;
    return a - 'a' + 27;
}

inline bool BFs(Graph &G, int Source, int Sink) {
    Used.reset();
    Q.push(Source);
    Used[Source] = true;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] > 0) {
                Used[*it] = 1;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline int getMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BFs(G, Source, Sink))
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!Used[*it] || C[*it][Sink] <= 0)
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[Father[i]][i]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                C[Father[i]][i] -= bottleNeck;
                C[i][Father[i]] += bottleNeck;
            }
            maxFlow += bottleNeck;
        }
    return maxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        char x, y;
        int z;
        cin >> x >> y >> z;
        if(x != y) {
            G[getKey(x)].push_back(getKey(y));
            G[getKey(y)].push_back(getKey(x));
            C[getKey(x)][getKey(y)] += z;
            C[getKey(y)][getKey(x)] += z;
        }
    }
    cout << getMaxFlow(G, getKey('A'), getKey('Z'));
    return 0;
}
