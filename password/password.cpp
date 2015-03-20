#include<fstream>
using namespace std;
ifstream fin("password.in");
ofstream fout("password.out");
int v[26],n,rezultat;
int main()
{
int i,j;
char n[100004];
fin>>n;
for(i=0;i<strlen(n);i++)
       {
                 v[n[i]-97]++;
                 for(j=n[i]-97+1;j<=25;j++)
                       rezultat=rezultat+v[j];
        }
fout<<rezultat<<"\n";
return 0;
}
