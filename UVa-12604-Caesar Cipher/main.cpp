#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

const int maxs = 500005;
const int maxw = 50005;
const int maxa = 70;

char a[maxa], w[maxw], s[maxs];
int n, lena, lenw, lens, pi[maxw];
unordered_map<char, int> where;

inline void buildprefix() {
    int k = pi[0] = -1;
    for(int i = 1 ; i < lenw ; ++ i) {
        while(k != -1 && w[k + 1] != w[i])
            k = pi[k];
        if(w[k + 1] == w[i])
            ++ k;
        pi[i] = k;
    }
}

inline bool getmatches() {
    int cnt = 0;
    int k = -1;
    for(int i = 0 ; i < lens ; ++ i) {
        while(k != -1 && w[k + 1] != s[i])
            k = pi[k];
        if(w[k + 1] == s[i])
            ++ k;
        if(k == lenw - 1)
            if(++ cnt >= 2)
                return false;
    }
    return cnt;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
    cin.sync_with_stdio(false);
    cin >> n;
    cin.get();
    while(n --) {
        cin.getline(a, maxa);
        cin.getline(w, maxw);
        cin.getline(s, maxs);
        lena = strlen(a);
        lenw = strlen(w);
        lens = strlen(s);
        where.clear();
        for(int i = 0 ; i < lena ; ++ i)
            where[a[i]] = i;
        vector <int> ans;
        for(int i = 0 ; i < lena ; ++ i) {
            buildprefix();
            bool v = getmatches();
            if(v == 1)
                ans.push_back(i);
            for(int j = 0 ; j < lenw ; ++ j)
                w[j] = a[(where[w[j]] + 1) % lena];
        }
        if(ans.size() == 0)
            cout << "no solution\n";
        else
            if(ans.size() == 1)
                cout << "unique: " << ans[0] << '\n';
            else {
                cout << "ambiguous: ";
                cout << ans[0];
                for(int i = 1 ; i < ans.size() ; ++ i)
                    cout << ' ' << ans[i];
                cout << '\n';
            }
    }

}
