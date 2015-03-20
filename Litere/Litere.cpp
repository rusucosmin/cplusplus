#include<fstream>
using namespace std;
ifstream fin("litere.in");
ofstream fout("litere.out");
int v[26],n,rezultat;
int main()
{
int i,j;
char a;
fin>>n;
for(i=1;i<=n;i++)
       {
                 fin>>a;
                 v[a-97]++;
                 for(j=a-97+1;j<=25;j++)
                       rezultat=rezultat+v[j];
        }
fout<<rezultat<<"\n";
return 0;
}
