#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("radixsort.in");
ofstream fout("radixsort.out");

const int bucket = 8;
const int bytes = 32;
const int times = bytes / bucket;
const int lim = (1 << 8);
const int mask = lim - 1;

inline void radixsort(vector <int> &v, int n) {
    vector <int> act(n);
    for(int i = 0 ; i < times ; ++ i) {
        vector <int> cnt(lim, 0);
        for(auto it : v)
            ++ cnt[(it >> (i * bucket)) & mask];
        for(int i = 1 ; i < lim ; ++ i)
            cnt[i] += cnt[i - 1];
        for(int j = v.size() - 1 ; j >= 0 ; -- j)
            act[-- cnt[(v[j] >> (i * bucket)) & mask]] = v[j];
        v = act;
    }
}

int main() {
    int n, a, b, c;
    vector <int> v;
    fin >> n >> a >> b >> c;
    v.push_back(b);
    for(int i = 2 ; i <= n ; ++ i)
        v.push_back((1LL * a * v.back() + b)%c);
    radixsort(v, n);
    for(int i = 0 ; i < n ; i += 10)
        fout << v[i] << ' ';
}
