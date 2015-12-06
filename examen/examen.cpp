#include<fstream>
#include <iostream>
#include<cstring>

using namespace std;

const int MAXN = 50005;
const int INF = 0x3f3f3f3f;

typedef struct lnod{
	int vf,cost;
   	struct lnod *next;
} *Nod;

/// folosim algoritmul lui bellman ford
Nod a[MAXN];
int Q[MAXN << 5]; // coada
bool viz[MAXN];
int D[MAXN];
int N, M; // nr de noduri, respectiv de muchii

void add(int x,int y,int c)
{ // adauga o muchie intre x si y de cost c
     Nod p = new lnod;
     p->vf = y;
     p->cost = c;
     p->next = a[x];
     a[x] = p;
}

void readdata()
{
     int i,x,y,z;
     cin >> N >> M;
     for(i=1;i<=M;++i)
     {
     	cin>>x>>y>>z;
     	add(x,y,z);
     }
}

void Bellman_Ford(){
    int nod;
    memset(D,INF,sizeof(D));
    D[1] = 0;
	int p = 0, u = 0;
	Q[++ u] = 1;
    viz[1]=1;

    while(p <= u)
    {
      nod = Q[++ p];
      viz[nod] = 0;

      for(Nod p=a[nod];p;p=p->next)
       if(D[nod] + p->cost < D[p->vf])
        {
         D[p->vf] = D[nod] + p->cost;
         if(!viz[p->vf])
          {
		  	Q[++ u] = p->vf;
            viz[p->vf]=1;
          }
        }
    }
}

void writedata(){
     for(int i=2;i<=N;++i)
	 	if(D[i] == INF)
			cout << "0 ";
		else
			cout << D[i] << ' ';
}

int main(void){
	readdata();
	Bellman_Ford();
	writedata();
	return 0;
}
