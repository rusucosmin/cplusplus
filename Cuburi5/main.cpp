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

const char infile[] = "cuburi5.in";
const char outfile[] = "cuburi5.out";

ofstream fout(outfile);

const int MAXN = 50005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector <int> G[MAXN];
int dp[100005][2]; /// dp[i] = lungimea minima a unui sir care contine i
int N, K;
int last[MAXN];


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
int cubix;
int pre[100005];

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= K ; ++ j) {
            int x;
            fin >> x;
            G[i].push_back(x);
            cubix = max(cubix, x);
        }
    }
    for(int i = 1 ; i <= cubix ; ++ i) {
        dp[i][0] = -1;
        dp[i][1] = 0;
    }
    for(int i = N ; i > 0 ; -- i) {
        int maxInd = 0;
        for(int j = 1 ; j < K ; ++ j)
            if(dp[G[i][j]][1] == dp[G[i][maxInd]][1]) {
                if(dp[G[i][j]][0] <= dp[G[i][maxInd]][0])
                    maxInd = j;
            }
            else if(dp[G[i][j]][1] > dp[G[i][maxInd]][1])
                maxInd = j;
        pre[i] = dp[G[i][maxInd]][0];
        int sz = dp[G[i][maxInd]][1];
        for(int j = 0 ; j < K ; ++ j) {
            dp[G[i][j]][1] = sz + 1;
            dp[G[i][j]][0] = i;
        }
    }
    int Ans = 0;
    for(int i = 0 ; i < cubix ; ++ i)
        if(dp[Ans][1] < dp[i][1])
            Ans = i;
    int act = dp[Ans][0];
    while(act != -1) {
        fout << act << ' ';
        act = pre[act];
    }
    fout.close();
    return 0;
}
