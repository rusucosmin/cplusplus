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
#include <cassert>

using namespace std;

const char infile[] = "spargere2.in";
const char outfile[] = "spargere2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

long long dp[2*MAXN];
int N, K;

int main() {
    fin >> N >> K;
    for(int i = K ; i <= N + K - 1; ++ i) {
        long long x;
        fin >> x;
        dp[i] = max(x, max(dp[i - K] + x, dp[i - 1]));
    }
    fout << max(dp[N + K - 1], 0LL) << '\n';
    fin.close();
    fout.close();
    return 0;
}
