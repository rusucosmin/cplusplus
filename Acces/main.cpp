#include<fstream>
#define min(A,B)	( (A) < (B) ? (A):(B))
//#define gandac
using namespace std;
ifstream cin("acces.in");
ofstream cout("acces.out");
int a[1002][1002], i, j,l, c,q, x,y, b[1002][1002];

int main()
{
    cin>>l>>c;
    for(i=1;i<=l;i++)
                     for(j=1;j<=c;j++)
                                     cin>>a[i][j];

    	// prima linie
	for (i=1 ; i<=c ; i++)
		if (a[1][i] == 1) b[1][i] = 0;
		else b[1][i] = b[1][i-1] + 1;

	// prima coloana:
	for (i=1 ; i <= l ; i++)
		if (a[i][1] == 1) b[i][1] = 0 ;
		else b[i][1] = b[i-1][1] + 1 ;

	// construiesc restul matricei
	for (i=2 ; i <= l ; i++)
		for (j=2 ; j<=c ; j++)
			if (a[i][j] == 1) // perete
			{
				if ( (b[i-1][j] == 0) || (b[i][j-1] == 0) )
					b[i][j] = 0 ;
				else if ( (b[i-1][j] > 0) && (b[i][j-1] > 0) )
					b[i][j] = -b[i-1][j-1] ;
				else b[i][j] = min(b[i-1][j], b[i][j-1]);
			}
			else // liber!
			{
				if ( (b[i-1][j] > 0) && (b[i][j-1] > 0) )
				{
					b[i][j] = 1 + b[i-1][j] + b[i][j-1] ;
					if (b[i-1][j-1] < 0)
						b[i][j] = b[i][j] + b[i-1][j-1] ;
					else
						b[i][j] = b[i][j] - b[i-1][j-1] ;
				}
				else
					if (b[i-1][j] > 0) b[i][j] = 1 + b[i-1][j] ;
					else if (b[i][j-1] > 0) b[i][j] = 1 + b[i][j-1] ;
					else b[i][j] = 1 ;
			}
#ifdef gandac
    for(i=1;i<=l;i++)
                   { for(j=1;j<=c;j++)
                                    cout<<b[i][j]<<" ";
                    cout<<"\n";}
#endif
    cin>>q;
    for(i=1;i<=q;i++)
                      {cin>>x>>y;
                       cout<<b[x][y]<<"\n";}
    return 0;
}

