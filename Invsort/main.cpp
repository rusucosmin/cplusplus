#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "invsort.in";
const char outfile[] = "invsort.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 32005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, cnt[MAXN], v[MAXN], vmax, p[MAXN], a[MAXN];

inline void reverse(const int &st, const int &dr) {
    int i, aux;
    for(int i = st ; i <= ((st + dr ) >> 1) ; ++ i) {
        swap(a[i], a[dr - i + st]);
        swap(p[i], p[dr - i + st]);
    }
    fout << st << ' ' << dr << '\n';
}

void anotherSort(const int &st, const int &dr) {
    int mid = (st + dr) >> 1;
    if(st == dr)
        return;
    anotherSort(st, mid);
    anotherSort(mid + 1, dr);
    int i = mid, j = mid + 1;
    while(i >= st && a[i])
        -- i;
    while(j <= dr && !a[j])
        ++ j;
    if(i == mid || j == mid + 1)
        return;
    ++ i;
    -- j;
    reverse(i, j);
}

void sort(const int &st, const int &dr) {
    int mid = ((st + dr) >> 1);
    if(st == dr)
        return;
    for(int i = st ; i <= dr ; ++ i)
        a[i] = (p[i] >= mid);
    anotherSort(st, dr);
    sort(st, mid);
    sort(mid + 1 , dr);
}

int main() {
    fin >> N;
    for(int i = 1; i <= N ; ++ i) {
        fin >> v[i];
        ++ cnt[v[i] + 1];
        vmax = max(vmax, v[i] + 1);
    }
    for(int i = 1 ; i <= vmax ; ++ i)
        cnt[i] += cnt[i - 1];
    for(int i = 1 ; i <= N ; ++ i)
        p[i] = (cnt[v[i]] ++ );
    sort(1, N);
    fin.close();
    fout.close();
    return 0;
}
