#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

const int maxn = 2000005;
const int mod1 = 666013;
const int mod2 = 100007;
const int base = 73;

int n, pi[maxn], m;
char s[maxn];

map<pair<int, int>, int> _hash;

inline pair<int, int> get_hash(int lg) {
    pair<int, int> ret;
    for(int i = 1 ; i <= lg ; ++ i) {
        ret.first = (ret.first * base + s[i]) % mod1;
        ret.second = (ret.second * base + s[i]) % mod2;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> n;
    cin.get();
    long long ans = 0;
    for(int test = 1 ; test <= n ; ++ test) {
        cin >> m >> s + 1;
        int k = 0;
        for(int i = 2 ; i <= m ; ++ i) {
            while(k > 0 && s[k + 1] != s[i])
                k = pi[k];
            if(s[k + 1] == s[i])
                ++ k;
            pi[i] = k;
        }
        int period = m;
        if(m % (m - pi[m]) == 0)
            period = m - pi[m];
        /*for(int i = 1 ; i <= period ; ++ i)
            cerr << s[i] << ' ';
        cerr << '\n';
        */pair<int, int> acthash = get_hash(period);
        ans = ans + _hash[acthash];
        ++ _hash[acthash];
    }
    cout << (ans * 2) + n << '\n';
}
