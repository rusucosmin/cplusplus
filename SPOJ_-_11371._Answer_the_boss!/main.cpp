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
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
set<int> R[MAXN];
int deg[MAXN], dist[MAXN];
int N, M, T;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    memset(dist, oo, sizeof(dist));
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> N >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            cin >> x >> y;
            G[y + 1].push_back(x + 1);
            ++ deg[x + 1];
        }
        queue <int> Q;
        for(int i = 1 ; i <= N ; ++ i)
            if(!deg[i]) {
                Q.push(i);
                dist[i] = 1;
            }
        while(!Q.empty()) {
            int Node = Q.front();
            R[dist[Node]].insert(Node);
            Q.pop();
            for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
                -- deg[*it];
                if(!deg[*it]) {
                    dist[*it] = dist[Node] + 1;
                    Q.push(*it);
                }
            }
        }
        cout << "Scenario #" << test << ":\n";
        for(int i = 0 ; i <= N ; ++ i) {
            for(set<int> :: iterator it = R[i].begin(), fin = R[i].end(); it != fin ; ++ it)
                cout << i << ' ' << *it - 1 << '\n';
            set<int>().swap(R[i]);
            deg[i] = 0;
            vector <int>().swap(G[i]);
            dist[i] = oo;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
