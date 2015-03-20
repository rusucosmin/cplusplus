#include<fstream>
#include<algorithm>
using namespace std;
long long N, K, i;
char stk[10005];
int stk_len;
char s[10005];
bool ok[10005];
ifstream cin("alibaba.in");
ofstream cout("alibaba.out");
int main()
{
    cin>>N>>K;
    cin.get();
    cin.getline(s, 10005);
    stk_len = 0;
    int sterse=0;
    for(i=0 ; i<N , sterse<=K;)
    {
        bool oky=0;
        while((s[i]<s[i-1]))
        {
            oky=1;
      //      cout<<i<<" ";
            ++i;
        }
        sterse++;
        ok[i]=1;
        if(!oky) ++i;
    }
    for(i=1;i<=N;++i)
        if(!ok[i])
          cout<<s[i-1];

    return 0;
}
