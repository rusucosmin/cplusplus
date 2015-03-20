#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("arbore3.in");
ofstream fout("arbore3.out");

const int maxn = 1000005;
const int mod = 666013;
const int oo = 0x3f3f3f3f;

int n, s, v[maxn];
vector <int> g[maxn], _hash[2*mod];

inline void _insert(int value) {
    int key = value % mod + mod;
    _hash[key].push_back(value);
}

inline void _erase(int value) {
    int key = value % mod + mod;
    for(vector <int> :: iterator it = _hash[key].begin() ; it != _hash[key].end() ; ++ it)
        if(*it == value) {
            _hash[key].erase(it);
            return ;
        }
}

inline int _count(int value) {
    int key = value % mod + mod, ret = 0;
    for(vector <int> :: iterator it = _hash[key].begin() ; it != _hash[key].end() ; ++ it)
        if(*it == value)
            ++ ret;
    return ret;
}

long long ans = 0;

//// strmasii care sum - sum_stramos == S =>

inline void dfs(int node, int sum) {
    ans += _count(sum - s);
    _insert(sum);
    for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
        dfs(*it, sum + v[*it]);
    _erase(sum);
}

int main() {
    fin >> n >> s;
    for(int i = 1 ; i <= n ; ++ i) {
        int x;
        fin >> x >> v[i];
        g[x].push_back(i);
    }
    _insert(0);
    dfs(1, v[1]);
    fout << ans << '\n';
}
