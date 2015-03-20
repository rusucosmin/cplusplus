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
#include <stack>
#include <cassert>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 275;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }
const inline int myAbs(int a) { return max(a, -a); }

Graph G;

Graph bipartite;
int C[2 * MAXN][2 * MAXN];
bitset <MAXN> Used;

int N, M, B, lowLink[MAXN], depth[MAXN], T, supply[MAXN], energy[MAXN], match[MAXN], mate[MAXN];
vector <int> bcc;
stack<pair<int, int> > stk;
bitset <MAXN> used;

inline void extractBCC(int x, int y) {
    int Tx, Ty;
    set <int> s1, s2;
    do {
        Tx = stk.top().first;
        Ty = stk.top().second;
        stk.pop();
        s1.insert(Tx);
        s1.insert(Ty);
    } while(x != Tx || y != Ty);
    int sum1 = 0;
    if(s1.size() <= 2)
        return ;
    for(set<int> :: iterator it = s1.begin(), fin = s1.end(); it != fin ; ++ it) {
        sum1 += supply[*it];
        used[*it] = 1;
    }
    bcc.push_back(sum1);
}

inline void DFs(int Node, int Father, int actLevel) {
    depth[Node] = lowLink[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!depth[*it]) {
            stk.push(make_pair(Node, *it));
            DFs(*it, Node, actLevel + 1);
            lowLink[Node] = min(lowLink[Node], lowLink[*it]);
            if(lowLink[*it] >= depth[Node])
                extractBCC(Node, *it);
        }
        else
            lowLink[Node] = min(lowLink[Node], depth[*it]);
    }
}

inline bool pairUp(int Node, int value) {
    if(Used[Node])
        return 0;
    Used[Node] = 1;
    for(It it = bipartite[Node].begin(), fin = bipartite[Node].end(); it != fin ; ++ it)
        if(C[Node][*it] <= value)
            if(!mate[*it] || pairUp(mate[*it], value)) {
                mate[*it] = Node;
                match[Node] = *it;
                return 1;
            }
    return 0;
}

inline int maximumMatching(int value) {
    int maxMatch = 0;
    memset(match, 0, sizeof(match));
    memset(mate, 0, sizeof(mate));
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= B ; ++ i)
            if(!match[i])
                if(pairUp(i, value)) {
                    ++ maxMatch;
                    change = true;
                }
    }
    return maxMatch;
}

inline int binarySearch() {
    int li = 0, ls = 1000000;
    int Ans = -1;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        int match = maximumMatching(mid);
        if(match >= bcc.size()) {
            ls = mid - 1;
            if(match == bcc.size())
                Ans = mid;
        }
        else li = mid + 1;
    }
    assert(Ans != -1);
    return Ans;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T; ++ test) {
        cin >> N >> M >> B;
        int Source = 0, Sink;
        for(int i = 1 ; i <= N ; ++ i)
            cin >> supply[i];
        for(int i = 1 ; i <= B ; ++ i)
            cin >> energy[i];
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        for(int i = 1 ; i <= N ; ++ i)
            if(!depth[i])
                DFs(i, i, 1);
        for(int i = 1 ; i <= N ; ++ i)
            if(!used[i]) {
                bcc.push_back(supply[i]);
                used[i] = 1;
            }
        for(int i = 1 ; i <= B ; ++ i) {
            for(int j = 0 ; j < bcc.size() ; ++ j) {
                int x = i;
                int y = j + 1;
                int z = myAbs(energy[i] - bcc[j]);
                bipartite[x].push_back(y);
                C[x][y] = z;
            }
        }
        if(bcc.size() > B)
            cout << "Buzz Mission " << test << ": " << bcc.size() << ' ' << "No" << '\n';
        else
            cout << "Buzz Mission " << test << ": " << bcc.size() << ' ' << binarySearch() << '\n';
        for(int i = 0 ; i <= max(N, B) ; ++ i) {
            vector <int> ().swap(G[i]);
            vector <int > ().swap(bipartite[i]);
        }
        used.reset();
        while(stk.size())
            stk.pop();
        vector <int> ().swap(bcc);
        memset(C, 0, sizeof(C));
        memset(depth, 0, sizeof(depth));
        memset(lowLink, 0, sizeof(lowLink));
    }
    fin.close();
    fout.close();
    return 0;
}
