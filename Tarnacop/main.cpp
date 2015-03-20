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

string file = "tarnacop";

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

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

Graph G, Gt;
int N, M, S, D, nrc, where[MAXN];
bitset <MAXN> Used;
vector <int> discovered;

void DFs(const int &Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it);
    discovered.push_back(Node);
}

void DFs2(const int &Node, const int &act) {
    Used[Node] = true;
    where[Node] = act;
    for(It it = Gt[Node].begin(), fin = Gt[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs2(*it, act);
}

int main() {
    cin >> N >> M >> S >> D;
    vector<pair<int, int> > v;
    for(int i = 1 ; i <= M ; ++ i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(c == 0)
            continue;
        if( d > 0 ) {
            G[b].push_back(a);
            Gt[a].push_back(b);
        }
        if(c != d) {
            G[a].push_back(b);
            Gt[b].push_back(a);
        }
        else v.push_back(make_pair(a, b));
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFs(i);
    Used.reset();
    for(vector <int> :: reverse_iterator it = discovered.rbegin(), fin = discovered.rend();
        it != fin ; ++ it)
            if(!Used[*it])
                DFs2(*it, ++nrc);
    vector <pair<int, int> > Ans;
    for(int i = 0 ; i < v.size() ; ++ i)
        if(where[v[i].first] != where[v[i].second])
            Ans.push_back(v[i]);
    sort(Ans.begin(), Ans.end());
    cout << Ans.size() << '\n';
    for(int i = 0 ; i < Ans.size() ; ++ i)
        cout << Ans[i].first << ' ' << Ans[i].second << '\n';
    return 0;
}
