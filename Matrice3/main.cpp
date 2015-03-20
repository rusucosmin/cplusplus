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

const char infile[] = "matrice3.in";
const char outfile[] = "matrice3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 250;
const int oo = 0x3f3f3f3f;

int N, M, Q;
unsigned char Lg[MAXN];
unsigned char RMQ[8][8][MAXN][MAXN];

const int lim = (1 << 12);
char A[lim];
char buff[lim];
int pos = 0;

inline void get(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim)
            fread(buff, 1, lim, stdin), pos = 0;

    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim)
            fread(buff, 1, lim, stdin), pos = 0;
    }
}

inline bool Check(int x1, int y1, int x2, int y2, int L) {
    int lg1 = Lg[x2 - x1 + 1];
    int lg2 = Lg[y2 - y1 + 1];
    return max(max(RMQ[lg1][lg2][x1][y1],
                   RMQ[lg1][lg2][x1][y2 - (1 << lg2) + 1]),
               max(RMQ[lg1][lg2][x2 - (1 << lg1) + 1][y1],
               RMQ[lg1][lg2][x2 - (1 << lg1) + 1][y2 - (1 << lg2) + 1])) >= L;
}

int main() {
    freopen(infile, "r", stdin);
    scanf("%d %d %d", &N, &M, &Q);
    scanf("\n");
    for(int i = 1 ; i <= N ; ++ i) {
        gets(A);
        for(int j = 1 ; j <= M ; ++ j)
            if(A[j - 1] == '0')
                RMQ[0][0][i][j] = min(RMQ[0][0][i - 1][j - 1], min(RMQ[0][0][i - 1][j], RMQ[0][0][i][j - 1])) + 1;
            else RMQ[0][0][i][j] = 0;
    }
    for(int i = 2 ; i <= max(N, M) ; ++ i)
        Lg[i] = Lg[i >> 1] + 1;

    for(int k1 = 1 ; (1 << k1) <= N ; ++ k1)
        for(int i = 1 ; i + (1 << k1) - 1 <= N ; ++ i)
            for(int j = 1 ; j <= M ; ++ j)
                RMQ[k1][0][i][j] = max(RMQ[k1-1][0][i][j], RMQ[k1-1][0][i + (1 << (k1 - 1))][j]);

    for(int k2 = 1 ; (1 << k2) <= M ; ++ k2)
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j + (1 << k2) - 1 <= M ; ++ j)
                RMQ[0][k2][i][j] = max(RMQ[0][k2-1][i][j], RMQ[0][k2-1][i][j + (1 << (k2 - 1))]);
    for(int k1 = 1 ; (1 << k1) <= N ; ++ k1)
        for(int k2 = 1 ; (1 << k2) <= M ; ++ k2)
            for(int i = 1 ; i + (1 << k1) - 1 <= N ; ++ i)
                for(int j = 1 ; j + (1 << k2) - 1 <= M ; ++ j) {
                    int l1 = (1 << (k1 - 1));
                    int l2 = (1 << (k2 - 1));
                    RMQ[k1][k2][i][j] = RMQ[k1 - 1][k2 - 1][i][j];
                    RMQ[k1][k2][i][j] = max(RMQ[k1][k2][i][j], max(
                                        max(RMQ[k1-1][k2-1][i + l1][j],
                                            RMQ[k1-1][k2-1][i][j + l2]),
                                            RMQ[k1-1][k2-1][i + l1][j + l2]));
                }
    //int mata;
    //get(mata);
    for(int i = 1 ; i <= Q ; ++ i) {
        int x1, x2, y1, y2;
        ///scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        get(x1);
        get(y1);
        get(x2);
        get(y2);
        int li = 0, ls = min(x2 - x1, y2 - y1) + 1;
        int ans = 0;
        while(li <= ls) {
            int mid = ((li + ls) >> 1);
            if(Check(x1 + mid - 1, y1 + mid - 1, x2, y2, mid)) {
                ans = mid;
                li = mid + 1;
            } else ls = mid - 1;
        }
        fout << ans << '\n';
    }
    fout.close();
    return 0;
}
