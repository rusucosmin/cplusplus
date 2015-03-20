#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "matrice2.in";
const char outfile[] = "matrice2.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 305;
const int MAXQ = 20005;
const int oo = 0x3f3f3f3f;
const int dx[] = { -1, 1, 0,  0};
const int dy[] = {  0, 0, 1, -1};

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, Q, Father[MAXN * MAXN], m[MAXN][MAXN], actValue, nrQ[MAXN * MAXN], Q1[MAXQ], Q2[MAXQ], Qr[MAXQ];
vector < pair<int, int> > v;
vector <int> Query[MAXN * MAXN];

struct _greater {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.first > b.first;
    }
};

int Find(const int &X) {
    if(Father[X] != X)
        Father[X] = Find(Father[X]);
    return Father[X];
}

inline void Unite(int x, int y) {
    x = Find(x);
    y = Find(y);
    if(x == y)
        return;
    if(nrQ[x] > nrQ[y])
        swap(x, y);

    Father[x] = y;
    nrQ[y] += nrQ[x];
    for(vector<int> :: iterator it = Query[x].begin(), fin = Query[x].end(); it != fin ; ++ it) {
        if(Q1[*it] == Q2[*it])
            continue;
        if(Q1[*it] == x)
            Q1[*it] = y;
        if(Q2[*it] == x)
            Q2[*it] = y;
        if(Q1[*it] == Q2[*it]) {
            Qr[*it] = actValue;
            continue;
        }
        Query[y].push_back(*it);
    }
    Query[x].clear();
}

int main() {
    cin >> N >> Q;
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < N ; ++ j) {
            cin >> m[i][j];
            v.push_back(make_pair(m[i][j], i * N + j ));
        }
    sort(v.begin(), v.end(), _greater());
    for(int i = 0 ; i < Q; ++ i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        -- x1; -- y1; -- x2; -- y2;

        Q1[i] = x1 * N + y1;
        Q2[i] = x2 * N + y2;

        Query[Q1[i]].push_back(i);
        Query[Q2[i]].push_back(i);
    }

    for(int i = 0 ; i < N * N ; ++ i) {
        Father[i] = i;
        nrQ[i] = Query[i].size();
    }

    for(int i = 0 ; i < N * N ; ) {
        actValue = v[i].first;

        int j;
        for(j = i ; j < N * N && v[i].first == v[j].first ; ++ j) {
            int x = v[j].second / N;
            int y = v[j].second % N;
            for(int d = 0 ; d < 4 ; ++ d) {
                int newx = x + dx[d];
                int newy = y + dy[d];
                if(newx < 0 || newx >= N || newy < 0 || newy >= N)
                    continue;
                if(m[newx][newy] < actValue)
                    continue;
                Unite(x * N + y , newx * N + newy);
            }
        }
        i = j;
    }
    for(int i = 0 ; i < Q ; ++ i)
        cout << Qr[i] << '\n';
    cin.close();
    cout.close();
    return 0;
}
