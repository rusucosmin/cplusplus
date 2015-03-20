#include<fstream>
using namespace std;
int nrraspuns[1000005];
int main()
{   int i, n, max=0,raspunsul=0, raspuns[1000005];
    ifstream in("mincinosi.in");
    ofstream out("mincinosi.out");
    in>>n;
    for(i=1;i<=n;i++)
   {in>>raspuns[i];
    nrraspuns[raspuns[i]]++;} 
    for(i=0;i<=n;i++)
      if(i+nrraspuns[i]==n)
        if (max<nrraspuns[i]) 
        {max=nrraspuns[i];
         raspunsul=i;}   
    out<<max<<"\n";
    for(i=0;i<=n;i++)
       if (raspuns[i]==raspunsul)
             out<<i<<"\n";
    in.close();
    out.close();
    return 0;
}  
