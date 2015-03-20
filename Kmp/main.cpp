#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 2000005;

char a[maxn], b[maxn];
int n, m, pi[maxn], ans;
vector <int> v;

int main() {
    ifstream fin("strmatch.in");
    ofstream fout("strmatch.out");
    fin.getline(a + 1, maxn);
    fin.getline(b + 1, maxn);

    n = strlen(a + 1);
    m = strlen(b + 1);


    int k = 0;
    for(int i = 2 ; i <= n ; ++ i) {
        while(k && a[k + 1] != a[i])
            k = pi[k];
        if(a[k + 1] == a[i])
            ++ k;
        pi[i] = k;
    }

    k = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        while(k && a[k + 1] != b[i])
            k = pi[k];
        if(a[k + 1] == b[i])
            ++ k;
        if(k == n) {
            ++ ans;
            if(ans <= 1000)
                v.push_back(i - n);
        }
    }
    fout << ans << '\n';
    for(auto it : v)
        fout << it << ' ';
}
