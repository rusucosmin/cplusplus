#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "cifru.in";
const char outfile[] = "cifru.out";

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

int N, K, x[MAXN];

int main() {
    fin >> N >> K;
    x[0] = 1;
    for(int i = 1 ; i <= N ; ++ i) {
        int j = 1, a = 1;
        while( j <= i && j <= K ) {
            if(K % j == 0)
                x[i] = (x[i] + a * x[i - j]) % 19997;
            a = (a * (i - j)) % 19997;
            ++ j;
        }
    }
    fout << x[N] << '\n';
    fin.close();
    fout.close();
    return 0;
}
