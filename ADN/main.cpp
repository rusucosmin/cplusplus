#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream fin("adn.in");
ofstream fout("adn.out");

const int oo = 0x3f3f3f3f;
const int maxn = 18;
const int maxlg = 30005;

int n, pi[maxn][maxlg], lg[maxn], removedmask, cost[maxn][maxn], dp[1 << maxn][maxn];
char s[maxn][maxlg];

inline void buildpi(int ind) {
    int k = 0;
    for(int i = 2 ; i <= lg[ind]; ++ i) {
        while(k > 0 && s[ind][k + 1] != s[ind][i])
            k = pi[ind][k];
        if(s[ind][k + 1] == s[ind][i])
            ++ k;
        pi[ind][i] = k;
    }
}

inline int get(int x, int y) {
    int k = 0;
    for(int i = 1 ; i <= lg[y] ; ++ i) {
        while(k > 0 && s[x][k + 1] != s[y][i])
            k = pi[x][k];
        if(s[x][k + 1] == s[y][i])
            ++ k;
        if(k == lg[x]) {
            removedmask |= (1 << x);
            return -1;
        }
    }
    return k;
}

inline int lsb(int x) {
    return x & (-x);
}

inline void write(int conf, int node) {
    int cst = 0;
    for(int i = 0 ; i < n ; ++ i)
        if(conf & (1 << i))
            if(i != node && dp[conf ^ (1 << node)][i] + lg[node] - cost[i][node] == dp[conf][node]) {
                write(conf ^ (1 << node), i);
                cst = cost[i][node];
                break;
            }
    for(int i = cst + 1 ; i <= lg[node] ; ++ i)
        fout << s[node][i];
}

int main() {
    fin >> n;
    fin.get();
    for(int i = 0 ; i < n ; ++ i) {
        fin >> s[i] + 1;
        lg[i] = strlen(s[i] + 1);
        buildpi(i);
    }
    for(int i = 0 ; i < n ; ++ i)
        for(int j = 0 ; j < n ; ++ j) {
            if(i == j)
                continue;
            int aux = get(j, i);
            if(aux != -1)
                cost[i][j] = aux;
        }
    memset(dp, oo, sizeof(dp));
    for(int i = 0 ; i < n ; ++ i)
        dp[1 << i][i] = lg[i];
    int maxconf = 1 << n;
    for(int conf = 0 ; conf < maxconf ; ++ conf)
        for(int i = 0 ; i < n ; ++ i)
            if(conf & (1 << i))
                for(int j = 0 ; j < n ; ++ j) {
                    if(conf & (1 << j))
                        if(i == j)
                            continue;
                        dp[conf][i] = min(dp[conf][i], dp[conf ^ (1 << i)][j] + lg[i] - cost[j][i]);
                }
    int ans = 0x3f3f3f3f;
    int lastnode = 0;
    -- maxconf;
    int conf = maxconf ^ removedmask;
    for(int i = 1 ; i < n ; ++ i)
        if(dp[conf][lastnode] > dp[conf][i])
            lastnode = i;
    write(conf, lastnode);
}
