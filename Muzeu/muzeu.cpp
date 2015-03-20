//Problema muzeu
#include<fstream>
using namespace std;

int a[251][251],i,j,ok,u,p,q[3][200001],c,d,y,sir[3][100000],maxi,l[251][251],n,k=0;
ifstream fin("muzeu.in");
ofstream g("muzeu.out");

void init()
{
	//citim datele din fisierul muzeu.in
	fin>>n;
	char c;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) {
			fin>>c;
			if (c=='.') {
				a[i][j]=1;
				l[i][j]=-1;
			}
			else if (c=='P') {
				a[i][j]=10;
				k++;
				sir[1][k]=i;
				sir[2][k]=j;
			}
			else l[i][j]=-2;
		}
	fin.close();
}

//instroduc linia c si col d in coada
void intr(int c,int d)
{
	u=u+1;
	q[1][u]=c;
	q[2][u]=d;
}

//extrag un element din coada
void extr(int &c,int &d)
{
	p=p+1;
	c=q[1][p];
	d=q[2][p];
}

//algoritmul LEE
void lee()
{
	int x,y;
	p=0;
	u=k;
	while(p!=u) {
		extr(x,y);
	   //vecinul de sus
	   //daca are inaltime mai mare si numarul de catarari mai mic atunci
	   //actualizez numarul de catarari cu l[x][y]+1
     if(x>1)

      if(a[x-1][y]==1)
       if(l[x-1][y]>l[x][y]+1||l[x-1][y]==-1)
       {l[x-1][y]=l[x][y]+1;
       intr(x-1,y);

      }
      if(x<n)
       if(a[x+1][y]==1)
        if(l[x+1][y]>l[x][y]+1||l[x+1][y]==-1)
        {l[x+1][y]=l[x][y]+1;
         intr(x+1,y);

         }

    if(y>1)
     if(a[x][y-1]==1)
           if(l[x][y-1]>l[x][y]+1||l[x][y-1]==-1)
           {l[x][y-1]=l[x][y]+1;
                                  intr(x,y-1);

                                  }
    if(y<n)
     if(a[x][y+1]==1)
      if(l[x][y+1]>l[x][y]+1||l[x][y+1]==-1)
    {l[x][y+1]=l[x][y]+1;
    intr(x,y+1);

    }

}

}
void scriere()
{



      for(i=1;i<=n;i++)
             {
                          for(j=1;j<=n;j++)
              g<<l[i][j]<<" ";
              g<<"\n";}
     maxi=-1;
    //  for(i=1;i<=n;i++)
     //  for(j=1;j<=n;j++)
       // if(l[i][j]>maxi)
       // maxi=l[i][j];

}
int main()
{
    init();
    for(i=1;i<=k;i++) {
		q[1][i]=sir[1][i];
		q[2][i]=sir[2][i];
	}
	lee();
	scriere();
    return 0;
}
