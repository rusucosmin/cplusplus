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

const char infile[] = "numere8.in";
const char outfile[] = "numere8.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int main() {
    const int N = 10;
    vector <int> a(N);
    for(int i = 0 ; i < N ; ++ i)
        fin >> a[i];
    int nr = 0, smax = 0, conf1smax = 0, conf2smax = 0;
    for(int i = 1 ; i < (1 << N) ; ++ i) {
        int sum1 = 0, sum2 = 0;
        for(int j = 0 ; j < N ; ++ j)
            if(i & (1 << j))
                sum1 += a[j];
        for(int j = i + 1 ; j < (1 << N) ; ++ j) {
            sum2 = 0;
            if(i & j)
                continue;
            for(int k = 0 ; k < N ; ++ k)
                if(j & (1 << k))
                    sum2 += a[k];
            if(sum1 == sum2) {
                ++ nr;
                if(smax < sum1) {
                    smax = sum1;
                    conf1smax = i;
                    conf2smax = j;
                }
            }
        }
    }
    fout << nr << ' ' << smax << '\n';
    for(int i = 0 ; i < N ; ++ i)
        if(conf1smax & (1 << i))
            fout << a[i] << ' ';
    fout << '\n';
    for(int i = 0 ; i < N ; ++ i)
        if(conf2smax & (1 << i))
            fout << a[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
