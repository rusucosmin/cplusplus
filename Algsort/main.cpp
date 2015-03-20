#include <fstream>
#include <vector>

using namespace std;

ifstream fin("algsort.in");
ofstream fout("algsort.out");

const int lim = 1 << 8;
const int mask = lim - 1;

inline void radixsort(vector <int> &v, int n) {
    vector <int> act(n);
    for(int i = 0 ; i < 4 ; ++ i) {
        vector <int> cnt(lim);
        for(auto it : v)
            ++ cnt[(it >> (i * 8) & mask)];
        for(int i = 1 ; i < lim ; ++ i)
            cnt[i] += cnt[i - 1];
        for(int j = v.size() - 1 ; j >= 0 ; -- j)
            act[-- cnt[(v[j] >> (i * 8)) & mask]] = v[j];
        v = act;
    }
}

int main() {
    int n; vector <int> v;
    fin >> n;
    for(int i = 0 ; i < n ; ++ i) {
        int x;
        fin >> x;
        v.push_back(x);
    }
    radixsort(v, n);
    for(int i = 0 ; i < v.size() ; ++ i)
        fout << v[i] << ' ';
}
