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
#include <deque>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 101005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph R;
int Father[MAXN], d[MAXN], deg[MAXN];
int N, K;
bitset <MAXN> used;

inline int Find(int x) {
    if(x != Father[x])
        Father[x] = Find(Father[x]);
    return Father[x];
}

inline void Unite(int x, int y) {
    Father[x] = y;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> d[i];
        if(d[i] > 100000) {
            cout << "-1\n";
            return 0;
        }
        R[d[i]].push_back(i);
        Father[i] = i;
    }
    if(R[0].size() > 1 || !R[0].size()) {
        cout << "-1\n";
        return 0;
    }
    queue <int> Q;
    int stNode = R[0][0];
    used[stNode] = 1;
    Q.push(stNode);
    vector <pair<int, int> > E;
    while(!Q.empty()) {
        int Node = Q.front();
        used[Node] = 1;
        Q.pop();
        int dist = d[Node] + 1;
        if(R[dist].size() == 0)
            break;
        for(It it = R[dist].begin(), fin = R[dist].end(); it != fin ; ++ it) {
            if(deg[Node] >= K)
                break;
            if(!used[*it] && deg[*it] < K) {
                E.push_back(make_pair(Node, *it));
                Q.push(*it);
                used[*it] = 1;
                ++ deg[Node];
                ++ deg[*it];
                Unite(Find(Node), Find(*it));
            }
        }
    }
    int unu = Find(1);
    for(int i = 1 ; i <= N ; ++ i)
        if(Find(i) != unu) {
            cout << "-1\n";
            return 0;
        }
    cout << E.size() << '\n';
    for(vector <pair<int, int> > :: iterator it = E.begin(), fin = E.end(); it != fin ; ++ it)
        cout << it->first << ' ' << it->second << '\n';
    fin.close();
    fout.close();
    return 0;
}
