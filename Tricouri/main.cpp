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
#include <list>

using namespace std;

const char infile[] = "tricouri.in";
const char outfile[] = "tricouri.out";

ofstream fout(outfile);

const int MAXN = 300005;
const int oo = 0x3f3f3f3f;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, P, dp[6][21], v[105], A[MAXN];
list<int> linkedList[21][21];

class Scanner {
  public:
    Scanner(string file, int buffer_size = 32768):
            buffer_size_(buffer_size) {
        file_ = fopen(file.c_str(), "r");
        buffer_ = new char[buffer_size];
        pointer_ = buffer_ + buffer_size_;
    }

    Scanner& operator>>(int &object) {
        object = 0;
        while (next() < '0' or next() > '9')
            advance();
        while (next() >= '0' and next() <= '9') {
            object = object * 10 + next() - '0';
            advance();
        }
        return *this;
    }

  private:
    char next() {
        if (pointer_ == buffer_ + buffer_size_) {
            pointer_ = buffer_;
            fread(buffer_, 1, buffer_size_, file_);
        }
        return *pointer_;
    }

    void advance() {
        ++pointer_;
    }

    FILE *file_;
    int buffer_size_;
    char *buffer_, *pointer_;
};
Scanner fin(infile);

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> A[i];
    sort(A + 1, A + N + 1, greater<int>());
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 2 ; j <= 20 ; ++ j)
            if(linkedList[j][A[i] % j].size() < 5)
                linkedList[j][A[i] % j].push_back(A[i]);
    for(int q = 1 ; q <= M ; ++ q) {
        fin >> K >> P;
        memset(dp, 0, sizeof(dp));
        v[0] = 0;
        for(int rest = 0 ; rest < P ; ++ rest)
            for(list <int> :: iterator it = linkedList[P][rest].begin(), fin = linkedList[P][rest].end();
            it != fin ; ++ it)
            v[ ++ v[0] ] = *it;
        for(int i = 1 ; i <= v[0] ; ++ i) {
            for(int k = K - 1 ; k >= 0 ; -- k)
                for(int rest = 0 ; rest < P ; ++ rest)
                    if(dp[k][rest])
                        Get_max(dp[k + 1][(rest + v[i]) % P], dp[k][rest] + v[i]);
            if(dp[1][v[i] % P] == 0)
                dp[1][v[i] % P] = v[i];
        }
        fout << ((dp[K][0] == 0) ? -1 : dp[K][0]) << '\n';
    }
    fout.close();
    return 0;
}
