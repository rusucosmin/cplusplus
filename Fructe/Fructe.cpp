#include <fstream>
using namespace std;
int n,p,b,i;
int main()
{
	ifstream f("fructe.in");
	ofstream g("fructe.out");
	f>>n;
	for (i=1;i<=n;i++)
	{
		f>>p>>b;
		if (b%2==0)
			g<<0<<"\n";
		else g<<1<<"\n";
	}
	f.close();
	g.close();
	return 0;
}
