#include <stdio.h>
#include <string.h>

const int MAXN = 10000005;

int n, huge[MAXN];

inline void multiply(int huge[MAXN], int a) {
    int rest = 0, i;
    for(i = 1 ; i <= huge[0] || rest ; ++ i, rest = rest / 10000) {
        huge[i] = (rest += huge[i] * a) % 10000;
    }
    huge[0] = i - 1;
}

int main(void) {
    freopen("tamplar.in","r",stdin);
    freopen("tamplar.out","w",stdout);
    int n;
    huge[0] = huge[1] = 1;
    scanf("%d",&n);
    for(int i = 2 ; i < n ; ++ i)
        multiply(huge, i);
    printf("%d", huge[huge[0]]);
    for(int i=huge[0]-1; i; i--){
        printf("%04d", huge[i]);
    }
    return 0;
}
