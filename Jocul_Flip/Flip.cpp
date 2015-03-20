#include<fstream>
#include<iostream>
using namespace std;
int main()
{
   long a[17][17],n,m,i,j,s=0;
   ifstream f("flip.in");
   f>>n>>m;
   for(i=1;i<=n;i++)
	   for(j=1;j<=m;j++)
		   f>>a[i][j];
	f.close();
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
			s=s+a[i][j];
		if(s<0)
			for(j=1;j<=m;j++)
				a[i][j]=-a[i][j];
		s=0;
	}
	for(j=1;j<=m;j++)
	{
		for(i=1;i<=n;i++)
			s=s+a[i][j];
		if(s<0)
			for(i=1;i<=n;i++)
				a[i][j]=-a[i][j];
		s=0;
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			s=s+a[i][j];
	ofstream g("flip.out");
	g<<s;
	g.close();
	return 0;
}
