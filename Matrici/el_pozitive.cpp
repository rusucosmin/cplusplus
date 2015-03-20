#include <iostream>
using namespace std;
int main()
{
    int a[30][30] ,nr, i, j, n, m ;
    cout<<"Numar de linii  ";  cin>>n;
    cout<<"Numar de coloane  "; cin>>m;
    
    for(i=1; i<=n; i++)
             { for(j=1; j<=m; j++) 
               {cout<<"a["<<i<<"]["<<j<<"] = "; cin>>a[i][j];  }
               if(a[i][j]>0)
               nr++; }
               cout<<"Numarul elemtelor pozitive: "<<nr;
               system("pause");
               return 0 ;
}             
