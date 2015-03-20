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

const char infile[] = "algsort.in";
const char outfile[] = "algsort.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 500005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int lim = (1 << 20);
char buff[lim];
int pos;

int N, v[MAXN];

inline void getInt(int &x) {
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    x = 0;
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

inline void QuickSort(int left, int right) {
    if(left >= right)
        return;
    int pos = (left + right) / 2;
    int pivot = v[pos];
    int i = left;
    int j = right;
    while(i <= j) {
        while(i < right && v[i] < pivot)
            ++ i;
        while(left < j && v[j] > pivot)
            -- j;
        if(i <= j) {
            swap(v[i], v[j]);
            ++ i;
            -- j;
        }
    }
    QuickSort(left, j);
    QuickSort(i, right);
}

int main() {
    freopen(infile, "r", stdin);
    srand(time(NULL));
    getInt(N);
    for(int i = 1 ; i <= N ; ++ i)
        getInt(v[i]);
    QuickSort(1, N);
    for(int i = 1 ; i <= N ; ++ i)
        fout << v[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
