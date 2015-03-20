   long i,s=0,nr=0,l;
for (i=1;i<=n-1;i++)
{
l=strlen(a[i]);
s+=l;
if (s<y&&s+strlen(a[i+1])<y)
{
printf("%s ",a[i]);
s++;
}
else
{
for (long j=1;j<=y-s;j++)
printf(" ");
printf("%s\n",a[i]);
nr++;
s=0;
}
if (nr==x)
{
printf("\n");
nr=0;
}
}
      
