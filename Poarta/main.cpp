# include <algorithm>
# include <cstdio>
# include <cmath>

const char *FIN = "poarta.in", *FOU = "poarta.out" ;
const int MOD = 997, oo = 0x3f3f3f ;

int A[105][105] ;
int X[1005], Y[1005] ;
int N, M, K, L1, C1, L2, C2 ;

inline int Nr ( int x, int y, int p, int q ) {
    int N = abs (x - p) + 1, M = abs (y - q) + 1 ;
    for ( int i = 1; i <= M; ++i ) {
        A[1][i] = 1 ;
    }
    for ( int i = 2; i <= N; ++i ) {
        A[i][1] = 1 ;
        for ( int j = 2; j <= M; ++j ) {
            A[i][j] = A[i][j - 1] + A[i - 1][j], A[i][j] %= MOD ;
        }
    }
    return A[N][M] ;
}

int main ( void ) {
    freopen ( FIN, "r", stdin ) ;

    scanf ( "%d %d %d", &N, &M, &K ) ;
    scanf ( "%d %d %d %d", &L1, &C1, &L2, &C2 ) ;
    for ( int i = 1; i <= K; ++i ) {
        scanf ( "%d %d", X + i, Y + i ) ;
    }
    int d = abs (L1 - L2) + abs (C1 - C2) ;
    int nr = Nr ( L1, C1, L2, C2 ) ;
    if ( K ) {
        int min1 = oo, nr1 = 0 ;
        for ( int i = 1; i <= K; ++i ) {
            int d2 = abs (L1 - X[i]) + abs (C1 - Y[i]) ;
            if ( d2 < min1 ) {
                min1 = d2 ;
                nr1 = Nr ( L1, C1, X[i], Y[i] ) ;
            } else if ( d2 == min1 ) {
                nr1 += Nr ( L1, C1, X[i], Y[i] ), nr1 %= MOD ;
            }
        }
        int min2 = oo, nr2 = 0 ;
        for ( int i = 1; i <= K; ++i ) {
            int d2 = abs (L2 - X[i]) + abs (C2 - Y[i]) ;
            if ( d2 < min2 ) {
                min2 = d2 ;
                nr2 = Nr ( L2, C2, X[i], Y[i] ) ;
            } else if ( d2 == min2 ) {
                nr2 += Nr ( L2, C2, X[i], Y[i] ), nr2 %= MOD ;
            }
        }
        int d2 = min1 + min2 + 1 ;
        int numar = (nr1 * nr2) % MOD ;
        if ( d2 < d ) {
            d = d2 ;
            nr = numar ;
        } else if ( d2 == d ) {
            nr += numar, nr %= MOD ;
        }
    }
    fprintf ( fopen ( FOU, "w" ) , "%d\n%d", d, nr ) ;
}
