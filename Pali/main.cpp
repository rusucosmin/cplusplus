#include <fstream>
#include <string.h>
#define LMax 5005
using namespace std;
short n;
short rez;
char s[LMax];
    short i, j, p[LMax], nrmin;
void citire()
{
    ifstream cin("pali.in");
    cin.getline(s, 5001);
    n=strlen(s);
    cin.close();
}
bool palindrom(short inceput, short sfarsit)
{

    while(inceput<sfarsit)
        {if(s[inceput]!=s[sfarsit])
            return 0;
        ++inceput; --sfarsit; }
    return 1;
}
void dinamica()
{
    for(i=0;i<n;i++)
        if(palindrom(0, i))
            p[i]=1;
        else
            {
                nrmin=LMax+2;
                for(j=0;j<i;j++)
                    if (p[j]<nrmin)
                    if (palindrom(j+1, i))
                        nrmin=p[j];
                    p[i]=nrmin+1;
            }
    rez=p[n-1];
}
void afisare()
{
    ofstream cout("pali.out");
//    for(i=0;i<=n;i++)
//        cout<<p[i]<<" ";
    cout<<rez<<"\n";
    cout.close();
}
int main()
{
    citire();
    dinamica();
    afisare();
    return 0;
}
