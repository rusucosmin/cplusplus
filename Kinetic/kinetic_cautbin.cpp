#include<fstream>
#include<math.h>
using namespace std;
ifstream cin("kinetic.in");
ofstream cout("kinetic.out");
int n, m, a[505], b[505], c[505],aux;
long long j, i, x,y,t;
long long caz1(long long r)
{
    long long li=1, ls=n, mij, fin;
    while( li<=ls)
    {
        mij=(li+ls)/2;
        if (c[mij]<=r)
        {
            fin=mij;
            li=mij+1;
        }
        else
            ls=mij-1;
    }
    return fin;
}
  
long long caz2(long long r)
{
    long long li=1,ls=n,mij,fin;
    while(li<=ls)
    {
    mij=(li+ls)/2;
    if (c[mij]>=r)
    {
        fin=mij;
        ls=mij-1;
    }
    else
    li=mij+1;
    }
    return fin;
}
void quickSort(int arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
  
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
  
      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
                     cin>>a[i]>>b[i];
    for(j=1;j<=m;j++)
                     { cin>>x>>y>>t;
                     if(x<y)
                       {aux=y;
                        y=x;
                        x=aux;}
                       for(i=1;i<=n;i++)
                           c[i]=a[i]+b[i]*t;
                      
                       quickSort(c, 1, n);
                     // for(int k=1;k<=n;k++)
                     //    cout<<c[k]<<" " ;
                     if(caz1(x)-caz2(y))
                     cout<<caz1(x)-caz2(y)+1<<"\n";
                     else cout<<"0\n";
                      
                 }
                      
     
     
     
    return 0;
     
}
