#include<fstream>
using namespace std;
const int n_max = 10001; // Definim numarul maxim de cifre al numerelor
const int m = 1000000007;
int main()
{
    unsigned int i, k;
    long long a, n, j, sol = 1, s=0;
    ifstream cin("puteri3.in");
    ofstream cout("puteri3.out");
    cin>>n>>k;
    for(j=1;j<=n;j++)
   {
    sol=1;
    a = i;
    for (i = 0; (1<<i) <= k; ++ i)  // Luam toti biti lui p la rand
    {
        if ( ((1<<i) & k) > 0) // Daca bitul i din p este 1 atunci adaugam n^(2^i) la solutie
            sol= (sol * a) % m;

            a=(a * a) % m; // Inmultim a cu a ca sa obtinem n^(2^(i+1))
    }
    s+=sol;
   }
    cout<<s<<"\n"; // Afisam solutia
}
