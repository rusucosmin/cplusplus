#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("combinari.in");
ofstream fout("combinari.out");

const int maxn = 20;

int n, m, st[maxn];

inline void back(int k) {
    if(k == m + 1) {
        for(int i = 1 ; i <= m ; ++ i)
            fout << st[i] << ' ';
        fout << '\n';
        return;
    }
    for(int i = st[k - 1] + 1 ; i <= n ; ++ i) {
        st[k] = i;
        back(k + 1);
    }
}

int main() {
    fin >> n >> m;
    back(1);
}
