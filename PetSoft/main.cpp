/*
    You're good, for a n00b :)) !
*/
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "petsoft.in";
const char outfile[] = "petsoft.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N;
int dp[MAXN][2];
int d[MAXN][MAXN];

///dp[i][0] = valoarea maxima pe care o pot obtine pe subarborele lui i, fara i
///dp[i][1] = valoarea maxima pe care o pot obtine pe subarborele lui i, inclusiv i
///d[i][j] = valoarea maxima pe care o pot obtine formand grupe intre poz i si j

inline void buildDP(const int &Node) {
    vector <int > v(G[Node]);
    sort(v.begin(), v.end());
    for(int i = v.size() - 1 ; i >= 0 ; -- i) {
        d[i][i] = max(dp[v[i]][1], dp[v[i]][0]);
        for(int j = i + 1 ; j < v.size() ; ++ j)
            d[i][j] = max(max(v[j] - v[i] + dp[v[i]][0] + dp[v[j]][0] + d[i + 1][j - 1],
                              max(dp[v[i]][1], dp[v[i]][0]) + d[i + 1][j]), max(dp[v[j]][1], dp[v[j]][0]) + d[i][j - 1]);
    }
    dp[Node][0] = d[0][v.size() - 1];
    v.push_back(Node);
    sort(v.begin(), v.end());
    for(int i = v.size() - 1 ; i >= 0 ; -- i) {
        if(v[i] == Node) {
            d[i][i] = -oo;
            for(int j = i + 1 ; j < v.size() ; ++ j)
                d[i][j] = max(v[j] - v[i] + dp[v[j]][0] + d[i + 1][j - 1],
                              max(dp[v[j]][0], dp[v[j]][1]) + d[i][j - 1]);
            continue;
        }
        d[i][i] = max(dp[v[i]][1], dp[v[i]][0]);
        for(int j = i + 1 ; j < v.size() ; ++ j)
            if(v[j] != Node)
                d[i][j] = max(max(v[j] - v[i] + dp[v[j]][0] + dp[v[i]][0] + d[i + 1][j - 1],
                                  max(dp[v[i]][0], dp[v[i]][1]) + d[i + 1][j]), max(dp[v[j]][0], dp[v[j]][1]) + d[i][j - 1]);
            else
                d[i][j] = max(v[j] - v[i] + dp[v[i]][0] + d[i + 1][j - 1],
                              max(dp[v[i]][0], dp[v[i]][1]) + d[i + 1][j]);
    }
    dp[Node][1] = d[0][v.size() - 1];
}

void DFs(const int &Node) {
    if(!G[Node].size()) { /// yeay we have a leaf
        dp[Node][0] = dp[Node][1] = 0;
        return ;
    }
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        DFs(*it);
    buildDP(Node);
}

int main() {
    fin >> N;
    for(int i = 2 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        G[x].push_back(i);
    }
    DFs(1);
    fout << dp[1][0] << '\n';
    fin.close();
    fout.close();
    return 0;
}
