/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=10005;
struct node { int from,to,len;} edge[maxn];//储存边的数据结构
int n,fa[maxn],m,ans,q;
bool cmp(node a,node b) { return a.len<b.len; }//边按从小到大的顺序排列
int Find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=Find(fa[x]);
}
void Merge(int x,int y)
{
    x=Find(x),y=Find(y);
    if(x!=y) fa[y]=x;
}
int kruskal()
{
    sort(edge,edge+m,cmp);//边排序
    for(int i=0;i<=n;i++) fa[i]=i;//初始化并查集
    ans=0;
    for(int i=0;i<m;i++)//一条边的两个端点不在同一个集合，则选它，并合并端点
        if(Find(edge[i].from)!=Find(edge[i].to)) Merge(edge[i].from,edge[i].to),ans+=edge[i].len;
    return ans;
}
int main()
{
    while(cin>>n,n)
    {
        m=n*(n-1)/2;
        for(int i=0;i<m;i++) cin>>edge[i].from>>edge[i].to>>edge[i].len;
        cout<<kruskal()<<endl;
    }
    return 0;
}
