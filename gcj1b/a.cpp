#include <bits/stdc++.h>
using namespace std;

const vector <string> digits = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
string s;
vector <int> sol, ans;
bool found;

void dfs(string act, int digit) {
    if(act.size() == s.size()) {
        sort(act.begin(), act.end());
        if(act == s)
            found = 1, ans = sol;
        return;
    }
    if(act.size() > s.size() || found || digit >= 10)
        return ;
    sol.push_back(digit);
    dfs(act + digits[digit], digit);
    sol.pop_back();
    dfs(act, digit + 1);
}

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    int t;
    cin >> t;
    int test = 0;
    while(t --) {
        cin >> s;
        sort(s.begin(), s.end());
        found = 0;
        sol.clear();
        dfs("", 0);
        cout << "Case #" << ++ test << ": ";
        for(auto it : ans)
            cout << it;
        cout << '\n';
    }
}
