#include<stdio.h>
long n,k,b[1000007][8],a[1000007],i,t,j;
int main()
{
	freopen("divprim.in","r",stdin);
	freopen("divprim.out","w",stdout);
	b[1][0]=0;
	for(i=2;i<1000005;i++)
	{
		if(!a[i])
			for(j=i;j<1000005;j+=i)//ciur
				++a[j];
		for(j=0;j<=7;j++)//k<=7 
			b[i][j]=b[i-1][j];
		if(a[i]<=7)//daca a[i]<=7 noua pozitie
			b[i][a[i]]=i;
	}
	scanf("%ld",&t);//nr teste
	for(i=1;i<=t;i++)
	{
		scanf("%ld %ld",&n,&k);//n,k
		printf("%ld\n",b[n][k]);
	}
	return 0;
}
