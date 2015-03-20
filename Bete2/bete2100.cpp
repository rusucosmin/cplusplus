#include<fstream>
using namespace std;
ifstream cin("bete2.in");
ofstream cout("bete2.out");
long long sir[3005];
int n, contor, i, j;
bool Bsearch ( int val ) { 

   int mid , left = j , right = n;
    
   while ( left <= right ) { 
        mid = ( left + right )/2;
        if ( sir[mid] == val ) return 1;
          else if ( sir[mid] < val ) left = mid + 1;
              else right = mid - 1;
     }

return 0;
}

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
    for(i=1;i<=n;i++)
         cin>>sir[i];
    quickSort(sir, 1, n);
    for(i=1;i<=n-1;i++)
       for(j=i+1;j<=n;j++)
          if (Bsearch(sir[i]+sir[j]))
                 contor++;
    cout<<contor;
    return 0;
}
