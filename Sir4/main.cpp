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

const char infile[] = "sir4.in";
const char outfile[] = "sir4.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2*1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

string c;
bitset <MAXN> Used;
int X0, A, B, M, Q, Xlast, period;
int qu[1005], nr[100005];
map<int, int> mp;

int div(int X) {
    int r=0;
    for (int i = 0;i < c.size() ; ++ i)
        r = (r * 10 + (c[i] - '0'))%X;
    return r;
}

int main() {
    fin >> X0 >> A >> B >> M >> Q;
    Xlast = X0;
    Used[X0] = true;
    ++ period;
    while(true) {
        int Xi = (1LL * Xlast * A + B ) % M;
        if(Used[Xi])
            break;
        Used[Xi] = true;
        ++ period;
        Xlast = Xi;
    }
    for(int i = 1 ; i <= Q ; ++ i) {
        int modul = 0;
        fin >> c;
        qu[i] = div(period);
        mp[qu[i]] = 0;
    }
    Used.reset();
    Xlast = X0;
    Used[X0] = true;
    mp[0] = X0;
    period = 0;
    while(true) {
        int Xi = (1LL * Xlast * A + B ) % M;
        if(Used[Xi])
            break;
        Used[Xi] = true;
        ++ period;
        if(mp.find(period) != mp.end())
            mp[period] = Xi;
        Xlast = Xi;
    }
    for(int i = 1 ; i <= Q ; ++ i)
        fout << mp[qu[i]] << ' ';
    fin.close();
    fout.close();
    return 0;
}
