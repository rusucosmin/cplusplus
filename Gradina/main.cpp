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
#include <cassert>

using namespace std;

const char infile[] = "gradina.in";
const char outfile[] = "gradina.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 255;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    /// fuck unsigned numbers
    char sign = '+';
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        sign = buff[pos];
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    x = 0;
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    if(sign == '-')
        x = -x;
}

int N, idx[MAXN], best;
pair<int, int> P[MAXN];
bitset <MAXN> Used;
long long ans = (1LL << 60);
char s[2][MAXN];
string ansString;

struct classComp {
    inline bool operator () (const int &a, const int &b) const {
        return P[a].first < P[b].first || (P[a].first == P[b].first && P[a].second < P[b].second);
    }
};

inline long long crossProduct(pair<int, int> A, pair<int, int> B, pair<int, int> C) {
    return 1LL * (B.first - A.first) * (C.second - A.second) - 1LL * (B.second - A.second) * (C.first - A.first);
}

inline void convexHull(vector <int> &v, vector <int> &inf) {
    if(v.size() < 3)
        return;
    inf.clear();
    inf.push_back(v[0]);
    inf.push_back(v[1]);
    Used.reset();
    Used[v[1]] = 1;
    for(int i = 2 ; i < v.size() ; ++ i) {
        if(Used[v[i]])
            continue;
        while(inf.size() >= 2 && crossProduct(P[inf[inf.size() - 2]], P[inf[inf.size() - 1]], P[v[i]]) < 0) {
            Used[inf[inf.size() - 1]] = 0;
            inf.pop_back();
        }
        Used[v[i]] = 1;
        inf.push_back(v[i]);
    }
    for(int i = v.size() - 1 ; i >= 0 ; -- i) {
        if(Used[v[i]])
            continue;
        while(inf.size() >= 2 && crossProduct(P[inf[inf.size() - 2]], P[inf[inf.size() - 1]], P[v[i]]) < 0) {
            Used[inf[inf.size() - 1]] = 0;
            inf.pop_back();
        }
        Used[v[i]] = 1;
        inf.push_back(v[i]);
    }
    inf.pop_back();
}

inline long long Area(vector<int> v) {
    long long _area = 0;
    for(int i = 1; i + 1 < v.size(); i ++) {
        long long cross = crossProduct(P[v[0]], P[v[i]], P[v[i + 1]]);
        _area += cross;
    }
    return abs(_area);
}

inline string getAnsString(vector<int> inf[2]) {
    for(int i = 0 ; i < 2 ; ++ i)
        for(int j = 0 ; j < inf[i].size() ; ++ j)
            if(i == 0) {
                s[0][inf[i][j]] = 'I';
                s[1][inf[i][j]] = 'V';
            }
            else {
                s[0][inf[i][j]] = 'V';
                s[1][inf[i][j]] = 'I';
            }
    string s1(s[0] + 1);
    string s2(s[1] + 1);
    return min(s1, s2);
}

int main() {
    freopen(infile, "r", stdin);
    getInt(N);
    for(int i = 1 ; i <= N ; ++ i) {
        getInt(P[i].first);
        getInt(P[i].second);
        idx[i] = i;
    }
    sort(idx + 1, idx + N + 1, classComp());
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = i + 1 ; j <= N ; ++ j) {
            //if(i == j)
            //    continue;
            vector <int> v[2];
            for(int k = 1 ; k <= N ; ++ k) {
                if(k == i) {
                    v[0].push_back(idx[i]);
                    continue;
                }
                if(k == j) {
                    v[1].push_back(idx[j]);
                    continue;
                }
                long long now = crossProduct(P[idx[i]], P[idx[j]], P[idx[k]]);
                if(now > 0)
                    v[0].push_back(idx[k]);
                else v[1].push_back(idx[k]);
            }
            vector <int> inf[2];

            convexHull(v[0], inf[0]);
            if(v[0].size() != inf[0].size())
                continue;

            convexHull(v[1], inf[1]);
            if(v[1].size() != inf[1].size())
                continue;

            long long area[2];
            area[0] = Area(inf[0]);
            area[1] = Area(inf[1]);
            long long dif = abs(area[0] - area[1]);
            if(ans > dif) {
                ans = dif;
                ansString = getAnsString(inf);
            }
            else if(ans == dif)
                ansString = min(ansString, getAnsString(inf));
    }
    assert(ans != (1LL << 60));
    fout << fixed << setprecision(1) << (0.5 * ans) << '\n';
    fout << ansString << '\n';
    fout.close();
    return 0;
}
