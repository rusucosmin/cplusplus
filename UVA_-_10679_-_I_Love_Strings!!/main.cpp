#include <cstring>
#include <cstdio>

using namespace std;

#define MAX_N 100010

char T[MAX_N], P[MAX_N];
int b[MAX_N], n, m;

void kpmPreprocess() {
    int i=0, j=-1;
    b[0] = -1;
    while (i < m) {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        i++; j++;
        b[i] = j;
    }
}

bool kpmSearch() {
    int i=0, j=0;
    while (i < n) {
        while (j >= 0 && T[i] != P[j]) j=b[j];
        i++; j++;
        if (j == m) {
            return true;
            j = b[j];
        }
    }
    return false;
}

int t, q;

int main() {
    scanf("%d\n", &t);
    while (t--) {
        n = (int)strlen(gets(T));
        kpmPreprocess();
        scanf("%d\n", &q);
        while (q--) {
            m = (int)strlen(gets(P));
            if (kpmSearch())
                printf("y\n");
            else
                printf("n\n");
        }
    }
}
