#include <fstream>
#include <iostream>
#include <bitset>

using namespace std;

ifstream fin("permutari.in");
ofstream fout("permutari.out");

const int maxn = 100;

int n, st[maxn];
bitset <maxn> used;

inline void back(int p) {
    if(p == n + 1) {
        for(int i = 1 ; i <= n ; ++ i)
            fout << st[i] << ' ';
        fout << '\n';
        return ;
    }
    for(int i = 1 ; i <= n ; ++ i)
        if(!used[i]) {
            used[i] = 1;
            st[p] = i;
            back(p + 1);
            used[i] = 0;
        }
}

int main() {
    fin >> n;
    back(1);
}
