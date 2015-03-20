#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

short n, best[10003], maxim, k, L[10003], nr;
double v[10003];

short best1[10003];

int caut(double x) {
    int p, u, m;
    p = 0;
    u = nr;
    m = (p+u)/2;
    while (p <= u) {
        if (v[L[m]] < x &&  v[L[m+1]] >= x) return m;
        else if (v[L[m+1]] < x) {
            p = m + 1;
            m = (p + u)/2;
        } else {
            u = m - 1;
            m = (p + u)/2;
        }
    }
    return nr;
}


int main() {
    freopen("euro2.in","r",stdin);
    freopen("euro2.out","w",stdout);
    int i, j, poz;
    nr = 1;

    scanf("%d",&n);
    for (i = 1; i <= n; i++)
        scanf("%lf", v + i);
    best[1] = L[1] = 1;
    L[0] =  0;

    for (i = 2; i <= n; i++) {
        poz = caut(v[i]);
        best[i] = poz + 1;
        L[poz + 1] = i;
        if (nr < poz + 1)   nr = poz + 1;
    }

    for(int i = 1 ; i <= n / 2 ; ++ i)
        swap(v[i], v[n - i + 1]);

    nr = 1;
    memset(L, 0, sizeof(L));

    best1[1] = L[1] = 1;
    L[0] =  0;

    for (i = 2; i <= n; i++) {
        poz = caut(v[i]);
        best1[i] = poz + 1;
        L[poz + 1] = i;
        if (nr < poz + 1)   nr = poz + 1;
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(ans < best[i] + best1[n - i + 1] - 1 && best[i] >= 2 && best1[n - i + 1] >= 2)
            ans = best[i] + best1[n - i + 1] - 1;
    }
    printf("%d\n", ans);
    return 0;
}
