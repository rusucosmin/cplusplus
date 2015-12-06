#include <iostream> // pt cin, cout

using namespace std;

int main() {
	int n; // numarul de citit
	cin >> n; // il citim
	int auxn = n; /// copiem continutuil sa nu pierdem valoarea lui n
	int invers = 0; /// variabila in care creem inversul lui n
	while(auxn > 0) /// cat timp are litere
	{
		int ultima_cifra = auxn % 10; // luam ultima cifra
		auxn = auxn / 10; /// o eliminam
		invers = invers * 10 + ultima_cifra; /// o adaug la finalul lui invers
	}
	if(invers == n) { /// daca sunt egale, e palindom
		cout << "palindrom";	
	}
	else
		cout << "nu e palindrom\n";
}
