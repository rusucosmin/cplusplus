#include <fstream>

using namespace std;

const char infile[] = "ciuperci.in";
const char outfile[] = "ciuperci.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MOD = 666013;
const int U = 31;
const int oo = 0x3f3f3f3f;

int T;
long long N;

pair<long long, long long> Solve(const long long &m, const long long &n) {
    if(m == 0 && n == 1)
        return make_pair(1LL, 1LL);
    if(m == 1 && n == 2)
        return make_pair(1LL, 2LL);
    pair<long long, long long> a = Solve(n / 2 - 1, n / 2), ret;
    if(n % 2 == 0) {
        ret.first = a.first * a.first % MOD;
        ret.second = a.first * a.second * 2 % MOD;
    }
    else {
        ret.second = a.second * a.second % MOD;
        ret.first = a.first * a.second * 2 % MOD;
    }
    return ret;
}

int main() {
    fin >> T;
    while(T --) {
        fin >> N;
        fout << Solve(N - 1, N).second << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
