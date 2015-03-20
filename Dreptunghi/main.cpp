#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <string>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <math.h>

using namespace std;

const char infile[] = "dreptunghi.in";
const char outfile[] = "dreptunghi.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

inline int solve(int N, int M) {
    if(N > M)
        swap(N, M);
    if(!N)
        return 0;
    return (M / N) * N + solve(N, M % N);
}

int main() {
    int N, M;
    fin >> N >> M;
    fout << solve(N, M) << '\n';
    fin.close();
    fout.close();
    return 0;
}
