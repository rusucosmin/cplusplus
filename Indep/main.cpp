#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "indep.in";
const char outfile[] = "indep.out";

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

int N, dp[2][MAXN][MAXN];

int main() {
    fin >> N;
    d
    fin.close();
    fout.close();
    return 0;
}
