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

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, dp[MAXN];
bitset <MAXN> inQ;

void BellmanFord(int stNode) {
    queue <int> Q;
    memset(dp, oo, sizeof(dp));
    Q.push(stNode);
    dp[stNode] = 0;
    inQ[stNode] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        inQ[Node] = false;
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(dp[it->first] > dp[Node] + it->second) {
                dp[it->first] = dp[Node] + it->second;
                if(!inQ[it->first]) {
                    inQ[it->first] = 1;
                    Q.push(it->first);
                }
            }
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    char s[MAXN];
    for(int i = 2 ; i <= N ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            cin >> s;
            if(s[0] == 'x')
                continue;
            int x = atoi(s);
            //cerr << x << '\n';
            G[i].push_back(make_pair(j, x));
            G[j].push_back(make_pair(i, x));
        }
    }
    BellmanFord(1);
    int Ans = dp[1];
    for(int i = 2 ; i <= N ; ++ i)
        Ans = max(Ans, dp[i]);
    cout << Ans << '\n';
    return 0;
}
