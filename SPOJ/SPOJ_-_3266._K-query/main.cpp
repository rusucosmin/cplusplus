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

const int MAXN = 30005;
const int MAXQ = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct event {
    int ind;
    int val;
    int st;
    int dr;
    bool type;
    event(int _ind, int _val, bool _type, int _st = 0, int _dr = 0) {
        ind = _ind;
        val = _val;
        type = _type;
        st = _st;
        dr = _dr;
    }
};

vector <event> V;
int N, Q;
int ans[MAXQ];

struct classComp {
    inline bool operator () (const event &a, const event &b) const {
        return a.val < b.val || (a.val == b.val && a.type < b.type);
    }
};

int aib[MAXN];

inline int lsb(int x) {
    return x & (-x);
}

inline void Update(int pos) {
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
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        scanf("%d", &x);
        V.push_back(event(i, x, 0));
    }
    scanf("%d", &Q);
    for(int i = 1 ; i <= Q ; ++ i) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        V.push_back(event(i, k, 1, x, y));
    }
    sort(V.begin(), V.end(), classComp());
    for(vector <event> :: iterator it = V.begin(), fin = V.end(); it != fin ; ++ it) {
        if(it->type) {
            int lessThan = Query(it->dr) - Query(it->st - 1);
            ans[it->ind] = (it->dr - it->st + 1) - lessThan;
        }
        else
            Update(it->ind);
    }
    for(int i = 1 ; i <= Q ; ++ i)
        printf("%d\n", ans[i]);
    return 0;
}
