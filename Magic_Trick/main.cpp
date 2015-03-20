/* http://www.codechef.com/JAN14/problems/MTRICK
 * Problema merge pe datele din exemplu. S-ar putea ca inmultirea
 * sa cauzeze arithmetic overflow, si atunci trebuie implementata
 * cu numere mari. Complexitate O(N)
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXN = 1010;

int main() {
	int t, testNum;
	scanf("%d", &t);
	for (testNum = 0; testNum < t; ++testNum) {
		// CITIRE
		int n, i;
		scanf("%d", &n);
		unsigned long long l[MAXN], a, b, c;
		for (i = 0; i < n; ++i) {
			scanf("%llu", &l[i]);
		}
		scanf("%llu%llu%llu", &a, &b, &c);
		char s[MAXN];
		scanf("%s", s);

		/* Variabila index merge de la 0 la n-1 in mod normal.
		 * In cazul unei inversari se schimba intre ele indexul
		 * curent si finalul secventei, si termenul de incrementare
		 * isi schimba semnul.
		 * Un numar x adunat si inmultit repetat cu orice numar poate
		 * fi exprimat si ca doua operatii x * multTerm + sumTerm
		 * Explicatie:
		 *    (x * multTerm + sumTerm) + k = x * multTerm + (sumTerm + k)
		 *    (x * multTerm + sumTerm) * k = x * (multTerm * k) + (sumTerm * k)
		 * Astfel, ajung doua variabile multTerm si sumTerm (initializate
		 * cu 0 si 1) care doar se modifica dupa fiecare operatie de adunare
		 * si inmultire. N-am verificat, dar sunt destul de sigur ca asta
		 * e valabil si modulo c.
		 */
		int first = 0, last = n - 1, inc = 1, rev = 0;
		unsigned long long sumTerm = 0, multTerm = 1;
		for (i = 0; i < n; ++i) {
            bool inverted = false;
			if (s[i] == 'R') { // Inversarea secventei
                swap(first, last);
                ++ rev;
			} else if (s[i] == 'A') { // Adunare
				sumTerm = (sumTerm + a) % c;
			} else if (s[i] == 'M') { // Inmultire
				multTerm = (multTerm * b) % c;
			}
            printf("first = %d last = %d\n", first + 1, last+1);
		}
		printf("\n");
	}
	return 0;
}
