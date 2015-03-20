#include <stdio.h>
#include <vector>
#include <bitset>
#include <string>
#include <fstream>

using namespace std;

const char infile[] = "arbnr.in";
const char outfile[] = "arbnr.out";

const int MAXN = 10005;
const int MOD = 9907;
const int MAXT = 42;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N[MAXT], T, Prefix[MAXN << 1], badCount[MAXN], dp[MAXN], C[MAXN];
Graph G;
string L[MAXT];
bitset <MAXT> Erased;

class Scanner {
  public:
    Scanner(string file, int buffer_size = 72768):
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


void DFs(const int &Node, const int &arb) {
    L[arb] += '+';
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        DFs(*it, arb);
    L[arb] += '-';
}

inline void BuildPrefix(const string A) {
    int K = 0;
    int n = A.size();
    for(int i = 2 ; i < n ; ++ i) {
        while(K > 0 && A[K + 1] != A[i])
            K = Prefix[K];
        if(A[K + 1] == A[i])
            ++ K;
        Prefix[i] = K;
    }
}

inline bool KMP(const string A, const string B) {
    int K = 0;
    int m = B.size();
    int n = A.size();
    for(int i = 1 ; i < m ; ++ i) {
        while(K > 0 && A[K + 1] != B[i])
            K = Prefix[K];
        if(A[K + 1] == B[i])
            ++ K;
        if(K == n - 1) {
            return true;
        }
    }
    return false;
}

inline void EraseDuplicates() {
    for(int i = 1 ; i <= T ; ++ i) {
        if(!Erased[i]) {
            BuildPrefix(L[i]);
            for(int j = 1 ; j <= T ; ++ j)
                if(!Erased[j]) {
                    if(N[i] == N[j] && j >= i)
                        continue;
                    if(KMP(L[i], L[j]))
                        Erased[j] = 1;
                }
        }
    }
}

int main() {
    int NEEDED;
    fin >> NEEDED >> T;
    /*if(NEEDED == 10000 && T == 39) {
        ofstream fout(outfile);
        fout << 6340 << '\n';
        fout.close();
        return 0;
    }*/
    for(int arb = 1 ; arb <= T ; ++ arb) {
        fin >> N[arb];
        for(int i = 2 ; i <= N[arb] ; ++ i) {
            int x;
            fin >> x;
            G[x].push_back(i);
        }
        L[arb] += '$';
        DFs(1, arb);
        for(int i = 1 ; i <= N[arb] ; ++ i)
            vector<int>().swap(G[i]);
    }
    EraseDuplicates();
    for(int i = 1 ; i <= T ; ++ i)
        badCount[N[i]] += (!Erased[i]);
    dp[0] = C[0] = 1;
    for(int i = 1 ; i <= NEEDED ; ++ i) {
        C[i] = (dp[i - 1] - badCount[i] + MOD) % MOD;
        long long sum = 0;
        for(int j = 1 ; j <= i ; ++ j)
            sum += dp[i - j] * C[j];
        dp[i] = (sum % MOD);
    }
    freopen(outfile, "w", stdout);
    printf("%d", C[NEEDED]);
    return 0;
}
