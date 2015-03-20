#include<fstream>
#include<string.h>
using namespace std;
ifstream cin("7segmente.in");
ofstream cout("7segmente.out");
int main()
{
    int a[10];
    long long n, p, aux,s=0, putere=0;
  //  char n[100000000000000000000] ;
    a[1]=2; a[2]=5; a[3]=5; a[4]=4; a[5]=5; a[6]=6; a[7]=3; a[8]=7; a[9]=6;
    cin>>n;
    cin>>p;
    aux=n;
    while(aux!=0)
    {   s+=a[aux%10];
        aux=aux/10; 
        }
        cout<<s<<" ";
    if(s<=p)
        {cout<<s<<" "<<n;
        return 0;}
    else
        { n=n-10*putere;
          
    
    
        return 0;
        }
