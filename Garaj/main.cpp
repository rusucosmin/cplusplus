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

const char infile[] = "garaj.in";
const char outfile[] = "garaj.out";

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

struct truck {
    int c, t;
};

struct classComp {
    inline bool operator () (const truck &A, const truck &B) const {
        return A.c > B.c;
    }
};

truck a[MAXN];
int N, M;

inline bool Check(const int &T) {
    int sent = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        int nr = T / a[i].t;
        sent += (nr * a[i].c);
        if(sent >= M)
            return true;
    }
    return false;
}

inline int binarySearch() {
    int li = 0;
    int ls = (1 << 29);
    int ret = 0;
    while(li <= ls) {
        int mid = li + ((ls - li) >> 1);
        if(Check(mid)) {
            ls = mid - 1;
            ret = mid;
        }
        else li = mid + 1;
    }
    return ret;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> a[i].c >> a[i].t;
        a[i].t *= 2;
    }
    int Ans1 = binarySearch();
    for(int i = 1 ; i <= N ; ++ i)
        a[i].c = (Ans1 / a[i].t) * a[i].c;
    sort(a + 1, a + N + 1, classComp());
    int cnt = 0;
    int sum = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        sum += a[i].c;
        ++ cnt;
        if(sum >= M)
            break;
    }
    fout << Ans1 << ' ' << cnt << '\n';
    //cerr << Ans1 << ' ' << cnt << '\n';
    fin.close();
    fout.close();
    return 0;
}
