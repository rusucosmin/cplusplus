#include<cstdio>
#define dim 1005

using namespace std ;

struct coord
{
	int lin, col ;
};

int dx[] = {-1, 0, 1,  0} ;
int dy[] = { 0, 1, 0, -1} ;
int a[dim][dim], L, C, totalDrept, adancimeMax, nrMax, t, v, top ;
coord st[dim * dim] ;

void Citire()
{
	int i, j, x ;
	freopen("dreptunghiuri2.in", "r", stdin) ;
	scanf("%d %d", &L, &C) ;
	for (i=1 ; i<=L ; i++)
		for (j=1 ; j<=C ; j++)
		{
			scanf("%d", &x) ;
			a[i][j] = -x ;
		}
}

inline int Interior(int x, int y)
{
	return ( x>=0 && x<=L+1 && y>=0 && y<=C+1 ) ;
}

/*void Fill_1(int x, int y)
{
	if ((a[x][y] == 0) && Interior(x,y))
	{
		a[x][y] = v ;
		Fill_1(x+1, y) ;
		Fill_1(x, y+1) ;
		Fill_1(x-1, y) ;
		Fill_1(x, y-1) ;
	}
}
*/
void Fill_1(int x, int y)
{
	int x1, y1, i ;
	top = 0 ;
	st[top].lin = x ;
	st[top].col = y ;
	a[x][y] = v ;
	while (top >= 0)
	{
		x = st[top].lin ;
		y = st[top].col ;
		top-- ;
		for (i=0 ; i<4 ; i++)
		{
			x1 = x + dx[i] ;
			y1 = y + dy[i] ;
			if (Interior(x1,y1))
			if (a[x1][y1] == 0)
			{
				a[x1][y1] = v ;
				top++ ;
				st[top].lin = x1 ;
				st[top].col = y1 ;
			}
		}
	}
}

void Fill(int x, int y)
{
	int x1, y1, i ;
	top = 0 ;
	st[top].lin = x ;
	st[top].col = y ;
	a[x][y] = v ;
	while (top >= 0)
	{
		x = st[top].lin ;
		y = st[top].col ;
		top-- ;
		for (i=0 ; i<4 ; i++)
		{
			x1 = x + dx[i] ;
			y1 = y + dy[i] ;
			if (a[x1][y1] == t)
			{
				a[x1][y1] = v ;
				top++ ;
				st[top].lin = x1 ;
				st[top].col = y1 ;
			}
		}
	}
}

void Calcul()
{
	int i, j ;
	totalDrept = adancimeMax = nrMax = 0 ;
	for (i=1 ; i<=L ; i++)
		for (j=1 ; j<=C ; j++)
			if (a[i][j] <= 0)
			{
				v = a[i-1][j-1]+1 ;
				if (v % 2 == 0)
				{
					totalDrept++ ;
					if (adancimeMax < v)
					{
						adancimeMax = v ;
						nrMax = 1 ;
					}
					else if (adancimeMax == v) nrMax++ ;
				}
				t = a[i][j] ;
				Fill(i, j) ;
			}
}

void Afisare()
{
	freopen("dreptunghiuri2.out", "w", stdout) ;
	printf("%d %d %d\n", totalDrept, adancimeMax/2, nrMax) ;
}
void write()
{
    for(int i=1;i<=L;++i)
        {
            for(int j=1; j<=C; ++j)
                printf("%d ", a[i][j]);
            printf("\n");
        }
}
int main()
{
	Citire() ;
	v = 1 ;
	Fill_1(0,0) ;
	Calcul() ;
	Afisare() ;
  //  write();
	return 0 ;
}

