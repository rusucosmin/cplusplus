#include<iostream>
#include<fstream>
using namespace std;
int sir[1000],n, s, st[1000], contor=0;
int valid(int p)
{
    int i,a=0;
    for(i=1;i<=p;i++)
    a=a+st[i];
    if(a==s)
      return 1;
    return 0;
}
      

void back(int p)
{
     int pval, i;
     for(pval=sir[p-1]+1;pval<=n;pval++)
        { st[p]=pval;
            if(valid(p))
                //if(suma(p))
                    contor++;
                else back(p+1);}
}


int main()
{
    int i;
    ifstream in("take5.in");
    ofstream out("take5.out");
    cin>>n;
    cin>>s;
    for(i=1;i<=n;i++)
         cin>>sir[i];
    back(1);
    cout<<contor;
    return 0;
}    
