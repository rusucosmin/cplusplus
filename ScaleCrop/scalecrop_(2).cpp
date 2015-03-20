#include<fstream>
#include<math.h>
#include<iomanip>
using namespace std;
ifstream cin("scalecrop.in");
ofstream cout("scalecrop.out");

int main()
{
    long long wf, hf; //dimensiunile flyerului;
     long long wp, hp; //dimensiunile imaginii initiale
    double wpn, hpn; //dimensiunile iamginii finale;
    cin>>wf>>hf>>wp>>hp;
    //Cand dimensiunea w a flyerului este mai mica ca a imagini)
    if (wf>wp && hf>hp) 
       { if( (wf-wp)>=(hf-hp) )  { wpn=wf;
                                hpn=(wpn*hp)/wp; }
        else {hpn=hf; 
              wpn=(hpn*wp)/hp;}
              }            
    else 
     if(wf>wp  && hf<hp)   { wpn=wf;  hpn=(wpn*hp)/wp; }                 
         else   
             if(wf<wp  && hf>hp)  { hpn=hf;  wpn=(hpn*wp)/hp; }       
                 else  
                     if(wf<wp  && hf<hp)        
                            { if( (wp-wf)>=(hp-hf) ) { hpn=hf;
                                    wpn=(hpn*wp)/hp; }
                                    else {wpn=wf; 
                                         hpn=(wpn*hp)/wp;}  }
                            else {wpn=wf;
                                  hpn=hf;}
              
  cout << fixed;
  cout << setprecision (2) << wpn << " ";
  cout << setprecision (2) << hpn << "\n";

         cin.close();
         cout.close();
        return 0;
}
