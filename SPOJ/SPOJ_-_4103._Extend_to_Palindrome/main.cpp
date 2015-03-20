#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

char A[MAXN], B[MAXN];
int Pi[MAXN], N, K;

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(gets(A + 1)) {
        N = strlen(A + 1);
        for(int i = N ; i >= 1 ; -- i)
            B[N - i + 1] = A[i];
        B[N + 1] = '\0';
        K = 0;
        Pi[1] = 0;
        for(int i = 2 ; i <= N ; ++ i) {
            while(K > 0 && B[K + 1] != B[i])
                K = Pi[K];
            if(B[i] == B[K + 1])
                ++ K;
            Pi[i] = K;
        }
        K = 0;
        for(int i = 1 ; i <= N ; ++ i) {
            while(K > 0 && A[i] != B[K + 1])
                K = Pi[K];
            if(A[i] == B[K + 1])
                ++ K;
        }
        printf("%s", A + 1);
        puts(B + K + 1);
    }
    return 0;
}
