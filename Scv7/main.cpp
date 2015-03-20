#include<cstdio>
using namespace std;
int n,v[30001];
int caut(int x,int y){
 int max=-10001,i;
 for(i=x;i<=y;i++)
  if(v[i]>max)
   max=v[i];
 return max;
}
int main(){
 int max=-10001,p,i,smin=0x3f3f3f3f,p1,p2,aux;
 freopen("secv7.in","r",stdin);
 scanf("%d",&n);
 for(i=1;i<=n;i++)
  scanf("%d",&v[i]),v[i]>max ? max=v[i],p=i:0;
 fclose(stdin);
 for(i=1;i<=n-2;i++){
  if(p>=n-i+1){
   aux=max+v[n-i]+caut(1,n-i-1);
   if(aux<smin)
    smin=aux,p2=n-i,p1=n-i-1;
  }
  else if(p==n-i){
   aux=max+v[1]+v[n];
   if(aux<smin)
    smin=aux,p1=1,p2=n-1;
  }
  else if(p<n-i){
   aux=max+v[n-i]+caut(n-i+1,n);
   if(aux<smin)
    smin=aux,p2=n-i,p1=n-i-1;
  }
 }
 freopen("secv7.out","w",stdout);
 printf("%d\n%d %d",smin,p1,p2);
 fclose(stdout);
 return 0;
}
