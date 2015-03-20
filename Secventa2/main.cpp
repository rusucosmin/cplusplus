#include<stdio.h>
using namespace std;
int s[50005];
int main()
{
    freopen("secv2.in","r",stdin);
    freopen("secv2.out","w",stdout);
    int n,k,i,start,start_max,end_max;
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&s[i]);
        s[i]+=s[i-1];
    }
    int min=(1<<31)-1,max=-((1<<31)-1);
    for(i=k;i<=n;i++)
    {
        if(s[i-k]<min)
        {
            min=s[i-k];
            start=i-k+1;
        }
        if(s[i]-min>max)
        {
            max=s[i]-min;
            start_max=start;
            end_max=i;
        }
    }
    printf("%d %d %d\n",start_max,end_max,max);
    return 0;
}
