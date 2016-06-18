#include <bits/stdc++.h>

using namespace std;

int ans;
string ansa, ansb;

inline int abs(int a, int b) { return max(a - b, b - a); }

void dfs2(int pos, int vala, int valb, string a, string b) {
    if(pos == b.size()) {
        if(ans > abs(vala - valb)) {
            ans = abs(vala - valb);
            ansa = a;
            ansb = b;
        }
        else if(ans == abs(vala - valb)) {
            if(ansa > a)
                ansa = a;
            else if(ansa == a)
                if(ansb > b)
                    ansb = b;
        }
        return ;
    }
    if(b[pos] == '?')
        for(int i = 0 ; i < 10 ; ++ i) {
            b[pos] = i + '0';
            dfs2(pos + 1, vala, valb * 10 + i, a, b);
        }
    else
        dfs2(pos + 1, vala, valb * 10 + b[pos] - '0', a, b);
}

void dfs1(int pos, int vala, int valb, string a, string b) {
    if(pos == a.size()) {
        dfs2(0, vala, valb, a, b);
        return ;
    }
    if(a[pos] == '?') {
        for(int i = 0 ; i < 10 ; ++ i) {
            a[pos] = i + '0';
            dfs1(pos + 1, vala * 10 + i, valb, a, b);
        }
    }
    else
        dfs1(pos + 1, vala * 10 + a[pos] - '0', valb, a, b);
}

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    int t;
    cin >> t;
    int test = 0;
    while(t --) {
        ans = 0x3f3f3f3f;
        string a, b;
        cin >> a >> b;
        dfs1(0, 0, 0, a, b);
        cout << "Case #" << ++test << ": " << ansa << ' ' << ansb << '\n';
    }
}
