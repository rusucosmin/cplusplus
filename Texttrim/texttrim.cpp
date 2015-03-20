#include <fstream>
#include<stdio.h>
#include<string.h>
using namespace std;
 
ifstream cin("texttrim.in");
ofstream cout("texttrim.out");
char s[1000000],a[10];
long long i, n,sumsum, sum,p[100],w, letterw;
int main() 
{
for(i=0;i<=26;i++)
{  cin>>p[i];
  sumsum+=p[i];}
cin.getline(a, 10);
cin.getline(s,1000000);
int pos=-1;
n=strlen(s);
cin>>w;
long long sum=0;
for(i=0;i<n;i++)
       {               
                       
                       if(s[i]==' ')   letterw=p[0];           
                       else letterw=p[s[i]-'a'+1];
                       if(sum+letterw<=w-3) pos=i;                   
                       sum+=letterw; }

if (sum <= w) { cout<<s<<"\n"; fputs(s, texttrim.out); }

else { 
    for ( i = 0; i <= pos; i++) cout<<s[i];
    cout<<"...\n";
}
                                  

return 0;


}
