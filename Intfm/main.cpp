#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

typedef pair<int, int> per;

ifstream fin("intfm.in");
ofstream fout("intfm.out");

int N, cnt;
pair<per, per> v[4*2005];
set <int> S;
unordered_map<int, int> M;
unordered_map<int, int> dp;

inline int getIndex(const int &A, const int &B) {
    return A * cnt + B;
}

int Memoization(const int &a, const int &b) {
    if(a >= b)
        return 0;
    if(dp.find(getIndex(a, b)) != dp.end())
        return dp[getIndex(a, b)];
    int r = 0, z = 0;
    for(int i = 1 ; i <= N ; ++ i)
        if(a <= v[i].first.first && v[i].second.second <= b) {
            ++ z;
            r = max(r, Memoization(v[i].first.second, v[i].second.first) + Memoization(v[i].second.second, b) + 1);
            if(z > 100)
                break;
        }
    dp[getIndex(a, b)] = r;
    return r;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int a, b;
        fin >> a >> b;
        int st = (b - a) / 5;
        v[i].first.first = a;
        v[i].first.second = a + 2*st;
        v[i].second.first = a + 3*st;
        v[i].second.second = b;
        S.insert(a);
        S.insert(a + 2*st);
        S.insert(a + 3*st);
        S.insert(b);
    }
    for(set<int> :: iterator it = S.begin(), fin = S.end(); it != fin ; ++ it)
        M[*it] = ++cnt;
    for(int i = 1 ; i <= N ; ++ i) {
        v[i].first.first = M[v[i].first.first];
        v[i].first.second = M[v[i].first.second];
        v[i].second.first = M[v[i].second.first];
        v[i].second.second = M[v[i].second.second];
    }
    sort(v + 1, v + N + 1);
    fout << Memoization(v[1].first.first, cnt) << '\n';
    return 0;
}
