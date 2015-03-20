#include <fstream>
#include <string.h>
#include <string>

using namespace std;

ifstream fin("nc.in");
ofstream fout("nc.out");


char str[4005];
char c;
int u;
int sol[400000];

int main()
{
    int cuvinte = 0 ;
    char dinainte='#';

    while(fin.get(c))
    {
        if(c == '\n')
        if( dinainte=='.' )
            while(c=='.')
                fin.get(c), dinainte = c;
        if(isalpha(c) && !isalpha(dinainte))
            ++cuvinte;
        if((c == '!' || c == '.' || c == '?') && dinainte != '.')
        {
            sol[++u] = cuvinte;
            cuvinte = 0;
        }
        dinainte = c;
    }
fout << u <<"\n";
for(int i = 1 ; i <= u ; ++ i)
    fout << sol[i] << "\n";
fin.close();
fout.close();
return 0;
}
