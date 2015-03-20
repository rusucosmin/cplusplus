#include <fstream>
#define M 250
///#define cosmin
using namespace std;
ifstream cin("lacusta.in");
ofstream cout("lacusta.out");
unsigned short A[M][M], B[M][M], m, n, i, j, min1, min2, jmin;
int main()
{
    cin>>m>>n;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            cin>>A[i][j];
    cin.close();
    B[1][0]=32000; //infinit
    for(i=1;i<n;i++)
        B[1][i]=A[0][0]+A[0][i]+A[1][i];    //initializarea celei de-a doua linii;
    for(i=1;i<m-1;i++)
        {//calculez doua valori minime pe linia i
                if(B[i][0]<=B[i][1])
                {
                    min1=B[i][0]; min2=B[i][1]; jmin=0;
                }
                else {min1=B[i][1]; min2=B[i][0]; jmin=1;}
                for(j=2; j<n;j++)
                    if(B[i][j]<min1)
                        {
                            min2=min1;
                            min1=B[i][j];
                            jmin=j;
                        }
                        else if(B[i][j]<min2) min2=B[i][j];
                for(j=0;j<n;j++)
                    if(j!=jmin)
                        B[i+1][j]=min1+A[i][j]+A[i+1][j];
                    else B[i+1][j]=min2+A[i][j]+A[i+1][j];
        }
    min1=B[m-1][0];
    for(j=1;j<n;j++)
        if(B[m-1][j]<min1)
            min1=B[m-1][j];
    cout<<min1+A[m-1][n-1]<<"\n";
   #ifdef cosmin
    for(i=0;i<n;i++)
        {for(j=0;j<m;j++)
            cout<<A[i][j]<<" ";
        cout<<"\n";}
    for(i=0;i<n;i++)
        {for(j=0;j<m;j++)
            cout<<B[i][j]<<" ";
        cout<<"\n";}
    #endif
    return 0;
}
