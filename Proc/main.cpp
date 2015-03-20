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

const char infile[] = "proc.in";
const char outfile[] = "proc.out";

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

int N, K, P;

inline bool Check(const int &value) {
    long long N1 = 0, N2 = 0, DOI = 0;
    for(int i = 1 ; i <= P ; ++ i)
        N2 += (value / i) / 2;
    if(N2 >= N - K) {
        for(int i = 1 ; i <= P ; ++ i)
            N1 += (value / i) % 2;
    }
    if(N1 + 2 * (N2 - N + K) >= K)
        return true;
    return false;
}

inline int binarySearch() {
    int li = 0, ls = (N << 1), Ans = 0;
    while(li <= ls) {
        int mid = (ls + li) / 2;
        if(Check(mid)) {
            Ans = mid;
            ls = mid - 1;
        }
        else li = mid + 1;
    }
    return Ans;
}

int main() {
    fin >> N >> K >> P;
    fout << binarySearch() << '\n';
    fin.close();
    fout.close();
    return 0;
}
