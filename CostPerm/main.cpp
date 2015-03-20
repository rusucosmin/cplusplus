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

const char infile[] = "costperm.in";
const char outfile[] = "costperm.out";

//ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

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

int N, A[MAXN];
long long Ans;
int aib[MAXN];

inline int lsb(const int &conf) {
    return conf & (-conf);
}

inline int Query(const int &pos) {
    int sum = 0;
    for(int i = pos ; i ; i -= lsb(i))
        sum += aib[i];
    return sum;
}

inline void Update(const int &pos) {
    for(int i = pos ; i <= N ; i += lsb(i))
        ++ aib[i];
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> A[i];
        Ans += 1LL * A[i] * (Query(N) - Query(A[i] - 1));
        Update(A[i]);
    }
    fout << Ans << '\n';
    fout.close();
    return 0;
}
