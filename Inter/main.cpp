#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "inter.in";
const char outfile[] = "inter.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, p[MAXN];
bool swaps[MAXN][MAXN];

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        p[i] = i;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        swaps[x][y] = 1;
        swaps[y][x] = 1;
    }
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j < N ; ++ j)
            if(swaps[p[j]][p[j+1]] || swaps[p[j+1]][p[j]])
                swap(p[j], p[j+1]), swaps[p[j]][p[j+1]] = swaps[p[j+1]][p[j]] = 0;
    }
    for(int i = 1 ; i <= N ; ++ i)
        fout << p[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
