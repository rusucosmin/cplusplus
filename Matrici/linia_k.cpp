#include <iostream>
using namespace std;
int main()
{
    int a[100][100], i, j, n, m, k ; 
    cout<<"Numarul de linii "; cin>>n;
    cout<<"Numarul de coloane ";  cin>>m;
    for(i=1; i<=n; i++)
    {
             for(j=1; j<=m; j++)
             {
                      cout<<"a["<<i<<"]["<<j<<"] = "; cin>>a[i][j];
                      
                      }}
    cout<<"Afiseaza elemente de pe linia # "; cin>>k; 
    
    cout<<"Pe linia # "<<k<<" se gasesc elemetele: " ;
    for(j=1; j<=m ; j++)
    cout<<a[k][j]<<"  "; 
    cout<<endl;
    system ("pause") ;
    return 0;
}
