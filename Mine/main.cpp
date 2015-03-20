#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>
#include <stdio.h>

using namespace std;

string file = "mine";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 10005;
const int MAXW = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, M, W, q[MAXW];
vector <int> D(MAXN, oo);

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return D[a] > D[b];
    }
};

priority_queue< int, vector<int> , ClassComp > Q;

inline int getTime(int X, int Y) {
    while(q[X] < Y && X <= W)
        ++ X;
    return X;
}

inline void BellmanFord() {
    D[1] = 1;
    Q.push(1);
    while(!Q.empty()) {
        int Node = Q.top();
        int Time = D[Node];
        Q.pop();
        //inQ[Node][Time] = 0;
        if(Time > W)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            int newNode = it->first;
            int newTime = getTime(Time, it->second);
            if(newTime > W)
                continue;
            if(newNode == N) {
                 cout << newTime << '\n';
                 exit(0);
            }
            if(D[newNode] > newTime) {
                D[newNode] = newTime;
                Q.push(newNode);
            }
        }
    }
}

int main() {
    freopen("mine.in", "r", stdin);
    freopen("mine.out", "w", stdout);
    scanf("%d %d", &N, &M);
    //cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        //cin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    scanf("%d", &W);
    //cin >> W;
    for(int i = 1 ; i <= W ; ++ i)
        scanf("%d", &q[i]);
        //cin >> q[i];
    BellmanFord();
    cin.close();
    cout.close();
    return 0;
}
