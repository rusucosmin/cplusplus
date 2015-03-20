//greedy
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

long ct1[10],ct2[10],cta[10];
ifstream f("2numere.in");
ofstream fout("2numere.out");

long n,cif,g,primcif,i,j,k,difmin,n1,n2,nsol1,nsol2,k1,w,ww,q2;
long dif,cif1,cif2,nc,min=2000000000l;
char a1[100],a2[100],a1sol[100],a2sol[100],sir1[30],sir2[30];


long conv(long a[], long nc)
{ long s=0,i;
  for (i=0;i<nc;i++)
    s = s*10 + a[i];
  return s;
}

int main()
{ long min=20000000;
 f>>n;
 for (i=1;i<=n;i++)
  {
   f>>cif;
   ct1[cif]++;
  }
 for (i=1;i<=n;i++)
  {
   f>>cif;
   ct2[cif]++;
  }

 for (k=0;k<=9;k++)
   while (ct1[k]!=0 && ct2[k]!=0)
     { ct1[k]--; ct2[k]--;
       cta[k]++;
       g++;
     }
 if (g==n)
  { fout<<"egale";
    return 0;
  }

 difmin=10;
 for (dif=1;dif<10&&difmin==10;dif++)
   for(k=9;k>=dif;k--)
     if (ct1[k]!=0 && ct2[k-dif]!=0)
	{difmin=dif;
	 break;
	}

 if (difmin!=10)	//5.1 exista cel putin o pereche de cifre "bune"

 for (cif=9;cif>=difmin;cif--)
  { cif1=cif;
    cif2=cif-difmin;
    if (ct1[cif1]!=0 && ct2[cif2]!=0)
   {
    a1[0]=cif1+48;   		//construiesc primul numar in a1
    ct1[cif1]--;
    j=1;
    for(k=0;k<10;k++)
      for(i=0;i<ct1[k];i++)
	{a1[j]=k+48;j++;}
    nc=j;
    a2[0]=cif2+48;		//construiesc al doilea numar in a2
    ct2[cif2]--;
    j=1;
    for(k=9;k>=0;k--)
      for(i=0;i<ct2[k];i++)
	{a2[j]=k+48;j++;}

     for (w=0;w<20;w++) sir1[w]=0;
     ww=0;
     for (w=1;w<=9;w++)
	 for (q2=0;q2<cta[w];q2++)
		   { sir1[ww]=48+w;
		     ww++;
		   }
      strcpy(sir2,sir1);
      strcat(sir1,a1);
      strcat(sir2,a2);
      n1 = atol(sir1);
      n2 = atol(sir2);
      if (n1-n2<min)
		{ min = n1-n2;
		  strcpy(a1sol,sir1);
		  strcpy(a2sol,sir2);
		}

     ct1[cif1]++;
     ct2[cif2]++;
   }
 }
/* else		//5.2 aduc cate o cifra dintre cele comune si refac 5.1
 {*/
  for (k1=9;k1>=0;k1--)
    if (cta[k1]!=0)
       {
	 cta[k1]--;ct1[k1]++;ct2[k1]++; //aduc o cifra din p. comuna
	 difmin=10;
	 for (dif=1;dif<10&&difmin==10;dif++)
	   for(k=9;k>=dif;k--)
	     if (ct1[k]!=0 && ct2[k-dif]!=0)
		{difmin=dif;
		 break;
		}
	 if (difmin!=10)	//exista cel putin o pereche de cifre "bune"
	  for (cif=9;cif>=difmin;cif--)
	  { cif1=cif;
	    cif2=cif-difmin;
	    if (ct1[cif1]!=0 && ct2[cif2]!=0)//o pereche de numere bune
	    {
	      a1[0]=cif1+48;   		//construiesc primul numar in a1
	      ct1[cif1]--;
	      j=1;
	      for(k=0;k<10;k++)
		for(i=0;i<ct1[k];i++)
		  {a1[j]=k+48;j++;}
	      nc=j;
	      a2[0]=cif2+48;		//construiesc al doilea numar in a2
	      ct2[cif2]--;
	      j=1;
	      for(k=9;k>=0;k--)
		for(i=0;i<ct2[k];i++)
		  {a2[j]=k+48;j++;}
	      for (w=0;w<20;w++) sir1[w]=0;
	      ww=0;
	      for (w=1;w<=9;w++)
		 for (q2=0;q2<cta[w];q2++)
		   { sir1[ww]=48+w;
		     ww++;
		   }
	      strcpy(sir2,sir1);
	      strcat(sir1,a1);
	      strcat(sir2,a2);
	      n1 = atol(sir1);
	      n2 = atol(sir2);
	      if (n1-n2<min)
		{ min = n1-n2;
		  strcpy(a1sol,sir1);
		  strcpy(a2sol,sir2);
		}
	      ct1[cif1]++;
	      ct2[cif2]++;
	    }
	  }
       cta[k1]++;ct1[k1]--;ct2[k1]--;
      }
// }

fout<<a1sol<<endl;
fout<<a2sol<<endl;
fout<<min<<endl;
//}

}


