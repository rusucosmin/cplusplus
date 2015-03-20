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
#include <limits.h>
#include <limits>

using namespace std;

const char infile[] = "spargere.in";
const char outfile[] = "spargere.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, b[MAXN], t[MAXN], Q;
map <long long, long long> _hash;
const long long inf = ((1LL << 62));

inline unsigned long long check(long long T) {
    if(_hash[T])
        return _hash[T];
    unsigned long long sum = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        sum += 1LL * (T / t[i]) * b[i];
        sum += b[i];
    }
    _hash[T] = sum;
    return sum;
}

inline long long binarySearch(unsigned long long x) {
    long long st = 0;
    long long dr = (1LL << 62);
    long long ans = 0, mid;
    while(st <= dr) {
        mid = (st + ((dr - st) / 2));
        if(check(mid) >= x) {
            dr = mid - 1;
            ans = mid;
        }
        else st = mid + 1;
    }
    return ans;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> b[i] >> t[i];
    fin >> Q;
    for(int i = 1 ; i <= Q ; ++ i) {
        unsigned long long x;
        fin >> x;
        fout << binarySearch(x) << '\n';
    }
    return 0;
}
