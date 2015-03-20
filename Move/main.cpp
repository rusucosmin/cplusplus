#include <fstream>
#include <algorithm>
using namespace std;
int N, a[100005],d[100005], u, i, j, v,p;
struct alabama{int x; int y;} sol[100005];
ifstream cin("move.in");
ofstream cout("move.out");
int ct;
void quickSort(int arr[], int left, int right)
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
    cin>>N;
    for(i=1;i<=N;++i)
            cin>>a[i];
    i=1;
    int aux=i;
    while(i<=N)
    {
        bool ok=0;
        if(a[i]+1==a[i+1])
        {
            d[++u]=a[i];
            i++;
            while(a[i]+1==a[i+1])
                i++;
            i++;
        }
        else
            d[++u]=a[i], i++;

    }
    quickSort(d, 1, u);

    cout<<ct<<"\n";
    for(i=1;i<=p;i++)
        cout<<a[sol[i].x]<<" "<<a[sol[i].y]<<"\n";
    cin.close();
    cout.close();
    return 0;
}
