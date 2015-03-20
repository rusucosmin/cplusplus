# include <fstream>
# include <string.h>
# include <ctype.h>
using namespace std;
ifstream cin("dir.in");
ofstream cout("dir.out");
char s[1610], st[1610];
int p[1610], kp;
int n, i, k=-1;
int main()
{
    cin.getline(s, 1605);
    n=strlen(s);
    for(i=0;i<n;i++)
        {
            if(isupper(s[i]) || isdigit(s[i]))
                {
                    k++;
                    st[k]=s[i];
                }
            else if(s[i]=='(')
                    {
                            kp++;
                            k++;
                            p[kp]=k;
                            cout<<kp<<" "<<p[kp]<<"\n";
                            st[k]='\\';
                    }
            else if(s[i]==')')
                {
                    kp--;
                    k=p[kp];
                }
            else if(s[i]==',')
                {
                    cout<<st<<" ";
                    kp--;
                    k=p[kp];
                }
            else if(islower(s[i]))
                {
                    k++;
                    st[k]=s[i];
                }
        }
    return 0;
}
