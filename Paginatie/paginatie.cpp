#include<fstream>
#include<string.h>
using namespace std;
typedef struct siruri {char c[55    ];} TSIR;
TSIR a[100][100];
ifstream cin("paginatie.in");
ofstream cout("paginatie.out");
char s[55];
int nr_col, nr_linii, lungime, i, linie=1, j, suma_linie[100],spatii_libere[101], cuvinte[1005];
int max(int a,int b)
{
    if (a>b) return a;
    else return b;}
int main()
{ 
    cin>>nr_linii>>nr_col;
    lungime=nr_col;
    i=1;
    j=0;
    while(cin>>s)
       {   if(strlen(s)<lungime)
             { 
                                strcpy(a[i][++j].c,s);
                                lungime=lungime-strlen(s)-1;
                                suma_linie[i]=suma_linie[i]+strlen(s);
                                cuvinte[i]++;
              }
           else
                {                 j=0;
                                  strcpy(a[++i][++j].c,s);
                                suma_linie[i]=suma_linie[i]+strlen(s);
                                cuvinte[i]++;  
                                  lungime=nr_col-strlen(s);
                }

           
       }
for(i=1;i<=n;i++)
    for(
       
          
                return 0;
}
