/*
    Retin doua stive:
        - el -> unde adaug operatorii si operanzii.
            - se garanteaza cat toti operanzii sunt positivi, deci codific
            - m cu -> -1
            - M cu -> -2
        - pos -> aceasta stive retine pentru o paranteza deschisa, ce operanzi 'acopera'
*/
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

/*
m - -1
M - -2
*/

const int maxn = 100005;

int el[maxn];
int pos[maxn];

inline void solve(int st, int dr) {
    int rasp = el[st];
    for(int i = st ; i <= dr ; ++ i) {
        if(el[i] == -1)
            rasp = min(rasp, el[i + 1]);
        else if(el[i] == -2)
            rasp = max(rasp, el[i + 1]);
    }
    el[0] = st;
    el[ el[0] ] = rasp;
}

int main() {
    freopen("emm.in", "r", stdin);
    freopen("emm.out", "w", stdout);
    string s;
    getline(cin, s);
    for(int i = 0 ; i < s.size() ; ++ i) {
        if(s[i] == '(') {
            pos[++ pos[0] ] = el[0];
        }
        else if(s[i] == ')') {
            solve(pos[ pos[0] ] + 1, el[0]);
            -- pos[0];
        }
        else if(s[i] == 'm')
            el[++ el[0] ] = -1;
        else if(s[i] == 'M')
            el[++ el[0] ] = -2;
        else {
            int x = 0;
            while(isdigit(s[i])) {
                x = x * 10 + s[i] - '0';
                ++ i;
            }
            el[ ++el[0] ] = x;
            -- i;
        }
    }
    solve(1, el[0]);
    cout << el[el[0]] << '\n';
}
