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

map<string, int> Vertex;
map<int, string> Capital;
set<string> Critical;
Graph G;
int N, M, depth[MAXN], lowlink[MAXN];

void DFs(int Node, int Father, int actLevel) {
    depth[Node] = lowlink[Node] = actLevel;
    int sons = 0;
    bool critic = false;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!depth[*it]) {
            ++ sons;
            DFs(*it, Node, actLevel + 1);
            lowlink[Node] = min(lowlink[Node], lowlink[*it]);
            critic |= (lowlink[*it] >= depth[Node]);
        }
        else lowlink[Node] = min(lowlink[Node], depth[*it]);
    }
    if(Node != Father) {
        if(critic)
            Critical.insert(Capital[Node]);
    } else if(sons > 1)
        Critical.insert(Capital[Node]);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    cin.sync_with_stdio(false);
    #endif
    int test = 0;
    bool start = true;
    while(cin >> N) {
        if(!N)
            return 0;
        string x, y;
        Vertex.clear();
        Capital.clear();
        for(int i = 1 ; i <= N ; ++ i) {
            cin >> x;
            Vertex[x] = i;
            Capital[i] = x;
            vector <int>().swap(G[i]);
            depth[i] = lowlink[i] = 0;
        }
        set<string>().swap(Critical);
        cin >> M;
        if(!start)
            cout << "\n";
        start = false;
        for(int i = 1 ; i <= M ; ++ i) {
            cin >> x >> y;
            G[Vertex[x]].push_back(Vertex[y]);
            G[Vertex[y]].push_back(Vertex[x]);
        }
        for(int i = 1 ; i <= N ; ++ i)
            if(!depth[i])
                DFs(i, i, 1);
        cout << "City map #" << ++ test <<  ": " << Critical.size() << " camera(s) found\n";
        for(set<string> :: iterator it = Critical.begin(), fin = Critical.end(); it != fin ; ++ it)
            cout << *it << '\n';
    }
    return 0;
}
