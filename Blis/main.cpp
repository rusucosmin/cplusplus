#include <fstream>
#include <string.h>

using namespace std;

ifstream cin("blis.in");
ofstream cout("blis.out");

int k, n, b, valm, i, x, p;
char s[100005];
void maxim()
{
	if (k >= n) // iau toti bitii
	{
		valm = 0;
		for (i = 1; i <= n; i++)
			valm |= ((s[i-1]-'0') << (n - i));
	}
	else
	{
		// iau primii k biti
		x = 0;
		p = 0;
		for (i = 1; i <= k; i++)
		{
			x |= ((s[i-1]-'0') << (k - i));
			p = (p << 1) + 1;
		}
		p >>= 1;
		valm = x;
		// iau pe rand urmatorii biti de la k+1 la n
		for (i = k + 1; i <= n; i++)
		{
			x = x & p;
			x = (x << 1) + (s[i-1]-'0');
			if (valm < x) valm = x;
		}
	}
    cout << valm << "\n";
}
int main()
{
    cin>>k;
    cin.get();
    cin.getline(s, 100005);
    n = strlen(s);
    maxim();
    cin.close();
    cout.close();
    return 0;
}
