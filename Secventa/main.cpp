#include <fstream>
#include <deque>
#include <ctype.h>
#include <string.h>
using namespace std;

ifstream cin("secventa.in");
ofstream cout("secventa.out");
deque <int> dq;
char s[35000005];
int nr, u, semn;
int n, k, a[500005], i, maxi=-((1<<31)-1), st, dr, j;
inline int max(int a, int b)
{
    if(a>b) return a;
    return b;
}
int main()
{
    cin>>n>>k;
    cin.get();
    cin.getline(s,3500005);
    i=j=0;
    for(i=1;i<=n;++i)
        {
            nr=0;
            semn=1;
            if(s[j]=='-')
                semn=-1,++j;
            for(;s[j]!=' ' && s[j]!='\0';++j)
                nr*=10,nr+=(s[j]-'0');
            ++j;
            a[i]=nr*semn;
            while(!dq.empty() && a[dq.back()]>=a[i])
                dq.pop_back();
            dq.push_back(i);
            if(dq.front()==i-k)
                dq.pop_front();
            if(i>=k)
                if(maxi<a[dq.front()])
                    {
                        maxi=a[dq.front()];
                        dr=i;
                    }
        }
 //   while(a[st-1]>=maxi && st>1)
   //     --st;
    cin.close();
    cout<<dr-k+1<<" "<<dr<<" "<<maxi<<"\n";
    cout.close();
    return 0;
}
