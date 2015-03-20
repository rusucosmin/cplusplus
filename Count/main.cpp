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

string file = "count";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 30005;
const int oo = (1<<31)-1;

typedef set<int> Graph[MAXN];
typedef set<int> :: iterator It;

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
vector<int> E;
int N, M, Ans[10];

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].insert(y);
        G[y].insert(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(G[i].size() < 6)
            E.push_back(i);
    for(unsigned int i = 0 ; i < E.size() ; ++ i) {
        for(It it = G[E[i]].begin(), fin = G[E[i]].end(), jt = it ; it != fin ; ++ it, jt = it)
            for(++jt ; jt != fin ; ++ jt)
                if(G[*jt].count(*it) > 0) {
                    ++ Ans[0];
                    It kt = jt;
                    for(++ kt ; kt != fin ; ++ kt)
                        if(G[*kt].count(*it) && G[*kt].count(*jt))
                            ++ Ans[1];
                }
        for(It it = G[E[i]].begin(), fin = G[E[i]].end() ; it != fin ; ++ it) {
            G[*it].erase(E[i]);
            if(G[*it].size() == 5)
                E.push_back(*it);
        }
    }
    if(Ans[1])
        cout << "4 " << Ans[1] << '\n';
        else if(Ans[0])
            cout << "3 " << Ans[0] << '\n';
            else cout << "2 " << M << '\n';
    cin.close();
    cout.close();
    return 0;
}
