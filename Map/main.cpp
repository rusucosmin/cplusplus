#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 2005;

int n, m, pi[maxn];
char s[maxn];

int main() {
    ifstream fin("map.in");
    ofstream fout("map.out");

    fin >> n >> m;
    fin.get();
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        fin.getline(s + 1, maxn);
        int k = 0;
        for(int j = 2 ; j <= m ; ++ j) {
            while(k > 0 && s[k + 1] != s[j])
                k = pi[k];
            if(s[k + 1] == s[j])
                ++ k;
            pi[j] = k;
        }
        int aux = m;
        while(pi[aux] > m / 2)
            aux = pi[aux];
        ans = max(ans, aux);
    }
    fout << ans << '\n';
}
