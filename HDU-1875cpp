/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include<bits/stdc++.h>
using namespace std;

int father[102];
double len;

struct sum
{
    double a;
    double b;
}num[150];

struct dir
{
    int a,b;
    double x;
}r[5000];

bool cmp(const dir &a,const dir &b)
{
    return a.x<b.x;
}

int find(int x)
{
    while(x!=father[x])
        x=father[x];
    return x;
}

void Union(int i)
{
    int a=find(r[i].a);
    int b=find(r[i].b);
    if(a!=b&&r[i].x<=1000 && r[i].x>=10)
    {
        father[a]=b;
        len+=r[i].x;
    }
}

int main()
{
    int T,C,i,j,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&C);
        for(i=0;i<102;i++)
        {
            father[i]=i;
        }
        for(i=0;i<C;i++)
        {
            scanf("%lf%lf",&num[i].a,&num[i].b);
        }
        int k=0;
        for(i=0;i<C;i++)
            for(j=i+1;j<C;j++)
            {
                r[k].a=i;
                r[k].b=j;
                double x=num[i].a-num[j].a;
                double y=num[i].b-num[j].b;
                r[k].x=sqrt(x*x+y*y);
                k++;
            }
        sort(r,r+k,cmp);
        len=0;
        for(i=0;i<k;i++)
            Union(i);
        for(i=0,m=0;i<C;i++)
        {
            if(m>1)
            {
                printf("oh!\n");
                break;
            }
            else if(father[i]==i)
                m++;
        }
        if(m==1)
            printf("%.1lf\n",100*len);
    }
    return 0;
}
