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

string file = "cezar";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 10005;

typedef vector<short> Graph[MAXN];
typedef vector<short> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

short C[MAXN];

struct ClassComp {
    inline bool operator () (const short &a, const short &b) const {
        return C[a] > C[b];
    }
};

Graph G;
int N, K;
priority_queue< short, vector<short> , ClassComp > H;

int main() {
    cin >> N >> K;
    for(short i = 1 ; i != N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    cin.close();
    for(short i = 1 ; i <= N ; ++ i) {
        C[i] = 1;
        if(G[i].size() == 1)
            H.push(i);
    }
    int Sol = 0;
    for(short i = 1 ; i < N - K ; ++ i) {
        short Node = H.top();
        H.pop();
        Sol += (int)C[Node];
        short Father = G[Node].back();
        G[Node].clear();
        G[Father].erase(find(G[Father].begin(), G[Father].end(), Node));
        C[Father] += C[Node];
        if(G[Father].size() == 1)
            H.push(Father);
    }
    cout << Sol << '\n';
    cout.close();
    return 0;
}
