/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <bits/stdc++.h>  
using namespace std;  
struct EDGE  
{  
    int u,v,cost;  
}eg[100001];  
int n,m,father[100001];  
  
bool cmp(EDGE e1,EDGE e2)  
{  
    return e1.cost<e2.cost;  
}  
  
// 并查集 初始化函数  
void Init( int m )  
{  
    int i;  
    for(i=1;i<=m;i++)  
        father[i]=i;  
}  
// 并查集 查找函数  
int Find(int x)  
{  
    while(father[x]!=x)  
        x=father[x];  
    return x;  
}  
// 并查集 合并函数  
void Combine(int a,int b)  
{  
    int temp_a,temp_b;  
    temp_a=Find(a);  
    temp_b=Find(b);  
  
    if(temp_a!=temp_b)  
        father[temp_a]=temp_b;  
}  
  
// 最小生成树 Kruskal 算法  
int Kruskal( void )  
{  
    EDGE e;  
    int i,res;  
    sort(eg,eg+n,cmp);  
    // 并查集 初始化  
    Init(m);  
  
    // 构建最小生成树  
    res=0;  
    for( i=0;i<n;++i )  
    {  
        e=eg[i];  
        if( Find(e.u)!=Find(e.v) )  
        {  
            Combine(e.u,e.v);  
            res+=e.cost;  
        }  
    }  
    return res;  
}  
  
int main()  
{  
    int i,ans;  
    bool bl;  
    while( scanf("%d%d",&n,&m) && n )  
    {  
        for( i=0;i<n;++i )  
            scanf("%d%d%d",&eg[i].u,&eg[i].v,&eg[i].cost);  
        ans=Kruskal();  
          
        // 是否所有的点都在同一个集合  
        bl=true;  
        for(i=2;i<=m;++i)  
            if( Find(1)!=Find(i) )  
            {  
                bl=false;  
                break;  
            }  
              
        if( bl )    printf("%d\n",ans);  
        else    printf("?\n");  
    }  
    return 0;  
}  
