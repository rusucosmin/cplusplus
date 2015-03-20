#include<fstream>
using namespace std;
unsigned long long n, sir[1002],st[1002],suma[1002],k, contor=0,i, s;
void back(int p)
{    unsigned int pval;
     for(pval=st[p-1]+1;pval<=n&&suma[p-1]<s;pval++)
       { st[p]=pval;
         suma[p]=suma[p-1]+sir[pval];
          if(suma[p]==s&&p==5)
            contor++;
         // else
            back(suma[p]+1);}
} 
int main()
{
    ifstream cin("take5.in");
    ofstream cout("take5.out");
    cin>>n;
    cin>>s;
    for(i=1;i<=n;i++)
    cin>>sir[i];
    back(1);
    cout<<contor;
    return 0;
}
