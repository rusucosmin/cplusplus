#include<fstream>
#include<limits.h>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;
ifstream cin("traseu2.in");
ofstream cout("traseu2.out");
long long a[75][75],minim=LONG_MAX,i_min,j_min,ok;
long long b[100];
int i, j, k,n,m,mini;
char diez;
int cmp(int a,int b)
{
    return a < b;
}
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
     for(j=1;j<=m;j++)
       {cin>>diez;
        if(diez!='#')
      {a[i][j]=diez-'0';
       if(a[i][j]<minim)
          {minim=a[i][j];
           mini=j+(m*(i-1));
           i_min=i;
           j_min=j; }  
       b[j+(m*(i-1))]=a[i][j];}
       }
     
    //de unde incep
    sort(b+1,b+(n*m)+1,cmp);
    
    while(a[i][j]!=0)
     {     if(a[i_min-1][j_min-1]==b[mini+1]) { ok=1; i_min=i_min-1;j_min=j_min-1;mini++; cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";}
              else if(a[i_min-1][j_min]==b[mini+1]) {ok=1; i_min=i_min-1; mini++;cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";}
                 else if(a[i_min-1][j_min+1]==b[mini+1])  {ok=1; i_min=i_min-1;j_min=j_min+1; mini++;cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";}
                      else if(a[i_min][j_min-1]==b[mini+1]) {ok=1; j_min=j_min-1; mini++;cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";}                     
                           else if(a[i_min][j_min+1]==b[mini+1]) {ok=1; j_min=j_min+1; mini++;cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";} 
                                else if(a[i_min+1][j_min-1]==b[mini+1]) {ok=1; i_min=i_min+1;j_min=j_min-1; mini++;cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";} 
                                    else if(a[i_min+1][j_min]==b[mini+1]) {ok=1; i_min=i_min+1; mini++;cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";}
                                         else if(a[i_min+1][j_min+1]==b[mini+1]) {ok=1; j_min=j_min+1;i_min=i_min+1; mini++;cout<<i_min<<" "<<j_min<<" "<<b[mini-1]<<"\n";} 
                                              else {remove("traseu2.in");cout<<"Nu exista solutie!\n"; return 0;} 
                     }
    
    return 0;
}
