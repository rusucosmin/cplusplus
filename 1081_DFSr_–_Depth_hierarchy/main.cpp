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

const int MAXN = 25;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M;
bool ok;
Graph G;
bitset <MAXN> Used;

#define fin cin
#define fout cout

inline void DFs(const int &Node, const int &actLevel, const int &Father) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        //if(*it != Father)
        {
        string actStr = "";
        stringstream ss;
        ss << Node;
        string strNode = ss.str();
        stringstream ii;
        ii << *it;
        string itrNode = ii.str();
        for(int j = 1 ; j <= actLevel ; ++ j)
            actStr += "  ";
        actStr += strNode;
        actStr.push_back('-');
        actStr += itrNode;
        if(!Used[*it]) {
            if(!ok) {
                ok = true;
                fout << '\n';
            }
            actStr += " pathR(G,";
            actStr += itrNode;
            actStr += ")";
        }
        fout << actStr << '\n';
        if(!Used[*it])
            DFs(*it, actLevel + 1, Node);
    }
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        for(int i = 0 ; i <= N ; ++ i)
            G[i].clear();
        Used.reset();
        fin >> N >> M;
        for(int i = 1 ; i <= M ; ++ i ){
            int x, y;
            fin >> x >> y;
            G[x].push_back(y);
            //G[y].push_back(x);
        }
        fout << "Caso " << test << ":";
        for(int i = 0 ; i < N ; ++i)
            if(!Used[i]) {
                ok = false;
                DFs(i, 1, -1);
            }
        fout << '\n';
    }
    return 0;
}
