#include <fstream>
#include <string.h>
using namespace std;
int poz[100005], st[100005];
char s[100005];
int k1, k2, m, cosmin, n;
ifstream cin("parantezare.in");
ofstream cout("parantezare.out");
int main()
{
    cin.getline(s, 100003);
    n=strlen(s);
    for(int i=0; i<n; ++i)
        {
            if(s[i]=='(')
                {
                    k1++;
                    st[k1]=i;
                }
            else if(s[i]==')')
               {
                      poz[st[k1]]=i;
                      k1--;
               }

        }
    cin>>m;
    for(int i=1;i<=m; ++i)
        cin>>cosmin, cout<<poz[cosmin]<<" ";
    cout<<"\n";
    cin.close();
    cout.close();
    return 0;
}
