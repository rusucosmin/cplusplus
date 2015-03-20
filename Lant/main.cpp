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

string file = "lant";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 155;
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

vector <string> W;
vector <int> G[MAXN];
int K, N, D[35][35], C[MAXN][MAXN], Sol;

inline int Levensthein(string a, string b) {
    int n = a.size();
    int m = b.size();
    memset(D, 0, sizeof(D));
    for(int i = 0 ; i <= n ; ++ i)  D[i][m] = n - i;
    for(int i = 0 ; i <= m ; ++ i)  D[n][i] = m - i;
    for(int i = n - 1 ; i >= 0 ; -- i)
        for(int j = m - 1 ; j >= 0 ; -- j) {
            D[i][j] = min(D[i+1][j] + 1, D[i][j+1] + 1);
            if(a[i] == b[j])
                D[i][j] = min(D[i][j], D[i+1][j+1]);
        }
    return D[0][0];
}

inline void DFs(int Pos, int Word) {
    bool Leaf = true;
    for(int j = Word + 1 ; j <= N ; ++ j)
        if(C[Word][j] <= K) {
            Leaf = false;
            DFs(Pos+1, j);
        }
    if(Leaf)
        ++ Sol;
}

int main() {
    cin >> K;
    string s;
    char chars[] = ",:;.!?-";
    while(cin >> s)
        W.push_back(s);
    N = W.size();
    for(int i = 0 ; i < N - 1 ; ++ i)
        for(int j = i + 1 ; j < N ; ++ j)
            C[i+1][j+1] = Levensthein(W[i], W[j]);
    for(int i = 2 ; i <= N ; ++ i)
        if(C[1][i] <= K)
            DFs(2, i);
    cout << Sol << '\n';
    cin.close();
    cout.close();
    return 0;
}
