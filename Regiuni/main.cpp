/// moving to stdio
#include <stdio.h>
#include <vector>

using namespace std;

vector <short> a, b, c;
vector <int> Hash;
vector <int> Hash2;
int x, y, N, M, Ans;

int main() {
    freopen("regiuni.in", "r", stdin);
    freopen("regiuni.out", "w", stdout);

    scanf("%d %d", &N, &M);

    a.reserve(N);
    b.reserve(N);
    c.reserve(N);
    Hash.reserve(M);
    Hash2.reserve(M);

    for(int i = 0 ; i < N ; ++ i)
        scanf("%hd %hd %hd", &a[i], &b[i], &c[i]);

    for(int i = 0 ; i < M ; ++ i) {
        scanf("%d %d", &x, &y);
        for(int j = 0 ; j < N ; ++ j) {
            bool sign = ((a[j] * x + b[j] * y + c[j]) > 0);
            Hash[i] = ((Hash[i] * 2) + sign) % 100007;
            Hash2[i] = ((Hash2[i] * 2) + sign) % 100021;
        }
    }

    for(int i = 0 ; i < M ; ++ i) {
        bool alone = 1;
        for(int j = 0 ; j < i && alone ; ++ j)
            if(Hash[i] == Hash[j] && Hash2[i] == Hash2[j])
                alone = 0;
        Ans += alone;
    }
    printf("%d\n", Ans);
    return 0;
}
