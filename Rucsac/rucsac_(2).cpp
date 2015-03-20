#include<fstream>
#define MAXN 5010
#define MAXG 10010

using namespace std;

ifstream cin("rucsac.in");
ofstream cout("rucsac.out");

int N, G, Pmax;
int W[MAXN], P[MAXN];
int D[MAXN][MAXG];
int main()
{
cin>>N>>G;
for(int i=1;i<=N;i++)
   cin>>W[i]>>P[i];
for(int i=1;i<=N;i++)
    for(int cw=0;cw<=G;cw++)
     { D[i][cw] = D[i-1][cw];
       if(W[i] <= cw)
       D[i][cw] = max(D[i][cw], D[i - 1][cw - W[i]] + P[i]);}
     
     Pmax = D[N][G];    
     cout<<Pmax<<"\n";
 return 0;   
}
