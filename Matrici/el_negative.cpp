#include <iostream>
using namespace std;
int main()
{
    int a[30][30] ,poz=0 ,neg=0 , nul=0 ,  i, j, n, m ;
    cout<<"Numar de linii  ";  cin>>n;
    cout<<"Numar de coloane  "; cin>>m;
    
    for(i=1; i<=n; i++)
{
             for(j=1; j<=m; j++) 
{            cout<<"a["<<i<<"]["<<j<<"] = "; cin>>a[i][j];  
                 if(a[i][j]<0) 
                 neg++;
                 if(a[i][j]==0)
                 nul++;
                 
                 if(a[i][j]>0)
                 poz++; }
}               
               cout<<"Numarul elemtelor negative: "<<neg<<endl;
               cout<<"Numarul elemtelor pozitive: "<<poz<<endl;
               cout<<"Numarul elemtelor nule: "<<nul<<endl;
               system("pause");
               return 0 ;
}             
