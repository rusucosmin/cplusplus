#include<fstream>
#include<string>
using namespace std;

struct text
  {    char tcuvant[21];
       char inceput;
       int lungime;
       char sfarsit;  }  cuvant[20005];

int main()
{
    
    char c, ultimul;
    bool spatiu=0;
    int contor_cuvant=1, contor_litere=0;
    ifstream cin("text3.in");
    ofstream cout("text3.out");
    while(cin.get(c))
        {   
            if(c!=' ' && c!='\n')
            {
            
            if(spatiu==1)
                         { cuvant[contor_cuvant].lungime=contor_litere;   contor_cuvant++;contor_litere=0;}
            spatiu=0;
            contor_litere++;
            cuvant[contor_cuvant].tcuvant[contor_litere]=c;
            
            }
            else {spatiu=1;
                  ultimul=c;}
                             }
    
    for(int i=1;i<=contor_cuvant;i++)
      { cuvant[i].inceput=cuvant[i].tcuvant[1];
        cuvant[i].sfarsit=cuvant[i].tcuvant[cuvant[i].lungime];}
       for(int i=1;i<=contor_cuvant;i++)
         cout<<i<<" "<<cuvant[i].inceput<<" "<<cuvant[i].sfarsit<<"\n";
    cin.close();
    cout.close();
    return 0;
}
