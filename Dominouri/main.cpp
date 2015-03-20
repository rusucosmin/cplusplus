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

string file = "dominouri";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long N, F[MAXN], Ans[MAXN], Sum[MAXN];
Graph G;
bitset <MAXN> leaf;

void DFs(int Node) {
    vector<long long> actVal;
    for(It it = G[Node].begin(), fin = G[Node].end(); it!= fin ; ++ it) {
        DFs(*it);
        if(!leaf[*it])
            actVal.push_back(Sum[*it]);
        else actVal.push_back(1LL);
    }
    sort(actVal.begin(), actVal.end());
    for(int i = 0 ; i < F[Node] ; ++ i)
        Sum[Node] += actVal[i];
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        cin >> x;
        if(!x) leaf[i] = true;
        else
        for(int j = 1 ; j <= x ; ++ j) {
            int y;
            cin >> y;
            G[i].push_back(y);
        }
    }
    for(int i = 1 ; i <= N ; ++ i)
        cin >> F[i];
    DFs(1);
    //for(int i = 1 ; i <= N ; ++ i)
    //    cout << Sum[i] << ' ';
    cout << Sum[1] << '\n';
    cin.close();
    cout.close();
    return 0;
}
