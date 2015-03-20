#include <s>

using namespace std;

const int MAXN = 1005;
int N;

int main() {
    freopen("sah.in", "r", stdin);
    freopen("sah.out", "w", stdout);
    scanf ("%d", &N);
    int X1=2, X2=3;
    for (int k=0; k<2; ++k) {
        for (int i=1; i<=N; ++i)
            printf ("1 ");
        printf ("\n");
    }
    for (int i=3; i<=N; i+=2) {
        for (int k=0; k<2; ++k) {
            for (int j=1; j<=N-i/2; ++j)
                printf ("%d ", X1);
            for (int j=N-i/2+1; j<=N; ++j)
                printf ("%d ", X2);
            printf ("\n");
        }
        X1+=2;
        X2+=2;
    }
    return 0;
}
