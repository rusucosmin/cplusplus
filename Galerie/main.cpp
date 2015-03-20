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

const char infile[] = "galerie.in";
const char outfile[] = "galerie.out";

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

struct event {
    int x, y, z;
    int ind;
    event(int _x, int _y, int _z, int _ind) {
        x = _x;
        y = _y;
        z = _z;
        ind = _ind;
    }
};

int N, M, T, aib[MAXN];
vector <event> v;

struct classComp {
    inline bool operator () (const event &a, const event &b) const {
        if(a.y == b.y)
            return a.ind < b.ind;
        return a.y > b.y;
    }
};

class aib {
private:
    int a[MAXN], n;
    inline int lsb(int x) {
        return x & (-x);
    }
public:
    void setLimit(int _n) {
        n = _n;
    }
    void update(int pos, int value) {
        for(int i = pos ; i <= n ; i += lsb(i))
            a[i] += value;
    }
    int query(int pos) {
        int sum = 0;
        for(int i = pos ; i > 0 ; i -= lsb(i))
            sum += a[i];
        return sum;
    }
} Aib;

long long ans[250005];

int main() {
    fin >> N >> M >> T;
    Aib.setLimit(N);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        if(x > y)
            swap(x, y);
        if(z);
            v.push_back(event(x, y, z, 0));
    }
    for(int i = 1 ; i <= T ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        if(x > y)
            swap(x, y);
        v.push_back(event(x, y, z, i));
    }
    sort(v.begin(), v.end(), classComp());
    for(vector <event> :: iterator it = v.begin(), fin = v.end(); it != fin ; ++ it) {
        if(it->ind == 0) {
            Aib.update(it->x, it->z);
            //cerr << it->x << ' ';
        }
        else {
            //cerr << "!\n";
            if(it->y - it->x > it->z) {
                int sum = Aib.query(it->x);
                ans[it->ind] = 1LL * sum * (it->y - it->x - it->z);
            }
        }
    }
    for(int i = 1 ; i <= T ; ++ i)
        fout << ans[i] << '\n';
    return 0;
}
