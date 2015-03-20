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

string file = "muncitori";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;
typedef pair<int, int> pii;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, st[MAXN], fn[MAXN], ind[MAXN], Ans[MAXN];
priority_queue <int, vector<int> , greater_equal <int> > qind;
priority_queue <pii, vector<pii> , greater_equal <pii> > Q;

struct classComp {  inline bool operator () (const int &a, const int &b) const {   return st[a] < st[b];  }  };

int main() {
    cin >> N >> M >> K;
    for(int i = 1 ; i <= M ; ++ i)
        cin >> st[i] >> fn[i], ind[i] = i;
    sort(ind+1, ind+M+1, classComp());
    for(int i = K ; i <= N ; ++ i)
        qind.push(i);
    for(int i = 1 ; i <= M ; ++ i) {
        int a = st[ind[i]];
        int b = fn[ind[i]];
        while(!Q.empty() && Q.top().first <= a) {
            qind.push(Q.top().second);
            Q.pop();
        }
        Ans[i] = qind.top();
        Q.push(make_pair(a + b, qind.top()));
        qind.pop();
    }
    for(int i = 1 ; i <= M ; ++ i)
        cout << Ans[i] << '\n';
    cin.close();
    cout.close();
    return 0;
}
