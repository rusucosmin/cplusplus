#include <fstream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <math.h>

using namespace std;

const char infile[] = "insula.in";
const char outfile[] = "insula.out";

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

int main() {
    int N, T;
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> T;
        double sol = 1.0 / (sqrt(T * 1.0 * T + 1.0));
        fout << fixed << setprecision(3) << (double)((long long)(sol * 1000.0) / 1000.0) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
