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

string file = "autobuze";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 50005;
const int MAXA = 10000005;
const int U = 666013;
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

int N, A[MAXN], maxValue, Father[MAXN], paduri;
vector < pair<int, int> > G[U];
bitset <MAXA> is;

inline int key(int Node) {
    return Node % U;
}

inline void Insert(pair<int, int> Value) {
    int Key = key(Value.first);
    G[Key].push_back(Value);
}

inline int Find(int value) {
    int Key = key(value);
    for(int i = 0 ; i < G[Key].size() ; ++ i)
        if(G[Key][i].first == value)
            return G[Key][i].second;
    return 0;
}

int FindPadure(int Node) {
    if(Father[Node] != Node)
        Father[Node] = FindPadure(Father[Node]);
    return Father[Node];
}

inline void Unite(int x, int y) {
    Father[x] = y;
    -- paduri;
}

int main() {
    cin >> N;
    paduri = N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> A[i], Father[i] = i, is[A[i]] = 1;
    sort(A + 1, A+ N + 1);
    maxValue = A[N];
    for(int i = N ; i ; -- i)
        Insert(make_pair(A[i], i));
    for(int i = 1 ; i <= N ; ++ i) {
        int actV = A[i];
        for(int mult = actV + actV ; mult <= maxValue ; mult += actV) {
            if(!is[mult])
                continue;
            int V = Find(mult);
            //is[mult] = 0;
            if(V) {
                //cout << "Gasit multiplu de " << A[i] << " ( " << i << " ) " << " pe domnul : " << mult << " ( " << V << " ) " << '\n';
                int tx = FindPadure(i);
                int ty = FindPadure(V);
                if(tx != ty)
                    Unite(FindPadure(i), FindPadure(V));
            }
        }
    }
    cout << paduri << '\n';
    cin.close();
    cout.close();
    return 0;
}
