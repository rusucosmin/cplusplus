#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int maxn = 100005;
const int maxk = 25005;
const int maxs = 30;

int n, k, s, aib[2][maxs], pi[maxk], cow[maxn], pattern[maxk];
int invariant;

inline int lsb(int x) {
    return x & (-x);
}

inline void _insert(int type, int pos, int value) {
    for(int i = pos ; i <= s ; i += lsb(i))
        aib[type][i] += value;//, cerr << "query " << i << '\n';
}

inline int sum(int type, int pos) {
    if(pos < 0)
        return -1;
    int sum = 0;
    for(int i = pos ; i > 0 ; i -= lsb(i))
        sum += aib[type][i];//, cerr << "queryadevarad " << i << '\n';
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin.sync_with_stdio(false);
    cin >> n >> k >> s;
    for(int i = 1 ; i <= n ; ++ i)
        cin >> cow[i];
    for(int i = 1 ; i <= k ; ++ i)
        cin >> pattern[i];
    invariant = 0;
    for(int i = 2 ; i <= k ; ++ i) {
        _insert(1, pattern[i], 1);
        while(invariant > 0 && ((sum(0, pattern[invariant + 1]) + 1 != sum(1, pattern[i]))||
                                (sum(0, pattern[invariant + 1] - 1) != sum(1, pattern[i] - 1)))) {
            for(int aux = invariant ; aux > pi[invariant] ; -- aux) {
                _insert(0, pattern[aux], -1);
                _insert(1, pattern[i - aux], -1);
            }
            invariant = pi[invariant];
        }
        if(sum(0, pattern[invariant + 1]) + 1 == sum(1, pattern[i]) &&
            sum(0, pattern[invariant + 1] - 1) == sum(1, pattern[i] - 1)) {
            ++ invariant;
            _insert(0, pattern[invariant], 1);
        }
        pi[i] = invariant;
    }
    invariant = 0;
    memset(aib, 0, sizeof(aib));
    vector <int> matches;
    for(int i = 1 ; i <= n ; ++ i) {
        _insert(1, cow[i], 1);
        while(invariant > 0 && (sum(0, pattern[invariant + 1]) + 1 != sum(1, cow[i]) ||
                                sum(0, pattern[invariant + 1] - 1) != sum(1, cow[i] - 1))) {
            for(int aux = invariant ; aux > pi[invariant] ; -- aux) {
                _insert(0, pattern[aux], -1);
                _insert(1, cow[i - aux], -1);
            }
            invariant = pi[invariant];
        }
        if(sum(0, pattern[invariant + 1]) + 1 == sum(1, cow[i]) &&
                                sum(0, pattern[invariant + 1] - 1) == sum(1, cow[i] - 1)) {
            ++ invariant;
            _insert(0, pattern[invariant], 1);
        }
        if(invariant == k)
            matches.push_back(i - k + 1);
    }
    cout << matches.size() << '\n';
    for(auto it : matches)
        cout << it << '\n';
}
