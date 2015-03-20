#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>

using namespace std;

#define Nmax 10001
#define Mmax 100001

struct edge{

    short x;
    short y;
    int c;
    bool uz;

} Arb[Mmax];

bitset <Mmax> viz;
vector <edge> v;

short TATA[Nmax], RANG[Nmax];

int N, M, K, COST, MAXIM;

int poz( int p, int u ){

    int m = -1;

    while ( p < u ){

        if ( Arb[p].c > Arb[u].c ){

            swap(Arb[p].x, Arb[u].x);
            swap(Arb[p].y, Arb[u].y);
            swap(Arb[p].c, Arb[u].c);

            m = -m;
        }

        if ( m == 1 )
            p++;
        else
            u--;
    }

    return p;
}

void Sort( int p, int u ){

    if ( p < u ){

        int k = poz( p , u );

        Sort( p, k - 1);
        Sort( k + 1, u );
    }
}

int gaseste( int x ){

    int R, y;

    for ( R = x; TATA[R] != R; R = TATA[R] );

    for ( ; TATA[x] != x; ){

        y = TATA[x];
        TATA[x] = R;
        x = y;
    }

    return R;
}


void uneste(int x, int y){

    if ( RANG[x] > RANG[y] )
        TATA[y] = x;
    else
        TATA[x] = y;

    if ( RANG[x] == RANG[y] )
        RANG[y]++;
}

void KRUSKAL(){

    for ( int i = 1, j = 0; j < N - 1; i++ ){

        if ( gaseste(Arb[i].x) != gaseste(Arb[i].y) ){

            COST += Arb[i].c;
            Arb[i].uz = 1;

            MAXIM = max(MAXIM, Arb[i].c);

            uneste(gaseste(Arb[i].x), gaseste(Arb[i].y));
            j++;
        }
    }
}

int cautare(int st, int dr, int x){

    int m;

    while ( st < dr ){

        m = st + ( dr - st ) / 2;

        if ( Arb[m].c <= x )
            st = m + 1;
        else
            dr = m;
    }

    m = st + ( dr - st ) / 2;

    if ( Arb[m].c > x )
        m--;

    return m;
}


void deplasare(int poz, int a, int b, int d){


    for( int i = ++M; i > poz; i-- ){

        Arb[i] = Arb[i-1];
    }

    Arb[poz].x = a;
    Arb[poz].y = b;
    Arb[poz].c = d;
}


void init(){

    for(int i = 1; i <= N; i++)
        RANG[i] = 1,
        TATA[i] = i;
}

void construieste(){

    for(int i = 1; i <= M; i++)
        if(Arb[i].uz)
            v.push_back(Arb[i]);

    M = 0;

    for( vector <edge> ::iterator it = v.begin(); it != v.end();  ++it)
        Arb[++M] = *it;
}

void rezolva(){

    freopen("online.in", "r", stdin);
    freopen("online.out", "w", stdout);

    scanf("%d %d", &N, &M);

    for(int i = 1; i <= M; i++)
        scanf("%d %d %d", &Arb[i].x, &Arb[i].y, &Arb[i].c);

    scanf("%d", &K);

    Sort(1, M);
    init();
    KRUSKAL();
    construieste();

    printf("%d\n", COST);

    for(; K; K--){

        int a, b, c, x;

        scanf("%d %d %d", &a, &b, &c);

        if ( MAXIM < c ){

            printf("%d\n", COST);
        }
        else{

            int x = cautare( 1, M, c );
            deplasare( x + 1, a, b, c );
            init();
            COST = 0;
            KRUSKAL();

            printf("%d\n", COST);
        }
    }
}


int main(){

    rezolva();

    return 0;
}
