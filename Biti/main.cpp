#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

int main()
{
    ofstream g("cifra.out");
    ifstream f("cifra.in");
    int  i,T;
    int sol=0, final;
    char s[1000000];


    f>>T;
    for(i=1;i<=T;i++)
     {
                     f.getline(s,10000);
                     final=strlen(s);

                     sol+=pow(s['final'-'0'], s['final'-'0']);

                     g<<sol%10<<"\n";


     }
g.close();
f.close();
return 0;


}
