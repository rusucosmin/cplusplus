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

const int MAXN = 205;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int G[MAXN][MAXN], deepestNode, depth[MAXN], N;

void DFs(int Node, int actLevel, int father) {
    depth[Node] = actLevel;
    if(depth[Node] > depth[deepestNode])
        deepestNode = Node;
    for(int i = 1 ; i <= N ; ++ i)
        if(G[Node][i] && i != father)
            DFs(i, actLevel + 1, Node);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    vector <pair<int, int> > E;
    for(int i = 1 ; i != N ; ++ i) {
        int a, b;
        cin >> a >> b;
        E.push_back(make_pair(a, b));
        G[a][b] = 1;
        G[b][a] = 1;
    }
    int ans = 0;
    for(vector <pair<int, int> > :: iterator it = E.begin(), fin = E.end(); it != fin ; ++ it) {
        G[it->first][it->second] = 0;
        G[it->second][it->first] = 0;
        deepestNode = it->first;
        DFs(it->first, 0, it->first);
        DFs(deepestNode, 0, deepestNode);
        int first = depth[deepestNode];
        deepestNode = it->second;
        DFs(it->second, 0, it->second);
        DFs(deepestNode, 0, deepestNode);
        int second = depth[deepestNode];
        ans = max(ans, first * second);
        G[it->first][it->second] = 1;
        G[it->second][it->first] = 1;

    }
    cout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
