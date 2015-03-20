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

const int MAXN = 100;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, Source, Sink;
Graph G;
int C[MAXN][MAXN], F[MAXN][MAXN], Father[MAXN];
bitset <10*MAXN> Used;
queue <int> Q;

inline int getKey(char s) {
    if(isupper(s))
        return s - 'A' + 1;
    return s - '0' + 1 + 'Z' - 'A' + 1;
}

inline bool BFs(Graph &G, int Source, int Sink) {
    Used.reset();
    Q.push(Source);
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Sink == Node)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] - F[Node][*it] > 0) {
                Used[*it] = 1;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline bool BFs2(Graph &G, int Source, int Sink) {
    Used.reset();
    Q.push(Source);
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Sink == Node)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && F[Node][*it] > 0) {
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
            if(!Used[*it] || C[*it][Sink] - F[*it][Sink] <= 0)
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[Father[i]][i] - F[Father[i]][i]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                F[Father[i]][i] += bottleNeck;
                F[i][Father[i]] -= bottleNeck;
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
    char s[30];
    Source = 0;
    Sink = getKey('9') + 1;
    int total = 0;
    for(int test = 1 ; cin.getline(s, 30) ; ++ test) {
        if(strlen(s) == 0) {
            for(char p = '0' ; p <= '9' ; ++ p) {
                G[getKey(p)].push_back(Sink);
                G[Sink].push_back(getKey(p));
                C[getKey(p)][Sink] = 1;
            }
            int maxFlow = getMaxFlow(G, Source, Sink);
            if(maxFlow != total)
                cout << "!\n";
            else {
                BFs2(G, Source, Sink);
                for(char p = '0' ; p <= '9' ; ++ p)
                    if(Used[getKey(p)])
                        cout << char(Father[getKey(p)] + 'A' - 1);
                    else cout << "_";
                cout << "\n";
            }
            total = 0;
            memset(C, 0, sizeof(C));
            memset(F, 0, sizeof(F));
            for(int i = Source ; i <= Sink ; ++ i)
                vector <int>().swap(G[i]);
            continue;
        }
        int last = strlen(s);
        int x = getKey(s[0]);
        //cerr << "X = " << x << '\n';
        G[Source].push_back(x);
        G[x].push_back(Source);
        total += (s[1] - '0');
        C[Source][x] = s[1] - '0';
        for(int ind = 3 ; ind + 1 < last ; ++ ind) {
            int y = getKey(s[ind]);
            //cerr << "Y = " << y << '\n';
            G[x].push_back(y);
            G[y].push_back(x);
            C[x][y] = 1;
        }
    }
    for(char p = '0' ; p <= '9' ; ++ p) {
        G[getKey(p)].push_back(Sink);
        G[Sink].push_back(getKey(p));
        C[getKey(p)][Sink] = 1;
    }
    int maxFlow = getMaxFlow(G, Source, Sink);
    if(maxFlow != total)
        cout << "!\n";
    else {
        BFs2(G, Source, Sink);
        for(char p = '0' ; p <= '9' ; ++ p)
            if(Used[getKey(p)])
                cout << char(Father[getKey(p)] + 'A' - 1);
            else cout << "_";
    }
    return 0;
}
