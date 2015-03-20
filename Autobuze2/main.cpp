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

const char infile[] = "autobuze2.in";
const char outfile[] = "autobuze2.out";

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
int N, M, B, dp[MAXN];

inline void bfs() {
    queue <int> q;
    memset(dp, -1, sizeof(dp));
    q.push(1);
    dp[1] = 1;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(It it = G[node].begin(), fin = G[node].end() ; it != fin ; ++ it) {
            if(dp[*it] == -1) {
                dp[*it] = dp[node] + 1;
                q.push(*it);
            }
        }
    }
    if(dp[N] == -1) {
        fout << "Iesim la un suc?\n";
        return ;
    }
    fout << dp[N] << '\n';
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
    }
    fin >> B;
    for(int i = 1 ; i <= B ; ++ i) {
        int k, x, y, st;
        fin >> k;
        fin >> x;
        st = x;
        for(int j = 2 ; j <= k ; ++ j) {
            fin >> y;
            G[x].push_back(y);
            x = y;
        }
        G[x].push_back(st);
    }
    bfs();
    fin.close();
    fout.close();
    return 0;
}
