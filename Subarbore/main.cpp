#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>

using namespace std;

const char infile[] = "subarbore.in";
const char outfile[] = "subarbore.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 65;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, T, st[MAXN], costTotal = oo, Father[MAXN];
int d[MAXN][MAXN];
vector <int> Nodes;
bitset <MAXN> special;
vector<pair<int, pair<int, int> > > edges;

inline void buildRoyFloyd() {
    for(int k = 1 ; k <= N ; ++ k)
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j)
                if(i != j && j != k && d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
}

int Find(int x) {
    if(x != Father[x])
        Father[x] = Find(Father[x]);
    return Father[x];
}

inline void Unite(int x, int y) {
    Father[x] = y;
}

int Apm(int k) {
    edges.clear();
    for(int i = 1 ; i <= k ; ++ i)
        for(int j = i + 1; j <= k ; ++ j)
            edges.push_back(make_pair(d[Nodes[st[i]]][Nodes[st[j]]], make_pair(Nodes[st[i]], Nodes[st[j]])));
    for(int i = 0 ; i <= N ; ++ i)
        Father[i] = i;
    int actCost = 0;
    sort(edges.begin(), edges.end());
    for(int i = 0, M = edges.size() ; i < M ; ++ i) {
        int Tx = Find(edges[i].second.first);
        int Ty = Find(edges[i].second.second);
        if(Tx != Ty) {
            actCost += edges[i].first;;
            if(actCost > costTotal)
                return oo;
            Unite(Tx, Ty);
        }
    }
    return actCost;
}

void Back(int k) {
    costTotal = min(costTotal, Apm(k));
    if(k>=2*T-2)
        return;
    for(int i = st[k] + 1 ; i <= N ; ++ i) {
        st[k + 1] = i;
        Back(k + 1);
    }
}

int main() {
    memset(d, oo, sizeof(d));
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        d[x][y] = d[y][x] = z;
    }
    buildRoyFloyd();
    cin >> T;
    if(T <= 1) {
        cout << "0\n";
        return 0;
    }
    Nodes.push_back(0);
    for(int i = 1 ; i <= T ; ++ i) {
        int x;
        cin >> x;
        special[x] = true;
        Nodes.push_back(x);
        st[i] = i;
    }
    if(T == 2) {
        cout << d[Nodes[1]][Nodes[2]] << '\n';
        return 0;
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!special[i])
            Nodes.push_back(i);
    Back(T);
    cout << costTotal << '\n';
    cin.close();
    cout.close();
    return 0;
}
