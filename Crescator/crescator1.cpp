#include<fstream>
using namespace std;
ifstream f("crescator.in");
ofstream g("crescator.out");
long long a[2000000],l[2000000],nr[2000000];
long i,j,c;
long m=-1;
long n;
int main()
{
    
    f>>n;
    for(i=1;i<=n;i++)
    f>>a[i];
    f.close();
    for(i=1;i<=n;i++) {l[i]=1;nr[i]=1;}
    
    for(i=1;i<n;i++)
      if (a[i]<a[i+1]) 
         { l[i+1]=l[i]+1;  
           nr[i+1]=nr[i]+1;
           } 
    long max;
    max=l[1];
    
    for(i=2;i<=n;i++)
       if (l[i]>max) max=l[i];
 
    long s=0;
         
    for(i=1;i<=n;i++)
       s=s+nr[i];
       
 
    
    g<<s<<" "<<max;
    g.close();
    return 0;
}
