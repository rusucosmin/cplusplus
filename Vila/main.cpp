#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "vila";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 130;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, M, act, nr;
int D[MAXN][MAXN], E[MAXN][MAXN];

const int dx[] = {0, -1, 1,  0};
const int dy[] = {1,  0, 0, -1};

inline void Fill(int i, int j, int l, int k) {
    D[i][j] = k;
    ++ act;
    for(int d = 0 ; d < 4 ; ++ d) {
        int inou = i + dx[d];
        int jnou = j + dy[d];
        if(D[inou][jnou] == l)
            Fill(inou, jnou, l, k);
    }
}

inline void Fill2(int i, int j, int l, int k) {
    E[i][j] = k;
    for(int d = 0 ; d < 4 ; ++ d) {
        int inou = i + dx[d];
        int jnou = j + dy[d];
        if(E[inou][jnou] == l)
            Fill2(inou, jnou, l, k);
    }
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            char c;
            cin >> c;
            if(c == '-')
                D[i][j] = -1, E[i][j] = -1;
            else D[i][j] = -2;
        }
    int Ans1 = 0, Ans2 = 0, Ansi = 0, Ansj = 0, Ans3 = 0;
    for(int i = 1; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            if(D[i][j] == -1) {
                act = 0;
                Fill(i, j, -1, ++ nr);
                Ans2 = max(act, Ans2);
                Fill2(i, j, -1, act);
            }
    Ans1 = nr;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            if(D[i][j] == -2) {
                set<int> s;
                int ct = 1;
                for(int d = 0 ; d < 4 ; ++ d) {
                    int inou = i + dx[d];
                    int jnou = j + dy[d];
                    if(s.find(D[inou][jnou]) == s.end()) {
                        ct += E[inou][jnou];
                        s.insert(D[inou][jnou]);
                    }
                    if(ct > Ans3)
                        Ans3 = ct, Ansi = i, Ansj = j;
                }
            }
    cout << Ans1 << '\n' << Ans2 << '\n' << Ansi << ' ' << Ansj << ' ' << Ans3 << '\n';
    cin.close();
    cout.close();
    return 0;
}
