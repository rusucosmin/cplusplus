#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "binar.in";
const char outfile[] = "binar.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int ind[MAXN], N, M, v[MAXN];
char mt[MAXN][MAXN];

void radixSort(int level,int st, int dr) {
    if(level == N)
        return;
    int a = st - 1, b = dr + 1;
    for(int i = st ; i <= dr ; ++ i)
        if(mt[level][ind[i]] == '0')
            v[++ a] = ind[i];
        else v[-- b] = ind[i];
    for(int i = st ; i <= a ; ++ i)
        ind[i] = v[i];
    for(int i = a + 1, j = dr ; i <= dr ; ++ i, -- j)
        ind[i] = v[j];
    if(a > st)
        radixSort(level + 1, st, a);
    if(b < dr)
        radixSort(level + 1, a + 1, dr);
}

int main() {
    fin >> N >> M;
    fin.get();
    for(int i = 0 ; i < N ; ++ i)
        fin.getline(mt[i], MAXN);
    for(int i = 0 ; i < M ; ++ i)
        ind[i] = i;
    radixSort(0, 0, M - 1);
    for(int i = 0 ; i < M ; ++ i)
        fout << ind[i] + 1 << ' ';
    fin.close();
    fout.close();
    return 0;
}
