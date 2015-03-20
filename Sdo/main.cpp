#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("sdo.in");
ofstream fout("sdo.out");

const int maxn = 3000005;

int n, a[maxn], k;

int main() {
    fin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i)
        fin >> a[i];
    nth_element(a + 1, a + k, a + n + 1);
    fout << a[k] << '\n';
}
