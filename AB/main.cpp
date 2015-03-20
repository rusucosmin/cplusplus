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

const char infile[] = "ab.in";
const char outfile[] = "ab.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 30005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, price[1005], last[MAXN];

int main() {
    cin.sync_with_stdio(false);
    int T;
    fin >> T;
    while(T -- ) {
        fin >> M >> N >> K;
        for(int i = 1 ; i <= K ; ++ i)
            fin >> price[i];
        fin >> last[1];
        for(int i = 2 ; i <= M ; ++ i) {
            fin >> last[i];
            last[i] += last[i-1];
        }
        int Ans = oo;
        sort(price + 1, price + K + 1);
        if(K == 2) {
            fout << max(M + N - last[M], last[M]) * price[1] + min(M + N - last[M], last[M]) * price[2] << '\n';
            continue;
        }
        for(int i = 0 ; i <= M ; ++ i)
            Ans = min(Ans, (i + N - last[i]) * price[1] + max(last[i], M - i) * price[2] + min(last[i], M - i) * price[3]);
        fout << Ans << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
