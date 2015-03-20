#include<fstream>
using namespace std;
int st[1003],n, k, sir[1003],suma[1003],s,contor=0;
ifstream cin("take5.in");
ofstream cout("take5.out");
void back(int p)
{ int pval; //valorile pentru nivelul p;
  for(pval=st[p-1]+1;pval<=n&&suma[p-1]<s;pval++)
    {st[p]=pval;
       suma[p]=suma[p-1]+sir[pval];
        if(p==5 && suma[p]==s) 
           contor++;
        //else
         back(p+1);}}
int main()
{    int i;
     cin>>n;
     cin>>s;
     for(i=1;i<=n;i++)
     cin>>sir[i];
     back(1);
     cout<<contor;
     cin.close();
     cout.close();
     return 0;}
