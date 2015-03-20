#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

ifstream fin("ssnd.in");
ofstream fout("ssnd.out");

const int maxn = 1000005;
const int mod = 9973;

bitset <maxn> used;
vector <int> primes;

inline void ciur() {
    primes.push_back(2);
    for(int i = 3 ; i < maxn ; i += 2) {
        if(used[i])
            continue;
        primes.push_back(i);
        for(int j = i + i ; j < maxn ; j += i)
            used[j] = 1;
    }
}

inline int lgpow(int a, int b) {
    a %= mod;
    int ans = 1;
    for( ; b ; b >>= 1) {
        if(b & 1)
            ans = (1LL * ans * a) % mod;
        a = (1LL * a * a) % mod;
    }
    return ans;
}

inline int invmod(int x) {
    return lgpow(x, mod - 2);
}

inline void solve(long long x) {
    int nr = 1, sum = 1;
    for(int i = 0 ; i < primes.size() && primes[i] * primes[i] <= x ; ++ i) {
        if(x % primes[i])
            continue;
        int cnt = 0;
        while(x % primes[i] == 0) {
            ++ cnt;
            x /= primes[i];
        }
        nr = (1LL * nr * (cnt + 1)) % mod;
        int first = lgpow(primes[i], cnt + 1) - 1;
        if(first < 0)
            first += mod;
        int second = invmod(primes[i] - 1);
        sum = (1LL * sum * first * second) % mod;
    }
    if(x > 1) {
        nr = (1LL * nr * 2) % mod;
        int first = lgpow(x, 2) - 1;
        if(first < 0)
            first += mod;
        int second = invmod(x - 1);
        sum = (1LL * sum * first * second) % mod;
    }
    fout << nr << ' ' << sum << '\n';
}

int main() {
    ciur();
    int t;
    fin >> t;
    while(t -- ) {
        long long x;
        fin >> x;
        solve(x);
    }
}
