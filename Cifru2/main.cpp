#include <fstream>
#include <stack>
#include <memory.h>

using namespace std;

const char infile[] = "cifru2.in";
const char outfile[] = "cifru2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MAXM = 10005;
const int oo = 0x3f3f3f3f;

int N, M, a[MAXN], b[2*MAXN];
int c[MAXN], d[2*MAXN];
int pi[MAXN];
stack <int> st[MAXM];
int first[MAXM];
int p[MAXM];

inline void buildPrefix(const int *A) {
    int K = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        while(K > 0 && A[K + 1] != A[i])
            K = pi[K];
        if(A[K + 1] == A[i])
            ++ K;
        pi[i] = K;
    }
}

/// try for a match for A in B
inline int KMP(const int *A, const int *B) {
    buildPrefix(A);
    int K = 0;
    for(int i = 1 ; i <= 2 * N ; ++ i) {
        while(K > 0 && A[K + 1] != B[i])
            K = pi[K];
        if(A[K + 1] == B[i])
            ++ K;
        if(K == N)
            return i - N;
    }
    return -1;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> a[i];
        if(!first[a[i]])
            first[a[i]] = i;
        if(!st[a[i]].empty()) {
            c[st[a[i]].top()] = (i - st[a[i]].top());
            st[a[i]].pop();
        }
        st[a[i]].push(i);
    }
    for(int i = 1 ; i <= N ; ++ i) {
        if(!c[i])
            c[i] = N - i + first[a[i]];
        while(!st[a[i]].empty())
            st[a[i]].pop();
    }
    memset(first, 0, sizeof(first));
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> b[i];
        b[i + N] = b[i];
        if(!first[b[i]])
            first[b[i]] = i;
        if(!st[b[i]].empty()) {
            d[st[b[i]].top()] = d[st[b[i]].top() + N] = (i - st[b[i]].top());
            st[b[i]].pop();
        }
        st[b[i]].push(i);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!d[i])
            d[i] = d[i + N] = N - i + first[b[i]];
    int D = KMP(c, d);
    fout << D << '\n';
    for(int i = D + 1 ; i <= D + 1 + N ; ++ i)
        p[a[i - D]] = b[i];
    for(int i = 1 ; i <= M ; ++ i)
        fout << p[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
