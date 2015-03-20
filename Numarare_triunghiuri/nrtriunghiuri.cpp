#include<fstream>
using namespace std;
ifstream cin("nrtri.in");
ofstream cout("nrtri.out");   
int n,i,j,k,q[1005],aux,sol=0;
void quickSort(int arr[], int left, int right) 
{
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
      /* partition */
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
{    //citire
     cin>>n;
     for(i=1;i<=n;i++)
        cin>>q[i];
     //Sortez vectorul folosind metoda quickSort
     quickSort(q, 1, n);
     //Numar triunghiurile 
     for(i=1;i<=n;i++)
         for(j=i+1;j<=n;j++)
            for(k=j+1;k<=n;k++)
               if(q[i]+q[j]>=q[k])
                  sol++;
   cout<<sol;   
   return 0;
} 
