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

const char infile[] = "becuri.in";
const char outfile[] = "becuri.out";

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

void DFs(int Node) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        DFs(*it);
    if(!G[Node].size()) {
        dp[Node][0] = 1;
        dp[Node][1] = 0;
        for(int i = 2 ; i <= P ; ++ i)
            dp[Node][i] = oo;
        return ;
    }
    vector <int> :: iterator it = G[Node].begin();
    for(int i = 0 ; i <= P ; ++ i)
        aux[i] = nr[arb[*it]][i];
    for(++ it ; it != G[Node].end() ; ++ it) {
        actMin = 200;
        for(vector <int> :: iterator jt = G[Node].end() ; jt <= it ; ++ it) {
            if(aux[*jt] != oo && dp[*it][i - j] != oo)
                actMin = min(actMin, aux[*jt] + dp[*it][it - jt]);
            fin[]
        }
    }
}

int main() {
    fin >> N;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
    }
    DFs(1);
    fin.close();
    fout.close();
    return 0;
}
