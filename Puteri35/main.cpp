#include <stdio.h>

inline long long desc(int i, int base) {
    long long r = 0;
    for(long long p = 1 ; i ; i /= 2 , p *= base)
        if(i & 1)
            r += p;
    return r;
}

int main() {
    int N;
    freopen("puteri35.in", "r", stdin);
    freopen("puteri35.out", "w", stdout);
    scanf("%d", &N);
    int i = 1LL, j = 1LL;
    long long x = desc(i, 3), y = desc(j, 5);
    while(i <= N && j <= N) {
        if(x <= y) {
            printf("%lld\n", x);
            x = desc(++i, 3);
        }
        else {
            printf("%lld\n", y);
            y = desc(++j, 5);
        }
    }
    while(i <= N) {
        printf("%lld\n", x);
        x = desc(++ i, 3);
    }
    while(j <= N) {
        printf("%lld\n", y);
        y = desc(++ j, 5);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
