#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 1005

int n, m, a[maxn], b[maxn];
int f[maxn];
int folosit[maxn];
int aux;

/// functiile f : a - > b, n = card(a), m = card(b)

FILE *g , *fin;

void injective(int k) {
	if(k == n + 1) {

		// testam daca e surjectiva, fiind si injectiva, si afisam mesajul functie noua bijeciva


		fprintf(stdout, "Functie noua %d\n", ++aux);
		int i;
		for(i = 1 ; i <= n ; ++ i)
			fprintf(stdout, "f(%d) = %d ", a[i], f[i]);
		fprintf(stdout, "\n");
		return;
	}
	int i;
	for(i = 1 ; i <= m ; ++ i) {
		if(!folosit[b[i]]) {
			f[k] = b[i];
			folosit[b[i]] = 1;
			injective(k + 1);
			folosit[b[i]] = 0;
		}
	}
}

void surjective(int k) {
	if(k == n + 1) {
		//memset(folosit, 0, sizeof(folosit)); // foloit [i] = 0 , pentru orice i
		int i;
		for(i = 0 ; i < maxn ; ++ i)
			folosit[i] = 0;

		//f[1] = 2, f[2] = 2, f[3] =2;
		//B = {2, 3}; //
		// caz care pica ...
		for(i = 1 ; i <= n ; ++ i)
			folosit[f[i]] = 1; /// folost [toate valorile functiei] = 1

		for(i = 1 ; i <= m ; ++ i) /// in vector b, testez ca toate elementeze sa folosite
			if(folosit[b[i]] == 0) // atunci b[i] nu e in functie, nu e buna functia, nu e surjectiva, si ma opresc
				return; // ies din funcite

		/// testam daca sunt injective => nu mai avem dubluri


		fprintf(stdout, "Functie noua surjectiva %d\n", ++ aux);
		for(i = 1 ; i <= n ; ++ i)
			fprintf(stdout, "f(%d) = %d ", a[i], f[i]);
		fprintf(stdout, "\n");
		return;
	}
	int i;
	for(i = 1 ; i <= m ; ++ i) {
		f[k] = b[i];
		surjective(k + 1);
	}
}

int main() {
	fin = fopen("generarefunctii.in", "r");
	g = fopen("generarefunctii.out", "w");
	

	// citim multimea a
	fscanf(stdin, "%d", &n);
	int i;
	for(i = 1 ; i <= n ; ++ i)
		fscanf(stdin, "%d", &a[i]);
	
	// citim multimea b
	fscanf(stdin, "%d", &m);
	for(i = 1 ; i <= m ; ++ i)
		fscanf(stdin, "%d", &b[i]);

	/// facem functiile injective 
	injective(1);

	// facem functiile surjective
	surjective(1);


	/// o functie bijective = si injectiva, si surjectiva
	/// obs : functiile bijective vor fi generate de doua ori
}
