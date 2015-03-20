#include<fstream>
using namespace std;
ifstream cin("joc8.in");
ofstream cout("joc8.out");
int main ()
{
    int li,ls,z, gasit=0,aux,bux,raspuns;
    cin>>li>>ls;
    while(!gasit && li<=ls)
    {  cin>>raspuns;
       z=(li+ls)/2;
       if (raspuns==1)
          gasit=1;
       else
           {cin>>raspuns;
              if(raspuns==1)
              ls=z-1;
              else
              li=z+1;}
    }
    if(gasit) cout<<z<<"\n";
    else cout<<"0\n";
    cin.close();
    cout.close();
    return 0;
}
                
