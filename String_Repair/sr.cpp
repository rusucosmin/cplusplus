#include<fstream>
#include<string.h>
using namespace std;
ifstream cin("sr.in");
ofstream cout("sr.out");
char A[100005], B[100005];
long i, j, m,n,aux;
int main()
{
    cin.getline(A, 100005);
    cin.getline(B, 100005);
    n=strlen(A);
    m=strlen(B);
    for(i=0;i<m;i++)
      for(j=i+aux;j<n;j++)
           {if(B[i]==A[j])
            {cout<<(j+1)<<" ";
            aux=(j-i);
            break;
            }
           }
        


   
   
    return 0;
}
