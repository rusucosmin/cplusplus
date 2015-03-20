#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <memory.h>

using namespace std;

const char infile[] = "dcmcp.in";
const char outfile[] = "dcmcp.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 10005;
const int oo = 0x3f3f3f3f;

struct trio {
    int x, c, t;
    trio(int _x, int _c, int _t) {
        x = _x;
        c = _c;
        t = _t;
    }
};

typedef vector< trio > Graph[MAXN];
typedef vector< trio > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, T, M, K, dist[MAXN], Ans;
Graph G;

inline void Clear() {
    for(int i = 1 ; i <= N ; ++ i)
        vector< trio > ().swap(G[i]);
}

inline int Check(const int&value) {
    priority_queue<pair<int, int> , vector <pair<int, int> > , greater < pair<int, int> > > Q;
    memset(dist, oo, sizeof(dist));
    dist[1] = 0;
    Q.push(make_pair(0, 1));
    while(!Q.empty()) {
        int Node = Q.top().second;
        int cost = Q.top().first;
        Q.pop();
        if(dist[Node] < cost)
            continue;
        if(Node == N)
            return cost;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(it->c >= value) {
                if(dist[it->x] > cost + it->t) {
                    dist[it->x] = cost + it->t;
                    Q.push(make_pair(dist[it->x],  it->x));
                }
            }
    }
    return oo;
}

inline void binarySearch() {
    int li = 1, ls = 2000000000;
    Ans = -1;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(Check(mid) <= K) {
            Ans = mid;
            li = mid + 1;
        }
        else ls = mid - 1;
    }
}

int main() {
    fin >> T;
    for(int test = 1 ;test <= T ; ++ test) {
        Clear();
        fin >> N >> M >> K;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, c, t;
            fin >> x >> y >> c >> t;
            G[x].push_back(trio(y, c, t));
            G[y].push_back(trio(x, c, t));
        }
        binarySearch();
        fout << Ans << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
