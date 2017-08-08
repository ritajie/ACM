/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <bits/stdc++.h>
using namespace std;
int a[1010];
int find(int x)
{
    if(x!=a[x])
    {
        a[x]=find(a[x]);
    }
    return a[x];
}
int main()
{
    int n,m,i,x,y,j;
    scanf("%d",&n);
    while(n)
    {
        scanf("%d",&m);
        for(i=0;i<=n;++i)
            a[i]=i;
        j=n-1;
        for(i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            x=find(x);
            y=find(y);
            if(x!=y)
            {
                a[y]=x;
                j--;
            }
        }
        printf("%d\n",j);
        scanf("%d",&n);
    }
    return 0;
}
