#include<fstream>
using namespace std;
ifstream cin("pietre.in");
ofstream cout("pietre.out");                 
int n,i,j, a[100], s[100], l[100], poz[100];
int main()
{
    int max=-100,pozmax;
    cin>>n;
    for(i=1;i<=n;i++)
    cin>>a[i];
    for(i=n;i>0;i--)
                     for(poz[i]=-1, l[i]=1, j=i+1; j<=n;j++)
                                           if(a[i]<=a[j] && l[i]<1+l[j])
                                                         {l[i]=1+l[j]; poz[i]=j;} 
    for(i=2;i<=n;i++)
                     if(l[i]>max)
                      {max=l[i];
                      pozmax=i;}
    cout<<max;
    i=pozmax;
    while(i!=-1)
                { cout<<a[i]<<" ";
                  i=poz[i];}       
                             
                        
    
    
    
    
    
    
    return 0;
}
