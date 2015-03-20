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

const char infile[] = "flori2.in";
const char outfile[] = "flori2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
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
    char c = '+';
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        c = buff[pos];
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    if(c == '-')
        x = -x;
}

int T, N;
vector <pair<int, int> > v;
vector <double> p;
inline int cmmdc(int x, int y) {
    if(y == 0)
        return x;
    return cmmdc(y, x % y);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    freopen(infile, "r", stdin);
    getInt(T);

    for(int test = 1 ; test <= T ; ++ test) {
        getInt(N);
        for(int i = 0 ; i < N ; ++ i) {
            int x, y;
            getInt(x);
            getInt(y);
            v.push_back(make_pair(x, y));
        }
        if(N == 1) {
            cout << "1\n";
            continue;
        }
        int best = 0;
        for(int i = 0 ; i < N ; ++ i) {
            vector <double>().swap(p);
            for(int j = 0 ; j < N ; ++ j) {
                if(i == j)
                    continue;
                int x = v[j].first - v[i].first;
                int y = v[j].second - v[i].second;
                p.push_back((1.0 * y) / (1.0 * x));
            }
            sort(p.begin(), p.end());
            sort(p.begin(), p.end());
            sort(p.begin(), p.end());
            sort(p.begin(), p.end());
            sort(p.begin(), p.end());
            for(int i = 0 ; i < p.size() ; ++ i) {
                int now = 1;
                while((abs(p[i] - p[i + 1]) < 0.000000001) && i + 1 < p.size()) {
                    ++ i;
                    ++ now;
                }
                best = max(best, now);
            }
        }
        cout << best + 1 << '\n';
        cerr << best + 1<< '\n';
        vector <pair<int, int> > ().swap(v);
    }
    fin.close();
    fout.close();
    return 0;
}
