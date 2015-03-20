#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "tree2.in";
const char outfile[] = "tree2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
bool a[350][350];

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1;
    }
    for(int i = 1 ; i < N ; ++ i){
        bool ok = true;
        for(int j = 1 ; j <= N && ok ; ++ j)
            for(int k = 1 ; k <= N && ok ; ++ k)
                if(!a[j][k] && j != k){
                    fout << j << ' ' << k << '\n';
                    a[j][k] = 1;
                    a[k][j] = 1;
                    ok = false;
                }
    }
    fin.close();
    fout.close();
    return 0;
}
