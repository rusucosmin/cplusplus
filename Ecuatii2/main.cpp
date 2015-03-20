# include <fstream>
# include <ctype.h>
# include <string.h>
# include <iomanip>
# include <limits.h>
using namespace std;
ifstream cin("ecuatii2.in");
ofstream cout("ecuatii2.out");
short n, ii, i, m, nr, semn=1, j, nr1, semn1=1;
int a, a1; //coeficientul lui X;
int b, b1; //coeficientul liber
char s[265];
bool ok;
int main()
{
    cin>>n;
    cin.getline(s, 20);
    for(ii=1;ii<=n;ii++)
       {
            cin.getline(s, 259);
            m=strlen(s);
            a=0;
            ok=0;
            if(ok==0)
            for(i=0;i<m;i++)
                {
                if(isdigit(s[i]))
                        {
                            if(i>=1 && s[i-1]=='-')
                                semn=-1;
                            nr=nr*10+(s[i]-'0');
                            i++;
                            while(isdigit(s[i]))
                                {
                                    nr=nr*10+(s[i]-'0');
                                    i++;
                                }
                            if(s[i]=='x')
                                {
                                    a+=(nr*semn);
                                }
                            else b+=(nr*semn);
                        }
                if(s[i]=='x'&&!isdigit(s[i-1]))
                                {
                                    if(s[i-1]=='-')
                                    a+=(-1);
                                    else a+=1;
                                }
                nr=0;
                semn=1;
                if(s[i]=='=')
                    {ok=1; break;}
                }
                if(ok==1)
                    for(j=i;j<m;j++)
                    {
                        if(isdigit(s[j]))
                        {
                            if(j>i && s[j-1]=='-')
                                semn1=-1;
                            nr1=nr1*10+(s[j]-'0');
                            j++;
                            while(isdigit(s[j]))
                                {
                                    nr1=nr1*10+(s[j]-'0');
                                    j++;
                                }
                            if(s[j]=='x')
                                {
                                    a1+=(nr1*semn1);
                                }
                            else b1+=(nr1*semn1);
                        }
                if(s[j]=='x'&&!isdigit(s[j-1]))
                                {
                                    if(s[j-1]=='-')
                                    a1+=(-1);
                                    else a1+=1;
                                }

                nr1=0;
                semn1=1;
                }
                if(b1==b && a==a1)
                    cout<<"infinit\n";
                else if(a==a1)
                    cout<<"imposibil\n";
                else
                cout<<fixed<<setprecision(4)<<(double)(b1-b)/(a-a1)<<"\n";
         //       cout<<a<<" "<<b<<"\n";
         //       cout<<a1<<"     "<<b1<<"\n";
                a=a1=b=b1=0;     }
    return 0;
}
