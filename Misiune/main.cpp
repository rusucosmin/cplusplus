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

const char infile[] = "misiune.in";
const char outfile[] = "misiune.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const unsigned long long oo = 0x3f3f3f3f;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Edge {
    int nxt, t, c;
    Edge(int _nxt, int _t, int _c) {
        nxt = _nxt;
        t = _t;
        c = _c;
    }
};

struct State {
    unsigned long long cost;
    int Node;
    int remCap;
    State(unsigned long long _cost, int _Node, int _remCap) {
        cost = _cost;
        Node = _Node;
        remCap = _remCap;
    }
};

typedef vector<Edge> Graph[MAXN];
typedef vector<Edge> :: iterator It;

int N, M, K, S, D, Level[MAXN], lowLink[MAXN];
int Father[MAXN];
unsigned long long dp[MAXN];
vector <int> Ships;
Graph G;
bitset <MAXN> Critic;

void DFs(const int &Node, const int &Father, const int &ActLevel) {
    Level[Node] = ActLevel;
    lowLink[Node] = ActLevel;
    bool critic = false;
    int sons = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(it->nxt == Father)
            continue;
        if(!Level[it->nxt]) {
            ++ sons;
            DFs(it->nxt, Node, ActLevel + 1);
            lowLink[Node] = min(lowLink[Node], lowLink[it->nxt]);
            critic |= (lowLink[it->nxt] >= Level[Node]);
        }
        else lowLink[Node] = min(lowLink[Node], Level[it->nxt]);
    }
    //fout << Node << ' ' << critic << ' ' << Father << ' ' << sons << '\n';
    if((Node != Father && critic) || (Father == Node && sons > 1))
        Critic[Node] = true;
}

inline unsigned long long getMinimumTime(const int &capacity) {
    queue <State> Q;
    memset(dp, oo, sizeof(dp));
    Q.push(State(1, S, capacity));
    dp[S] = 1;
    while(!Q.empty()) {
        unsigned long long cost = Q.front().cost;
        int Node = Q.front().Node;
        int cap = Q.front().remCap;
        if(Critic[Node])
            cap = capacity;
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(cap - it->c < 0)
                continue;
            if(cost * it->t < cost)
                continue;
            if(dp[it->nxt] > cost * it->t) {
                Father[it->nxt] = Node;
                dp[it->nxt] = cost * it->t;
                Q.push(State(dp[it->nxt], it->nxt, cap - it->c));
            }
        }
    }
    return dp[D];
}

void Write(const int &Node) {
    if(Node == S) {
        fout << S << ' ';
        return;
    }
    Write(Father[Node]);
    fout << Node << ' ';
}

int main() {
    fin >> N >> M >> K;
    fin >> S >> D;
    for(int i = 1 ; i <= K ; ++ i) {
        int x;
        fin >> x;
        Ships.push_back(x);
    }
    sort(Ships.begin(), Ships.end());
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z, d;
        fin >> x >> y >> z >> d;
        G[x].push_back(Edge(y, z, d));
        G[y].push_back(Edge(x, z, d));
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Level[i])
            DFs(i, i, 1);
    unsigned long long TMIN = getMinimumTime(Ships[K - 1]);
    int li = 0, ls = K - 1;
    int Ans = Ships[K - 1];
    while(li <= ls) {
        int mid = ((li + ls) / 2);
        unsigned long long actTime = getMinimumTime(Ships[mid]);
        if(actTime == TMIN) {
            ls = mid - 1;
            Ans = Ships[mid];
        }
        else li = mid + 1;
    }
    getMinimumTime(Ans);
    //TMIN %= 1000000;
    //vector <int> ans;
    //for(int i = 0 ; i < 6 ; ++ i) {
    //    ans.push_back(TMIN % 10);
    //    TMIN /= 10;
    //}
    //for(int i = 5 ; i >= 0 ; -- i)
    //    fout << ans[i];
    fout << TMIN;
    fout << ' ' << Ans << '\n';
    Write(D);
    fin.close();
    fout.close();
    return 0;
}
