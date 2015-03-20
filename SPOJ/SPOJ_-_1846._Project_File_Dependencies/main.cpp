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
bitset <MAXN> Used;
vector <int> discovered;
int N, M;

inline void DFs(int Node) {
    Used[Node] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it);
    discovered.push_back(Node);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y;
        for(int j = 1 ; j <= y ; ++ j) {
            cin >> z;
            G[z].push_back(x);
        }
    }
    for(int i = 1 ; i <= N ; ++ i)
        sort(G[i].rbegin(), G[i].rend());
    for(int i = N ; i >= 1 ; -- i)
        if(!Used[i])
            DFs(i);
    vector<int> :: reverse_iterator it = discovered.rbegin();
    cout << *it;
    for( ++ it ; it != discovered.rend() ; ++ it)
        cout << " " << *it;
    cout << "\n";
    fin.close();
    fout.close();
    return 0;
}
