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

const char infile[] = "ternar.in";
const char outfile[] = "ternar.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1240;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int a[MAXN][MAXN], N, M, maxx, maxy, minx, miny;
bitset <MAXN> Used[MAXN];
long long Comp;
bool ok = true;

const int dx[] = {1, 0, -1, 0, 1,  1, 1, 1};
const int dy[] = {0, 1,  0,-1, 1, -1,-1, 1};

void DFs(int x, int y) {
    int i, j;

    queue <pair<int, int> > Q;

    Q.push(make_pair(x, y));
    Used[x][y] = 1;
    Comp = 1;

    while (!Q.empty()) {
        i = Q.front().first;
        j = Q.front().second;
        Q.pop();

        minx = min(minx, i);
        miny = min(miny, j);
        maxx = max(maxx, i);
        maxy = max(maxy, j);

        for (int k = 0; k < 8; ++k)
            if (a[i + dx[k]][j + dy[k]] == 2 && !Used[i + dx[k]][j + dy[k]]) {
                Q.push(make_pair(i + dx[k], j + dy[k]));
                Used[i + dx[k]][j + dy[k]] = 1;
                ++Comp;
            } else if (a[i + dx[k]][j + dy[k]] == 0)
                ok = 0;
    }
}

int main() {
    long long Ans = 0;
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            fin >> a[i][j];
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            if(a[i][j] == 2 && !Used[i][j]){
                Comp = 0;
                minx = i;
                miny = j;
                maxx = i;
                maxy = j;
                ok = true;
                DFs(i, j);
                if(ok && 1LL * (maxx - minx + 1) * (maxy - miny + 1) == Comp && 1LL * (maxx - minx + 3) * (maxy - miny + 3) > Ans)
                    Ans = (maxx - minx + 3) * (maxy - miny + 3);
            }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
