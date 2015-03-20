#include <fstream>

using namespace std;

ifstream cin("cristale.in");
ofstream cout("cristale.out");

char s[105];
char x, y, z;
int p, n;

int solve()
{
    int nrA, nrB, nrC;
	nrA = nrB = nrC = 0;

	for(int i = 0; i < n; i++)
	{
		if ( s[i] == x ) nrA++;
		if ( s[i] == y ) nrB++;
		if ( s[i] == z ) nrC++;
	}

	if ( (nrA|nrB) == 0) return n;
	if ( (nrB|nrC) == 0) return n;
	if ( (nrC|nrA) == 0) return n;
	if ( nrA & nrB & nrC & 1) return 2;
	if ( !((nrA | nrB | nrC) & 1) ) return 2;
	return 1;
}
int main()
{
    //read data;
    cin >> x >> y >> z >> p;
    //solve?!
    while(p--)
    {
        cin >> n;
        cin >> s;
        cout << solve() << "\n";
    }
    cin.close();
    cout.close();
    return 0;
}
