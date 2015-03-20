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

const char infile[] = "xcmmdc.in";
const char outfile[] = "xcmmdc.out";
ofstream fout(outfile);

const int MAXLG = 10;
const int MAXN = 1005;
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

inline void get(int &x) {
    x = 0;
    while(!isdigit(buff[pos]))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while(isdigit(buff[pos])) {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

int m, n, k, q;
int rmq[MAXLG][MAXN][MAXN];
int mars[MAXN], Log[MAXN];
int ans[MAXN];

int cmmdc(int x, int y) {
    if(y == 0)
        return x;
    return cmmdc(y, x%y);
}

int cmmdcrmq(int x, int y, int l) {
    int log = Log[l];
    int ans = cmmdc(rmq[log][x][y], cmmdc(rmq[log][x + l - (1 << log)][y], cmmdc(rmq[log][x][y + l - (1 << log)], rmq[log][x + l - (1 << log)][y + l - (1 << log)])));
    return ans;
}

inline int lowerBound(int x, int y) {
    int st = 1;
    int dr = min(m + 1 - x, n + 1 - y);
    int ans = 0;
    while(st <= dr) {
        int mid = ((st + dr) >> 1);
        int cm = cmmdcrmq(x, y, mid);
        if(cmmdcrmq(x, y, mid) == k) {
            dr = mid - 1;
            ans = mid;
        }
        else if(cm < k)
            dr = mid - 1;
        else st = mid + 1;
    }
    return ans;
}

inline int upperBound(int x, int y) {
    int st = 1;
    int dr = min(m + 1 - x, n + 1 - y);
    int ans = 0;
    while(st <= dr) {
        int mid = ((st + dr) >> 1);
        int cm = cmmdcrmq(x, y, mid);
        if(cmmdcrmq(x, y, mid) == k) {
            st = mid + 1;
            ans = mid;
        }
        else if(cm < k)
            dr = mid - 1;
        else st = mid + 1;
    }
    return ans;
}

int main() {
    freopen(infile, "r", stdin);
    get(m);
    get(n);
    get(k);
    get(q);
    for(int i = 1 ; i <= m ; i ++)
        for(int j = 1 ; j <= n ; j ++)
            get(rmq[0][i][j]);
    for(int i = 2 ; i <= max(n, m) ; i ++)
        Log[i] = Log[i / 2] + 1;
    for(int l = 1 ; (1 << l) <= max(n, m) ; l ++) {
        for(int i = 1 ; i + (1 << l) - 1 <= m ; i ++)
            for(int j = 1 ; j + (1 << l) - 1 <= n ; j ++) {
                int aux = (1 << (l - 1));
                rmq[l][i][j] = cmmdc(rmq[l - 1][i][j], cmmdc(rmq[l - 1][i + aux][j], cmmdc(rmq[l - 1][i][j + aux], rmq[l - 1][i + aux][j + aux])));
            }
    }
    for(int i = 1 ; i <= m ; ++ i)
        for(int j = 1 ; j <= n ; ++ j) {
            int low = lowerBound(i, j);
            int high = upperBound(i, j);
            if(low == 0 && high == 0)
                continue;
            //cerr << i << ' ' << j << " values " << low << ' ' << high << '\n';
            mars[low] += 1;
            mars[high + 1] -= 1;
        }
    for(int i = 1 ; i <= max(n, m) ; i ++ ) {
        ans[i] = ans[i - 1] + mars[i];
        //cerr << ans[i] << '\n';
    }
    for(int i = 1; i <= q ; i ++) {
        int query;
        get(query);
        fout << ans[query] << '\n';
    }
    fout.close();
    return 0;
}
