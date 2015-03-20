#include<fstream>
using namespace std;
ifstream cin("livada.in");
ofstream cout("livada.out");
long long m, n, p, i, j, b[700005], a[105][700005], v[700000], pomi_maj, maxim, k, contor,linie;
void quickSort(long long arr[], long long left, long long right) 
{
      long long i = left, j = right;
      long long tmp;
      long long pivot = arr[(left + right) / 2];

      while (i <= j) 
      {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) 
                     {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
                  }
      }
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

int main()
{
    cin>>m;
    cin>>n;
    cin>>p;
    for(i=1;i<=m;i++)
    {   linie++;
        for(j=1;j<=n;j++)
           {cin>>v[j]; b[v[j]]++; 
            a[i][j]=v[j];}
        quickSort(v, 1, m);
        if (b[v[(n/2)+1]]>=(n/2)+1)
          {contor=1;
                                   pomi_maj++;
          for(k=1;k<=n;k++)
          if(   a[linie][k]==v[(n/2)+1] &&  a[linie][k+1]==v[(n/2)+1] )
              { contor++; }
          if(maxim<contor)
          maxim=contor; 
          }
    }
    
cout<<pomi_maj<<"\n"<<maxim;
    return 0;
}
