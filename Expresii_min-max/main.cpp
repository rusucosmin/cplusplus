#include <fstream>
#include <string.h>
#include <ctype.h>
//#define debugging
using namespace std;

ifstream cin("emm.in");
ofstream cout("emm.out");

char s[100005];
int i, j;
long long x, y, kp, n, aux, k;
bool ok;
int v[100001], p[100001];
// -1 -minim
// -2 -maxim
inline int min(int a, int b)
{
    if(a<b)
        return a;
    else return b;
}
inline int max(int a, int b)
{
    if(a>b)
        return a;
    else return b;
}
int main()
{
    cin.getline(s, 100001);
    n=strlen(s);
    i=0;
    while(i<n)
    {
        if(isdigit(s[i]))
        {
            x=(s[i]-'0');
            i++;
            while(isdigit(s[i]))
            {
                    x=x*10+(s[i]-'0');
                    i++;
            }
    //        if(v[k]==-1)
    //            {
    //                k--;
    //                v[k]=min(x, v[k]);
    //            }
    //        else if(v[k]==-2)
    //            {
    //                k--;
    //               v[k]=max(x, v[k]);
    //            }
    //        else
    //            {
                    k++;
                    v[k]=x;
    //            }
        }
        if(s[i]=='m')
            {
                k++;
                v[k]=-1;
            }
        if(s[i]=='M')
            {
                k++;
                v[k]=-2;
            }
        if(s[i]=='(')
            {
                kp++;
                p[kp]=k+1;
            }
        if(s[i]==')')
            {
                aux=v[p[kp]];

                for(j=p[kp]+1;j<=k-1;j+=2)
                {
         #ifdef debugging
                cout<<aux<<"   "<<v[j+1]<<"\n";
         #endif
                    if(v[j]==-1)
                        aux=min(aux, v[j+1]);
                    else if(v[j]==-2)
                        aux=max(aux, v[j+1]);
                }
                k=p[kp];
                v[k]=aux;
                kp--;
            }
        i++;
    }
    aux=v[1];
    for(i=2;i<=k;i+=2)
        {
        #ifdef debugging
                cout<<aux<<"   "<<v[j+1]<<"\n";
         #endif
            if(v[i]==-1)
                aux=min(aux, v[i+1]);
            else if(v[i]==-2)
                aux=max(aux, v[i+1]);
        }
    cout<<aux<<" ";
    return 0;
}
