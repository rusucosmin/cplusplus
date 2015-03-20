#include <stdio.h>
#define MOD 2011
#define DIMN 1002
#define DIMK 1002

int D[DIMN][DIMK];
int S[DIMK];

//D[i][j] = ? siruri de lungime i cu j - consecutiv la final

int N, K, i, j;

int main() {
	FILE *f = fopen("minusk.in","r");
	fscanf(f,"%d %d",&N, &K);
	fclose(f);

	D[1][0] = 1; D[1][1] = 1;
	S[1] = 2;
	for (i=2;i<=N;i++) {
		D[i][0] = S[i-1];
		S[i] = D[i][0];
		for (j=1;j<=K-1;j++) {
			D[i][j] = D[i-1][j-1];
			S[i] = (S[i] + D[i][j]) % MOD;
		}
	}
	FILE *g = fopen("minusk.out","w");
	fprintf(g,"%d",S[N]);
	fclose(g);

}
