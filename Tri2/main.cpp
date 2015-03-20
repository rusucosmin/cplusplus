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

const char infile[] = "tri2.in";
const char outfile[] = "tri2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector <pair<int, int> > P;
vector <int> _left, _right;
vector <int> norm;
vector <int> X;
int OX, OY;
int N, Q, a[4];
int aib[MAXN];
int Ans[MAXN][MAXN];

bool comp_left(const int &a, const int &b) {
    return 1LL * (OY - P[a].second) * (OX - P[b].first) < 1LL * (OX - P[a].first) * (OY - P[b].second);
}

bool comp_right(const int &a, const int &b) {
    return 1LL * (P[a].second - OY) * (P[b].first - OX) < 1LL * (P[a].first - OX) * (P[b].second - OY);
}
inline void split(int where) {
    for(int i = 0 ; i < N ; ++ i) {
        if(i == where)
            continue;
        if(P[i].first < P[where].first)
            _left.push_back(i);
        else _right.push_back(i);
    }
}

inline int lsb(int x) {
    return x & (-x);
}

inline void Update(int x) {
    for(int pos = x ; pos < MAXN ; pos += lsb(pos))
        ++ aib[pos];
}

inline int Query(int x) {
    int sum = 0;
    for(int pos = x ; pos > 0 ; pos -= lsb(pos))
        sum += aib[pos];
    return sum;
}

inline void buildBIT(int pos, vector <int> &v) {
    for(int i = 0 ; i < MAXN ; ++ i)
        aib[i] = 0;
    for(int i = 1 ; i < v.size() ; ++ i) {
        Update(norm[v[i - 1]]);
        Ans[pos][v[i]] = Query(max(norm[pos], norm[v[i]])) - Query(min(norm[pos], norm[v[i]]));
    }
}

int main() {
    fin >> N;
    for(int i = 0 ; i < N ; ++ i) {
        int x, y;
        fin >> x >> y;
        P.push_back(make_pair(x, y));
        X.push_back(x);
    }
    sort(X.begin(), X.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());
    for(int i = 0 ; i < N ; ++ i)
        norm.push_back(lower_bound(X.begin(), X.end(), P[i].first) - X.begin() + 1);
    for(int i = 0 ; i < N ; ++ i) {
        _left.clear();
        _right.clear();

        split(i);

        OX = P[i].first;
        OY = P[i].second;
        sort(_left.begin(), _left.end(), comp_left);
        sort(_right.begin(), _right.end(), comp_right);

        buildBIT(i, _left);
        buildBIT(i, _right);
    }
    fin >> Q;
    for(int q = 1 ; q <= Q ; ++ q) {
        for(int i = 0 ; i < 3 ; ++ i) {
            fin >> a[i];
            -- a[i];
        }
        for(int i = 0 ; i < 3 ; ++ i)
            for(int k = i + 1 ; k < 3 ; ++ k)
                if(P[a[i]].first > P[a[k]].first)
                    swap(a[i], a[k]);
        OX = P[a[0]].first;
        OY = P[a[0]].second;
        if(comp_right(a[1], a[2]))
            fout << Ans[a[0]][a[2]] - Ans[a[0]][a[1]] - Ans[a[1]][a[2]] - 1 << '\n';
        else fout << Ans[a[0]][a[1]] + Ans[a[1]][a[2]] - Ans[a[0]][a[2]] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
