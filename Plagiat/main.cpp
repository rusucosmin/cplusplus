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
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

const char infile[] = "plagiat.in";
const char outfile[] = "plagiat.out";

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

map<pair<int, int>, short> ok;
vector <pair<int, int> > v;
int N;

inline int ab(const int &value) {
    if(value < 0)
        return -value;
    return value;
}

int main() {
    int T;
    fin >> T;
    while(T -- ) {
        ok.clear();
        v.clear();
        fin >> N;
        bool o = true;
        for(int i = 0 ; i < N ; ++ i) {
            int x, y;
            fin >> x >> y;
            v.push_back(make_pair(x, y));
        }
        sort(v.begin(), v.end());
        for(int i = 0 ; i < N && o ; ++ i)
            for(int j = i + 1 ; j < N && o ; ++ j)
                if(++ ok[make_pair(v[j].first - v[i].first, v[j].second - v[i].second)] > 2)
                    o = false;
        if(o)
            fout << "NU\n";
            else fout << "DA\n";
    }
    fin.close();
    fout.close();
    return 0;
}
