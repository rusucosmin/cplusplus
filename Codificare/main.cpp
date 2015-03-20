#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "codificare.in";
const char outfile[] = "codificare.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;
const int SIGMA = 26;
const int MOD = 666013;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, fact[MAXN] = {1}, fr[SIGMA];
char s[MAXN];

int lgPut(int a, int n) {
    if(n == 1)
        return a;
    int aux = (1LL * a * a) % MOD;
    if(n % 2)
        return (1LL * a * lgPut(aux, ((n - 1) / 2))) % MOD;
    return lgPut(aux, n / 2);
}

inline int inv(int k) {
    return lgPut(k, MOD - 2);
}

inline int cmb(int n, int k) {
    int in = inv((1LL * fact[k] * fact[n - k]) % MOD);
    return (1LL * fact[n] * in) % MOD;
}

int main() {
    fin >> N;
    fin.get();
    fin.getline(s, MAXN);
    for(int i = 1; i <= N ; ++ i)
        fact[i] = (1LL * fact[i-1] * i)%MOD;
    for(int i = 0 ; i < N ; ++ i) {
        int st = i;
        int dr = N - i - 1;
        fr[s[i] - 'a'] = (fr[s[i] - 'a'] + cmb(st + dr, st)) % MOD;
    }
    int Ans = 0;
    for(int i = 0 ; i < 26 ; ++ i)
        Ans += (fr[i] > 0);
    fout << Ans << '\n';
    for(char i = 'a' ; i <= 'z' ; ++ i)
        if(fr[i - 'a'])
            fout << i << ' ' << fr[i - 'a'] << "\n";
    fin.close();
    fout.close();
    return 0;
}
