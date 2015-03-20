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

const char infile[] = "jarbore.in";
const char outfile[] = "jarbore.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 25;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long Nodes[MAXN], vmin[MAXN], vmax[MAXN], v1[MAXN], v2[MAXN];

inline void Preprocess() {
    Nodes[1] = 1;
    vmin[1] = 0;
    vmax[1] = 0;
    v1[1] = 0;
    v2[1] = 0;
    for(int i = 2 ; i < MAXN ; ++ i) {
        Nodes[i] = 1LL * (i - 1) * Nodes[i - 1];
        v1[i] = v2[i - 1] + 1;
        v2[i] = v1[i] + Nodes[i] - 1;
        vmin[i] = vmin[i - 1] + v1[i];
        vmax[i] = vmax[i - 1] + v2[i];
    }
}

inline pair<long long, long long> Check(long long Value) {
    int st = 1, dr = MAXN - 1;
    while(st <= dr) {
        int mid = ((st + dr) >> 1);
        if(vmin[mid] <= Value && Value <= vmax[mid])
            return make_pair(Value - vmin[mid], mid);
        else {
            if(vmin[mid] > Value)
                dr = mid - 1;
            else st = mid + 1;
        }
    }
    return make_pair(-1LL, -1LL);
}

inline long long Reconstruct(long long p, long long q, bool checked) { /// returns the index from the p-th edge from the level q
    if(q == 1)
        return 0;
    long long val = Reconstruct(p / (q - 1), q - 1, checked);
    if(checked)
        fout << v1[q] + p << ' ';
    return val + v1[q] + p;
}

inline pair<long long, long long> binarySearch(long long q, long long value) {
    long long st = 0, dr = Nodes[q] - 1;
    while(st <= dr) {
        long long mid = ((st + dr) >> 1);
        long long smtg = Reconstruct(mid, q, false);
        if(smtg == value)
            return make_pair(mid, q);
        if(smtg < value)
            st = mid + 1;
        else dr = mid - 1;
    }
    return make_pair(-1, -1);
}

int main() {
    Preprocess();
    int T;
    fin >> T;
    for(int i = 1 ; i <= T ; ++ i) {
        long long x;
        fin >> x;
        pair<long long, long long> pos = Check(x);
        if(pos.first == -1LL)
            fout << "-1\n";
        else {
            pos = binarySearch(pos.second, x);
            if(pos.first == -1LL)
                fout << "-1\n";
            else {
                Reconstruct(pos.first, pos.second, true);
                fout << '\n';
            }
        }
    }
    fin.close();
    fout.close();
    return 0;
}
