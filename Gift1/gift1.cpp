/*
ID: cosmynu1
PROG: gift1
LANG: C++
*/
#include<fstream>
#include <string.h>
using namespace std;
ifstream cin("gift1.in");
ofstream cout("gift1.out");
//using namespace std;
struct person
{
       char name[20];
       int icash;
       int fcash;

}      a[12];
char s[20], x[20];
int NP, NF, u, l;
int main()
{
    cin>>NP;
    cin.getline(a[0].name, 10);
    for(int i=1;i<=NP;i++)
      { cin.getline(a[i].name, 20); }
    for(int i=1;i<=NP;i++)
       { cin.getline(x, 14);
         l=1;
   //      cout<<x;
         while(strcmp (x,a[l].name)!=0)
              l++;
         cin>>a[l].icash>>NF;
         //a[l].fcash=a[l].icash;
         cin.getline(a[0].name, 14);
         for(int j=1; j<=NF; j++)
                 {cin.getline(s,14);
                  u=1;
                  while(strcmp (s,a[u].name)!=0)
                      { u++;
                         }
              //    cout<<s<<" "<<a[u].name<<"\n";
                  a[u].fcash+=(a[l].icash/NF);
                  a[l].fcash-=(a[l].icash/NF);            
                              }
                              
                              
         }
    for(int i=1;i<=NP;i++)
         cout<<a[i].name<<" "<<a[i].fcash<<"\n";
    
    
    
    return 0;
}
