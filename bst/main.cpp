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

const char infile[] = "aib.in";
const char outfile[] = "aib.out";

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

class bit {
private:
    vector <int> a;
    int n;
public:
    bit() {

    }
    bit(int n) {
        a.resize( n + 1 );
        this->n = n;
    }
    inline void update(int pos, int value) {
        for(int i = pos ; i <= n ; i += lsb(i) )
            a[i] += value;
    }
    inline int query(int pos) {
        int sum = 0;
        for(int i = pos ; i > 0 ; i -= lsb(i))
            sum += a[i];
        return sum;
    }
    inline int lsb(int v) {
        return v & (-v);
    }
} aib;

int n, m;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> n >> m;
    aib = bit(n);
    for(int i = 1 ; i <= n ; ++ i) {
        int value;
        fin >> value;
        aib.update(i, value);
    }
    while(m --) {
        int op, a, b;
        fin >> op >> a;
        if(op == 0) {
            fin >> b;
            aib.update(a, b);
        }
        else if(op == 1) {
            fin >> b;
            fout << aib.query(b) - aib.query(a - 1) << '\n';
        }
        else {
            int st = 1, dr = n, ans = -1;
            while(st <= dr) {
                int mid = ((st + dr) >> 1);
                int q = aib.query(mid);
                if(q == a) {
                    ans = mid;
                    dr = mid - 1;
                }
                else if(q > a)
                    dr = mid - 1;
                else st = mid + 1;
            }
            fout << ans << '\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}
