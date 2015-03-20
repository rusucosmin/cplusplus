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

const char infile[] = "volum.in";
const char outfile[] = "volum.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 760;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int n, m, a[MAXN][MAXN];
priority_queue<pair<int, pair<int, int> > > Q;
bool used[MAXN][MAXN];
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1,  0,-1};

inline bool inside(pair<int, int> x) {
    return x.first >= 1 && x.first <= n && x.second >= 1 && x.second <= m;
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1 ; j <= m ; j ++) {
            fin >> a[i][j];
            if(i == 1 || i == n || j == 1 || j == m) {
                Q.push(make_pair(-a[i][j], make_pair(i, j)));
                used[i][j] = 1;
            }
        }
    long long ans = 0;
    while(!Q.empty()) {
        int cost = -Q.top().first;
        pair<int, int> node = Q.top().second;
        Q.pop();
        for(int d = 0 ; d < 4 ; ++ d) {
            pair<int, int> newNode = make_pair(node.first + dx[d], node.second + dy[d]);
            if(!inside(newNode))
                continue;
            if(used[newNode.first][newNode.second])
                continue;
            int newcost = cost;
            if(newcost < a[newNode.first][newNode.second])
                newcost = a[newNode.first][newNode.second];
            ans = ans + newcost - a[newNode.first][newNode.second];
            Q.push(make_pair(-newcost, newNode));
            used[newNode.first][newNode.second] = 1;
        }
    }
    fout << ans;
    fin.close();
    fout.close();
    return 0;
}
