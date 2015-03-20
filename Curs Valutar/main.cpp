#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

const char infile[] = "cursvalutar.in";
const char outfile[] = "cursvalutar.out";

const int MAXN = 30;

double S, r[MAXN], c1, c2;
int t, N, Z;

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d", &t);
    while(t -- ) {
        scanf("%lf %d %d", &S, &N, &Z);
        for(int i = 0 ; i < Z ; ++ i)
            r[i] = 1;
        for(int i = 0 ; i < N ; ++ i) {
            scanf("%lf", &c1);
            for(int j = 1 ; j < Z ; ++ j) {
                scanf("%lf", &c2);
                r[j] = max(r[j], 1.0*c2 / c1);
                c1 = c2;
            }
        }
        for(int j = 0 ; j < Z ; ++ j)
            S *= r[j];
        printf("%.4lf\n", S);
    }
    return 0;
}
