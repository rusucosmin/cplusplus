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

const int MAXN = 100005;
const int MAXCH = 31;
const int oo = 0x3f3f3f3f;

typedef set< pair<int, pair<unsigned int, char> > > Graph[MAXN];
typedef set< pair<int, pair<unsigned int, char> > > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M, dp[MAXN][MAXCH];
string start, finish;
map<string, int> Vertex;
Graph G;

#define fin cin
#define fout cout

inline int Dijkstra(const int &st, const int &fn) {
    memset(dp, oo, sizeof(dp));
    queue< pair<int, char> > Q;
    dp[st]['z' + 1 - 'a'] = 0;
    Q.push(make_pair(st, 'z' + 1 - 'a'));
    int Ans = oo;
    while(!Q.empty()) {
        int Node = Q.front().first;
        char lastCh = Q.front().second;
        Q.pop();
        if(Node == fn) {
            Ans = min(Ans, dp[Node][lastCh - 'a']);
            continue;
        }
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(lastCh != it->second.second && dp[it->first][it->second.second - 'a'] > dp[Node][lastCh - 'a'] + it->second.first) {
                dp[it->first][it->second.second - 'a'] = dp[Node][lastCh - 'a'] + it->second.first;
                Q.push(make_pair(it->first, it->second.second));
            }
        }
    }
    return Ans;
}

int main() {
    for(int test = 1 ; ; ++ test) {
        fin >> M;
        if(M == 0)
            return 0;
        fin >> start >> finish;
        Vertex.clear();
        N = 0;
        for(int i = 1 ; i <= M ; ++ i) {
            string a, b, c;
            fin >> a >> b >> c;
            if(!Vertex[a])
                Vertex[a] = ++ N;
            if(!Vertex[b])
                Vertex[b] = ++ N;
            G[Vertex[a]].insert(make_pair(Vertex[b], make_pair(c.size(), c[0])));
            G[Vertex[b]].insert(make_pair(Vertex[a], make_pair(c.size(), c[0])));
        }
        int Ans = Dijkstra(Vertex[start], Vertex[finish]);
        if(Ans == oo)
            fout << "impossivel\n";
        else
        fout << Ans << '\n';
		for(int i = 1 ; i <= N ; ++ i)
			G[i].clear();
    }
    return 0;
}
