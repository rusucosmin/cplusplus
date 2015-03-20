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
#include <sstream>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int oo = 0x3f3f3f3f;
const int MAXN = 10005;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

map<pair<int, int>, int> C;
int K, N, Father[MAXN];
vector <vector <int> > v;
bitset <MAXN> Used;
queue <int> Q;
Graph G;

inline int in(int x) {
    return x;
}

inline int out(int x) {
    return x + N;
}

inline bool BFs(Graph &G, int Source, int Sink) {
    Used.reset();
    Used[Source] = 1;
    Q.push(Source);
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[make_pair(Node, *it)] > 0) {
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
            if(!Used[*it] || C[make_pair(*it, Sink)] <= 0)
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[make_pair(Father[i], i)]);
            vector <int> act;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                C[make_pair(Father[i], i)] -= bottleNeck;
                C[make_pair(i, Father[i])] += bottleNeck;
                act.push_back(i);
            }
            maxFlow += bottleNeck;
            if(v.size() < K)
                v.push_back(act);
        }
    return maxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    for(int test = 1 ; cin >> K >> N ; ++ test) {
        if(!K && !N)
            return 0;
        cin.get();
        for(int i = 1 ; i <= N ; ++ i) {
            string s;
            int x;
            getline(cin, s);
            stringstream get(s);
            while(get >> x) {
                G[out(i)].push_back(in(x));
                G[in(x)].push_back(out(i));
                C[make_pair(out(i), in(x))] = 1;
            }
            G[in(i)].push_back(out(i));
            G[out(i)].push_back(in(i));
            C[make_pair(in(i), out(i))] = 1;
        }
        int maxFlow = getMaxFlow(G, out(1), in(2));
        cout << "Case " << test << ":\n";
        if(maxFlow >= K) {
            sort(v.begin(), v.end());
            for(int i = 0 ; i < K ; ++ i) {
                cout << 1 << ' ';
                reverse(v[i].begin(), v[i].end());
                for(It it = v[i].begin(), fin = v[i].end(); it != fin ; ++ it)
                    if(*it <= N)
                        cout << *it << ' ';
                cout << '\n';
            }
        }
        else cout << "Impossible\n";
        cout << "\n";
        for(int i = 0 ; i <= 2 * N + 1 ; ++ i)
            vector <int>().swap(G[i]);
        vector <vector <int> > ().swap(v);
        C.clear();
    }
    return 0;
}
