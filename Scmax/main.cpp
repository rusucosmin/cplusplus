#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cassert>

using namespace std;

ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int maxn = 100005;
const int mod = 66013;

int n, m, a[maxn], v[maxn], cnt;
set <int> s;
vector <pair<int, int> > _hash[mod];

inline void insert_hash(int pos, int value) {
    int key = pos % mod;
    _hash[key].push_back(make_pair(pos, value));
}

inline int gethash(int pos) {
    int key = pos % mod;
    for(vector <pair<int, int> > :: iterator it = _hash[key].begin() ; it != _hash[key].end() ; ++ it)
        if(it->first == pos)
            return it->second;
    assert(false);
}

int aib[maxn], father[maxn], dp[maxn];

inline int lsb(int x) {
    return x & (-x);
}

inline void update(int pos, int value) {
    for(int i = pos ; i <= cnt ; i += lsb(i))
        if(dp[aib[i]] < dp[value])
            aib[i] = value;
}

inline int query(int pos) {
    int ret = aib[pos];
    for(int i = pos ; i > 0 ; i -= lsb(i))
        if(dp[aib[i]] > dp[ret])
            ret = aib[i];
    return ret;
}

int main() {
    fin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        fin >> a[i];
        s.insert(a[i]);
    }
    for(set<int> :: iterator it = s.begin() ; it != s.end() ; ++ it)
        insert_hash(*it, ++ cnt);
    int maxi = 1, posmax = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        int aux = gethash(a[i]);
        int pos = query(aux - 1);
        dp[i] = dp[pos] + 1;
        father[i] = pos;
        update(aux, i);
        if(maxi < dp[i]) {
            maxi = dp[i];
            posmax = i;
        }
    }
    fout << maxi << '\n';
    vector <int> ans;
    for(int i = posmax ; i ; i = father[i])
        ans.push_back(a[i]);
    for(vector <int> :: reverse_iterator it = ans.rbegin() ; it != ans.rend() ; ++ it)
        fout << *it << ' ';
}
