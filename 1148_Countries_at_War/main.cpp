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

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, ctc, where[MAXN], dp[MAXN];
Graph G, Gt, Dag;
bitset <MAXN> used;
vector <int> tsort;

void DFs(const int &Node) {
    used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!used[it->first])
            DFs(it->first);
    tsort.push_back(Node);
}

void DFs2(const int &Node) {
    where[Node] = ctc;
    for(It it = Gt[Node].begin(), fin = Gt[Node].end(); it != fin ; ++ it)
        if(!where[it->first])
            DFs2(it->first);
}

inline int Dijkstra(const int &stNode, const int &fnNode) {
    priority_queue <pair<int, int> , vector <pair<int, int> > , greater <pair<int, int> > > Q;
    memset(dp, oo, sizeof(dp));
    Q.push(make_pair(0, stNode));
    dp[stNode] = 0;
    while(!Q.empty()) {
        int cost = Q.top().first;
        int Node = Q.top().second;
        Q.pop();
        if(dp[Node] < cost)
            continue;
        if(Node == fnNode)
            return cost;
        for(It it = Dag[Node].begin(), fin = Dag[Node].end(); it != fin ; ++ it)
            if(dp[it->first] > cost + it->second) {
                dp[it->first] = cost + it->second;
                Q.push(make_pair(dp[it->first], it->first));
            }
    }
    return oo;
}

//#define fin cin
//#define fout cout

int main() {
    //cin.sync_with_stdio(false);
    while(true) {
        for(int i = 1 ; i <= N ; ++ i) {
            vector < pair<int, int> >().swap(G[i]);
            vector < pair<int, int> >().swap(Gt[i]);
            vector < pair<int, int> >().swap(Dag[i]);
            where[i] = 0;
        }
        used.reset();
        tsort.clear();
        ctc = 0;
        cin >> N >> M;
        if(!N && !M)
            return 0;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            G[x].push_back(make_pair(y, z));
            Gt[y].push_back(make_pair(x, z));
        }
        for(int i = 1 ; i <= N ; ++ i)
            if(!used[i])
                DFs(i);
        for(vector <int> :: reverse_iterator it = tsort.rbegin(), fin = tsort.rend(); it != fin ; ++ it)
            if(!where[*it]) {
                ++ ctc;
                DFs2(*it);
            }
        for(int i = 1 ; i <= N ; ++ i)
            for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
                if(where[i] != where[it->first])
                    Dag[where[i]].push_back(make_pair(where[it->first], it->second));
        int kk;
        cin >> kk;
        for(int i = 1 ; i <= kk ; ++ i) {
            int x, y;
            cin >> x >> y;
            int Ans = Dijkstra(where[x], where[y]);
            if(Ans == oo)
                cout << "Nao e possivel entregar a carta\n";
            else cout << Ans << '\n';
        }
        cout << '\n';
    }
    return 0;
}
