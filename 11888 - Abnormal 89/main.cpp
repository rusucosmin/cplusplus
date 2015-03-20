#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

const int maxn = 200005;

int n, pi[maxn];
string a, r;

inline bool pali(string a) {
    for(int i = 0 ; i < a.size() / 2 ; ++ i)
        if(a[i] != a[a.size() - i - 1])
            return 0;
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> n;
    cin.get();
    for(int i = 1 ; i <= n ; ++ i) {
        getline(cin, a);
        r = a;
        reverse(r.begin(), r.end());
        a = a + a;

        int k = pi[0] = -1;
        for(int i = 1 ; i < r.size() ; ++ i) {
            while(k != -1 && r[k + 1] != r[i])
                k = pi[k];
            if(r[k + 1] == r[i])
                ++ k;
            pi[i] = k;
        }
        k = -1;
        bool okay = false;
        cerr << r << ' ' << a << '\n';
        for(int i = 0 ; i < a.size() ; ++ i) {
            while(k != -1 && r[k + 1] != a[i])
                k = pi[k];
            if(r[k + 1] == a[i])
                ++ k;
            if(k + 1 == r.size() && i - k != 0 && i != a.size() - 1)
                okay = true;
        }
        if(okay)
            cout << "alindrome\n";
        else
            if(pali(r))
                cout << "palindrome\n";
            else
                cout << "simple\n";
    }
}
