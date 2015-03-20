#include<fstream>
using namespace std;
ifstream fin("desen2.in");
ofstream fout("desen2.out");

int a[1002][1002],b[1002][1002],n,m;

void citire()
{
	int i,j;

	fin>>n>>m;
	for(i=1;i<=n;i++)
	  for(j=1;j<=m;j++)
	    fin>>a[i][j];
}

int stare(int i,int j)
{
	int c=0; //determina cate laturi sunt langa b[i-1][j]

	if(b[i-1][j]+b[i-1][j-1]==1) c++;   //o latura
	if(b[i-1][j]+b[i-2][j]==1) c++;     //o latura
	if(b[i-1][j]+b[i-1][j+1]==1) c++;   //o latura
	return c;
}

void construieste()
{
	int i,j;

	for(i=2;i<n;i++)
	  for(j=2;j<m;j++)
	    if(stare(i,j)!=a[i-1][j])  //numarul de linii nu e corect?
	      b[i][j]=1-b[i-1][j];     //se trece de afara->inauntru sau invers
	    else                       //nu mai e nevoie de latura
	      b[i][j]=b[i-1][j];       //e de aceiasi parte
}
/*
void afisare()
{
	int i,j;

	for(i=1;i<=n;i++)
	  {
	    for(j=1;j<=m;j++)
	      cout<<b[i][j]<<" ";
	    cout<<endl;
	  }
}
*/

void afisare2()
{
	int i,j;

	for(i=1;i<=n;i++)
	  {
	    fout<<'.';                 //scrie primul caracter
	    for(j=2;j<=m;j++)
	      {
		if(b[i][j-1]!=b[i][j]) //se schimba starea pe orizontala?
		  fout<<'|';             //DA, pune o linie verticala
		else                   //daca NU
		  fout<<'.';             //pune punct
		if(b[i+1][j]!=b[i][j]) //se schimba starea pe verticala?
		  fout<<'_';             //DA, pune o linie orizontala
		else                   //daca NU
		  fout<<'.';             //pune punct
	      }
	    fout<<'\n';                //treci la linia urmatoare
	  }
}

int main()
{
	citire();
	construieste();
//	afisare();
	afisare2();
	fout.close();
	return 0;
}
