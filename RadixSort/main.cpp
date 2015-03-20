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

const char infile[] = "radixsort.in";
const char outfile[] = "radixsort.out";

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

const int bucket = 8;
const int times = 4;
const int mask = (1 << bucket) - 1;

inline void radixSort(vector <int> &a) {
    int n = a.size();
    vector <int> b(n);
    for(int sh = 0 ; sh < times ; ++ sh) {
        vector <int> _count(mask + 1, 0);
        for(int i = 0 ; i < n ; ++ i)
            ++ _count[(a[i] >> (sh * bucket)) & mask];
        for(int i = 1 ; i < mask + 1 ; ++ i)
            _count[i] += _count[i - 1];
        for(int i = n - 1 ; i >= 0 ; -- i)
            b[--_count[(a[i] >> (sh * bucket)) & mask]] = a[i];
        a = b;
    }
}

int main() {
    int n, A, b, c;
    fin >> n >> A >> b >> c;
    vector <int> a;
    a.push_back(b);
    for(int i = 2 ; i <= n ; ++ i)
        a.push_back((1LL * a.back() * A + b) % c);
    radixSort(a);
    for(int i = 0 ; i < a.size() ;i += 10)
        fout << a[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
