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

const char infile[] = "trib.in";
const char outfile[] = "trib.out";

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

int N, M, dp[MAXN], Answer;
Graph G;

struct classComp{
    inline bool operator () (const int &A, const int &B) {
        return dp[A] < dp[B];
    }
};

void removeFatherEdges(const int &Node, const int &Father) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(*it == Father)
            G[Node].erase(it);
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        removeFatherEdges(*it, Node);
}

void buildDynamic(const int &Node) {
    dp[Node] = 1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        buildDynamic(*it);
    sort(G[Node].begin(), G[Node].end(), classComp());
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        dp[Node] += (dp[*it] >= dp[Node]);
}

inline void Check(int &value, int &maxVal, const int &x) {
    if(value <= x)
        ++ value;
    else maxVal = x;

}

void getAnswerForNewRoot(const int &Node, const int &dadValue) {
    int value = 1, maxVal = -1, ok = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin; ++ it) {
        if(dp[*it] > dadValue && !ok) {
            ok = 1;
            Check(value, maxVal, dadValue);
        }
        Check(value, maxVal, dp[*it]);
    }
    if(!ok)
        Check(value, maxVal, dadValue);
    if(value > Answer)
        Answer = value;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(dp[*it] <= maxVal)
            getAnswerForNewRoot(*it, value);
        else getAnswerForNewRoot(*it, value - 1);
}

int main() {
    fin >> N;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    removeFatherEdges(1, 0);
    buildDynamic(1);
    Answer = dp[1];
    getAnswerForNewRoot(1, 0);
    fout << Answer << '\n';
    fin.close();
    fout.close();
    return 0;
}

                                                                                /**




                                                                                */
