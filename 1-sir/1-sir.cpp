#include<fstream>
#define max_N 2
#define max_S 32640

using namespace std;

ifstream fin("1-sir.in");
ofstream fout("1-sir.out");

int N, S, D[max_N][max_S], i, j, k;

int main()
{
	fin >> N >> S;
	D[0][0] = 1;
	for(i = 1; i <= N - 1; i ++)
	{
		for(j = 0; j <= N*(N-1)/2; j ++)
			D[1][j] = D[0][j + (i - 1)] + D[0][j - (i - 1)];
		
		for(k = 0; k <= N*(N-1)/2 ; k ++)
		{
			D[0][k] = D[1][k];
			D[1][k] = 0;
		}
	}
	fout << D[0][S];
	return 0;
}
