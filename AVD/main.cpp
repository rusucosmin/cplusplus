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

string file = "avd";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 14;
const int oo = (1<<31)-1;

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

int Total, N, conNum[MAXN], conComp;
set < vector <int> > partNum;
bitset <MAXN> Used;
vector<int> actPart;
Graph G;

inline void Read() {
    cin >> N;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(make_pair(y, i-1));
        G[y].push_back(make_pair(x, i-1));;
    }
}

inline void DFs(int Node, int actCon, int Conf) {
    Used[Node] = true;
    ++ conNum[actCon];
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[it->first] && !(Conf & (1<<it->second)))
            DFs(it->first, actCon, Conf);
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[it->first] && (Conf & (1<<it->second)))
            DFs(it->first, ++ conComp, Conf);
}

inline void BuildPartitions() {
    /// in reprezentarea binara a lui Conf bitul k este 1 daca a k - a muchia nu este eleminata si 0 daca este eliminata
    for(int Conf = 0 ; Conf < ( 1 << (N - 1)) ; ++ Conf) {
        conComp = 1;
        DFs(1, 1, Conf);
        for(int i = 1 ; i <= N ; ++ i)
            if(conNum[i])
                actPart.push_back(conNum[i]);
        sort(actPart.begin(), actPart.end());
        partNum.insert(actPart);
        memset(conNum, 0, sizeof(conNum));
        Used.reset();
        actPart.clear();
    }
}

inline void Back(int Sum, int Last) {
    if(Sum > N || Sum < 0)
        return;
    if(Sum == N) {
        ++ Total;
        return;
    }
    for(int i = Last ; i <= N ; ++ i)
        Back(Sum + i, i);
}

int main() {
    int T;
    for(cin >> T ; T ; -- T) {
        Read();
        BuildPartitions();
        Total = 0;
        Back(0, 1);
        cout << fixed << setprecision(5) << (double)partNum.size() / (double)Total << '\n';
        for(int i = 1 ; i <= N ; ++ i)
            G[i].clear();
        partNum.clear();
    }
    cin.close();
    cout.close();
    return 0;
}
