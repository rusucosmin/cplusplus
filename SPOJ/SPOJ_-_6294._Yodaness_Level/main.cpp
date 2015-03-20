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

const char infile[] = "input.in";
const char outfile[] = "output.out";

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

map<string, int> idx;
int ind[MAXN];
int aib[MAXN];
int N, T;

inline int lsb(int x) {
    return x & (-x);
}

inline int Update(int pos) {
    for(int i = pos ; i <= N ; i += lsb(i))
        ++ aib[i];
}

inline int Query(int pos) {
    int sum = 0;
    for(int i = pos ; i > 0 ; i -= lsb(i))
        sum += aib[i];
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        idx.clear();
        scanf("%d", &N);
        char s[25];
        for(int i = 1 ; i <= N ; ++ i) {
            scanf("%s", s);
            idx[s] = i;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            scanf("%s", s);
            ind[i] = idx[s];
            aib[i] = 0;
        }
        int Ans = 0;
        for(int i = 1 ; i <= N ; ++ i) {
            Update(ind[i]);
            Ans += (i - Query(ind[i]));
        }
        printf("%d\n", Ans);
    }
    return 0;
}
