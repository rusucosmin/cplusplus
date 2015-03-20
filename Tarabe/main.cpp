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

const char infile[] = "tarabe.in";
const char outfile[] = "tarabe.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, K;
int A[MAXN], B[MAXN];

inline bool Check(long long maxvalue) {
    long long ret = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        if(A[i] > maxvalue)
            continue;
        ++ ret;
        long long aux = maxvalue - A[i];
        ret += aux / B[i];
    }
    return ret >= K;
}

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> B[i] >> A[i];
    long long li = 1, ls = ((1LL << 50));
    long long ans = -1;
    while(li <= ls) {
        long long mid = li + (ls - li) / 2;
        if(Check(mid)) {
            ls = mid-1;
            ans = mid;
        }
        else li = mid+1;
    }
    long long sum = 0;
    long long cnt = 0;
    for(int i = 1 ; i <= N && K ; ++ i) {
        if(A[i] > ans)
            continue;
        long long many = ((ans - A[i]) / B[i] + 1);
        cnt += many;
        sum += ((many * A[i]) + (many * (many - 1) / 2) * B[i]);
    }
    sum -= ans * (cnt - K);
    fout << sum << '\n';
    fin.close();
    fout.close();
    return 0;
}
