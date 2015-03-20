#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 1000005;

int t, pi[maxn], n;
char s[maxn];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> t;
    for(int test = 1 ; test <= t ; ++ test) {
        cin >> n;
        cin.get();
        cin.getline(s + 1, maxn);
        int k = 0;
        for(int i = 2 ; i <= n ; ++ i) {
            while(k > 0 && s[k + 1] != s[i])
                k = pi[k];
            if(s[k + 1] == s[i])
                ++ k;
            pi[i] = k;
        }
        cout << "Test case #" << test << '\n';
        for(int i = 2 ; i <= n ; ++ i)
            if(i % (i - pi[i]) == 0 && pi[i])
                cout << i << ' ' << i / (i - pi[i]) << '\n';
        cout << '\n';
    }
}
