#include<fstream>
#include<string.h>
using namespace std;
ifstream cin("incantatii.in");
ofstream cout("incantatii.out");
int  main()
{
char cuvinte[1000000][10],aux[25];
int n,i,gasit;
cin>>n;
for(i=0;i<n;i++)
{cin>>cuvinte[i];}
do
{
gasit=0;
for(i=0;i<n-1;i++)
if(strcmp(cuvinte[i],cuvinte[i+1])>0)
{
strcpy(aux,cuvinte[i]);
strcpy(cuvinte[i],cuvinte[i+1]);
strcpy(cuvinte[i+1],aux);
gasit=1;
}
}while(gasit);
for(i=0;i<n;i++) cout<<cuvinte[i]<<"\n";
return 0;
}
