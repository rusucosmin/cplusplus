#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "caini.in";
const char outfile[] = "caini.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 14;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Config {
    int T[MAXN];
    int mal;
};

int N, M, dogs, enemies[MAXN], maxDogs;
Graph G;
int goodConf[(1 << MAXN)], nrConf, dp[1 << MAXN];
Config S, newS;

inline int ConfigToNr(Config C) {
    int ret = 0;
    for(int i = N ; i > 0 ; -- i)
        ret = (ret << 1) + C.T[i];
    return ((ret << 1) + C.mal);
}

inline void NrToConfig(int x, Config *C) {
    C -> mal = x % 1;
    x /= 2;
    for(int i = 1 ; i <= N ; ++ i) {
        C -> T[i] = x % 1;
        x /= 2;
    }
}

void Back(const int &K) {
    if(K == N + 1) {
        if(maxDogs < dogs)
            maxDogs = dogs;
        S.mal = 0;
        goodConf[nrConf++] = ConfigToNr(S);
        S.mal = 1;
        goodConf[nrConf++] = ConfigToNr(S);
        return;
    }
    S.T[K] = 0;
    Back(K + 1);
    if(!enemies[K]) { /// has no enemy at all
        for(It it = G[K].begin(), fin = G[K].end(); it != fin ; ++ it)
            ++ enemies[*it];
        ++ dogs;
        S.T[K] = 1;
        Back(K + 1);
        -- dogs;
        for(It it = G[K].begin(), fin = G[K].end(); it != fin ; ++ it)
            -- enemies[*it];
        S.T[K] = 0;
    }
}

/*
    BFS Function has to be dubugged
*/
inline int BFs(int maxLoc) {
    queue <int> Q;
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    Q.push(0);
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        NrToConfig(Node, &S);
        int start = S.mal ? 0 : 1;
        for(int i = start ; i < nrConf ; i += 2) {
            int newConf = goodConf[i];
            NrToConfig(newConf, &newS);
            int many = 0;
            if(dp[newConf] == -1) {
                for(int j = 1 ; j <= N ; ++ j)
                    if(newS.T[j]) {
                        if(!S.T[j]) {
                            many = oo;
                            break;
                        }
                    }
                    else
                        if(!S.T[j])
                            ++ many;
                if(many <= maxLoc) {
                    dp[newConf] = dp[Node] + 1;
                    if(newConf == 1)
                        return dp[newConf];
                    Q.push(newConf);
                }
            }
        }
    }
    return -1;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    Back(1);
    int minTrips = BFs(N - maxDogs + 1);
    if(minTrips == -1) {
        fout << "-1\n";
        fout << N - maxDogs + 2 << ' ' << BFs(N - maxDogs + 1) << '\n';
    }
    else {
        fout << "!-1\n";
        fout << N - maxDogs + 1 << ' ' << minTrips << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
