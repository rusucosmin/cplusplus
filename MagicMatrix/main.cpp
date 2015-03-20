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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

#define DIM 10000
char buff[DIM];
int poz=0;

inline void read(int &numar) {
     numar = 0;
     char semn='+';
     while (buff[poz] < '0' || buff[poz] > '9') {
          semn = buff[poz];
          if (++poz == DIM)
               fread(buff,1,DIM,stdin),poz=0;
     }
     while ('0'<=buff[poz] && buff[poz]<='9') {
          numar = numar*10 + buff[poz] - '0';
          if (++poz == DIM)
               fread(buff,1,DIM,stdin),poz=0;
     }
     if (semn == '-')
          numar = -numar;
}

int main() {
    freopen("magicmatrix.in", "r", stdin);
    freopen("magicmatrix.out", "w", stdout);
    int T;
    read(T);
    srand(time(NULL));
    for(int test = 1 ; test <= T ; ++ test) {
        int N;
        read(N);
        vector <vector <int> > M(N, vector<int>(N));
        for(int i = 0 ; i < N ; ++ i)
            for(int j = 0 ; j < N ; ++ j)
                read(M[i][j]);
        vector <int> perm(N);
        long long sum = 0;
        for(int i = 0 ; i < N ; ++ i) {
            perm[i] = i;
            sum += M[i][i];
        }
        string ans = "YES";
        for(int i = 0 ; i < 5e3 ; ++ i) {
            random_shuffle(perm.begin(), perm.end());
            long long actSum = 0;
            for(int j = 0 ; j < N ; ++ j)
                actSum += M[j][perm[j]];
            if(actSum != sum) {
                ans = "NO";
                break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
