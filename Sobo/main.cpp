#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "sobo.in";
const char outfile[] = "sobo.out";

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

int N, L;
int A[MAXN][MAXL];

int main() {
    fin >> N >> L;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= L ; ++ j)
            fin >> A[i][j];
    }
    fin.close();
    fout.close();
    return 0;
}
