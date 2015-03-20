#include<fstream>
using namespace std;
ifstream cin("bete2.in");
ofstream cout("bete2.out");
long long sir[50005], n, contor;
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
    cin>>n;
    for(int i=1;i<=n;i++)
         cin>>sir[i];
    quickSort(sir, 1, n);
    for(int i=1;i<=n-2;i++)
       for(int j=i+1;j<=n-1;j++)
          for(int k=j+1;k<=n;k++)
             if(sir[i]+sir[j]==sir[k])
                 contor++;
    cout<<contor;
    return 0;
}
