#include<fstream>
using namespace std;
int n, m, i, x, tip, poz, a, b, v[100005];

void adauga(int poz, int val){
	while (poz <= n){
		v[poz] += val;

		poz += (poz^(poz-1)) & poz;
	}
}
int cat(int poz){
	int rez = 0;

	while (poz > 0){
		rez += v[poz];

		poz -= (poz^(poz-1)) & poz;
	}

	return rez;
}
int caut_binar(int val){
	int li = 1, ls = n, x, gasit = -1;

	while (li <= ls){
		x = (li+ls) / 2;

		a = cat(x);
		if (a >= val){
			if (a == val)
				gasit = x;
			ls = x-1;
		}
		else
			li = x+1;
	}

	return gasit;
}

int main()
{
	ifstream f("aib.in");
	ofstream g("aib.out");

    f>>n>>m;

	for (i = 1; i <= n; i ++){
		f>>x;

		adauga(i, x);
	}

	for (i = 1; i <= m; i ++){
		f>>tip;

		if (tip == 0){
			f>>poz>>x;

			adauga(poz, x);
			continue;
		}
		if (tip == 1){
			f>>a>>b;

			g<<cat(b)-cat(a-1)<<"\n";
		}
		if (tip == 2){
			f>>a;

			g<<caut_binar(a)<<"\n";
		}
	}

	return 0;
}

