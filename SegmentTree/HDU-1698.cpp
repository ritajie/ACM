/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int left;
    int right;
    int color;
    int value;
};
Node node[100000*3];

void TreeMake(int l, int r, int i)
{
    node[i].left = l;
    node[i].right = r;
    node[i].color = 1;
    
    if (l == r)
    {
        node[i].value = 1;
        return ;
    }
    int m = (l + r)/2;
    TreeMake(l, m, i*2);
    TreeMake(m+1, r, i*2+1);
    node[i].value = node[i*2].value + node[i*2+1].value;
}

void TreeUpdate(int l, int r, int c, int i)
{
    if (node[i].left == l && node[i].right == r)
    {
        node[i].value = (r - l + 1) * c;
        node[i].color = c;
        return ;
    }
    
    int m = (node[i].left + node[i].right) / 2;
    // 如果原来整个区间的颜色一致，而现在需要更新其中的一个子区间
    // 先把父节点的颜色传递给子节点，同时更新子节点的value属性值
    if (node[i].color != 0)
    {
        node[i*2].color = node[i].color;
        node[i*2+1].color = node[i].color;
        node[i*2].value = (node[i*2].right - node[i*2].left + 1) * node[i*2].color;
        node[i*2+1].value = (node[i*2+1].right - node[i*2+1].left + 1) * node[i*2+1].color;
    }
    if (r <= m)
    {
        TreeUpdate(l, r, c, i*2);
    }
    else if (l > m)
    {
        TreeUpdate(l, r, c, i*2+1);
    }
    else
    {
        TreeUpdate(l, m, c, i*2);
        TreeUpdate(m+1, r, c, i*2+1);
    }
    
    // 更新节点的color属性值
    if (node[i*2].color == node[i*2+1].color)
    {
        node[i].color = node[i*2].color;
    }
    else
    {
        node[i].color = 0;
    }
    node[i].value = node[i*2].value + node[i*2+1].value;
}

int main(int argc, char **argv)
{
    //freopen("in.txt", "r", stdin);
    int m, n, line;
    int l, r, c, i;
    
    scanf("%d", &m);
    for (i = 1; i <= m; ++i)
    {
        scanf("%d", &n);
        TreeMake(1, n, 1);
        scanf("%d", &line);
        while(line--)
        {
            scanf("%d %d %d", &l, &r, &c);
            TreeUpdate(l, r, c, 1);
        }
        printf("Case %d: The total value of the hook is %d.\n", i, node[1].value);
    }
    
    return 0;
}