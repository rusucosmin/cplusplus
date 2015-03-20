// Powered by  Rusu Cosmin (C)  
#include<fstream>

using namespace std;
ifstream cin("kinetic.in");
ofstream cout("kinetic.out");
int n, m, a[505], b[505], c[505],pr,ul,aux,ii;
long long j, i, x,y,t;
int caz1(long long r, int li, int ls)
{
    int mij, fin=n;
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
 
int caz2(long long r, int li, int ls)
{
   // int ls=n,
    int mij,fin=1;
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
                     { pr=0;
                     ul=0;
                                     cin>>x>>y>>t;
                     if(x<y)
                       {aux=y;
                        y=x;
                        x=aux;}
                       for(i=1;i<=n;i++)
                           c[i]=a[i]+b[i]*t;
                     
                       quickSort(c, 1, n);
                       for(ii=1;ii<=n;ii++)
                           if(c[ii]>=y)
                              { pr=ii; break; }
                       if(pr)
                       for(ii=n;ii>=pr;ii--)
                           if(c[ii]<=x)
                               { ul=ii; break; }
                       if(pr&&ul)
                          cout<<ul-pr+1<<"\n";            
                   //    cout<<caz1(x, pr,ul)-caz2(y,pr, ul)+1<<"\n";
                       else cout<<"0\n";
                     
                 }
                     
    
    
    
    return 0;
    
}
