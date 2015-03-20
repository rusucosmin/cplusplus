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

const int MAXN = 105;
const int MAXS = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, depth[MAXN], lowlink[MAXN], Ans;

void DFs(int Node, int Father, int actLevel) {
    depth[Node] = lowlink[Node] = actLevel;
    bool critic = 0;
    int sons = 0;
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
    if(Node == Father)
        if(sons > 1)
            critic = 1;
        else critic = 0;
    Ans += critic;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    cin.sync_with_stdio(false);
    #endif
    string line;
    while(cin >> N) {
        if(!N)
            return 0;
        cin.get();
        while(getline(cin, line)) {
            istringstream ss(line);
            int x;
            ss >> x;
            if(!x) {
                Ans = 0;
                DFs(1, 1, 1);
                cout << Ans << '\n';
                for(int i = 1 ; i <= N ; ++ i) {
                    vector <int>().swap(G[i]);
                    depth[i] = lowlink[i] = 0;
                }
                break;
            }
            int y;
            while(ss >> y) {
                G[x].push_back(y);
                G[y].push_back(x);
            }
        }
    }
    fin.close();
    fout.close();
    return 0;
}
