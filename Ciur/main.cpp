#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

ifstream fin("ciur.in");
ofstream fout("ciur.out");

const int maxn = 2000005;

int n;
bitset <maxn> used;

int main() {
    fin >> n;
    int cnt = 1; /// 2;
    for(int i = 3 ; i <= n ; i += 2) {
        if(used[i])
            continue;
        ++ cnt;
        for(int j = i + i ; j <= n ; j += i)
            used[j] = 1;
    }
    fout << cnt << '\n';
    cerr << cnt;
}
