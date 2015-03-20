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

using namespace std;

string file = "camionas";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 50005;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

Graph G;
int N, M, dp[MAXN], g;
priority_queue <pair <int, int >, vector<pair<int, int> > , greater <pair<int, int> > > Q;

inline void BFs() {
    memset(dp, oo, sizeof(dp));
    dp[1] = 0;
    Q.push(make_pair(0, 1));
    for(; ! Q.empty() ; ) {
        int Node = Q.top().second;
        if(Node == N) {
            cout << dp[N] << '\n';
            return;
        }
        Q.pop();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            int actNode = it->first;
            bool cost = it->second < g;
            if(dp[actNode] > dp[Node] + (cost)) {
                dp[actNode] = dp[Node] + (cost);
                Q.push(make_pair(dp[actNode], actNode));
            }
        }
    }
    cout << dp[N]<< '\n';
}

int main() {
    cin >> N >> M >> g;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    BFs();
    cin.close();
    cout.close();
    return 0;
}
