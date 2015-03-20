#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 100005;

char s[maxn], r[maxn];
int pi[maxn], n;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin.getline(s + 1, maxn)) {
        strcpy(r + 1, s + 1);
        n = strlen(s + 1);
        for(int i = 1 ; i <= n / 2 ; ++ i)
            swap(r[i], r[n - i + 1]);
        int k = 0;
        for(int i = 2 ; i <= n ; ++ i) {
            while(k > 0 && r[k + 1] != r[i])
                k = pi[k];
            if(r[k + 1] == r[i])
                ++ k;
            pi[i] = k;
        }
        k = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            while(k > 0 && r[k + 1] != s[i])
                k = pi[k];
            if(r[k + 1] == s[i])
                ++ k;
        }
        s[n - k + 1] = '\0';
        cout << s + 1 << r + 1 << '\n';
    }


}
