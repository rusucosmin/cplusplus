#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string s;
int n, k;
vector <int> pi;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    #endif // ONLINE_JUDGE
    while(getline(cin, s)) {
        if(s[0] == '.')
            break;
        n = s.size();
        pi.resize(n);
        k = pi[0] = -1;
        for(int i = 1 ; i < n ; ++ i) {
            while(k != -1 && s[k + 1] != s[i])
                k = pi[k];
            if(s[k + 1] == s[i])
                ++ k;
            pi[i] = k;
            ///cerr << pi[i] << ' ';
        }
        cout << n / (n - pi[n - 1] - 1) << '\n';
    }


}
