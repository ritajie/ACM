/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <btis/stdc++.h>
using namespace std;

struct Node
{
    int left;
    int right;
    int count;
};

// 数组大小设为区间大小的四倍
Node node[4*50010];

void TreeMake(int l, int r, int i)
{
    node[i].left = l;
    node[i].right = r;
    node[i].count = 0;
    if (l == r)
    {
        return ;
    }
    
    int m = (l + r) / 2;
    TreeMake(l, m, i*2);
    TreeMake(m+1, r, i*2+1);
}

// i 为节点下标 x为节点值
void TreeUpdate(int i, int x, int op, int num)
{
    int l = node[i].left;
    int r = node[i].right;
    int m = (l + r) / 2;
    
    if (op == 1) // +
    {
        node[i].count += num;
    }
    else
    {
        node[i].count -= num;
    }
    
    if (x == l && x == r)
    {
        return ;
    }
    
    if (x > m)
    {
        TreeUpdate(i*2+1, x, op, num);
    }
    else if (x <= m)
    {
        TreeUpdate(i*2, x, op, num);
    }
}

int TreeQuery(int l, int r, int i)
{
    if (node[i].left == l && node[i].right == r)
    {
        return node[i].count;
    }
    
    int m = (node[i].left + node[i].right) / 2;
    if (r <= m)
    {
        return TreeQuery(l, r, i*2);
    }
    if (l > m)
    {
        return TreeQuery(l, r, i*2+1);
    }
    return TreeQuery(l, m, i*2) + TreeQuery(m+1, r, i*2+1);
}

int main(int argc, char **argv)
{
    int m, i, j, n, tmp;
    char cmd[10];
    int x, y;
    
    scanf("%d", &m);
    for (i = 1; i <= m; ++i)
    {
        printf("Case %d:\n", i);
        scanf("%d", &n);
        TreeMake(1, n, 1);
        for (j = 1; j <= n; ++j)
        {
            scanf("%d", &tmp);
            TreeUpdate(1, j, 1, tmp);
        }
        while (scanf("%s", cmd))
        {
            if (cmd[0] == 'E') break;
            scanf("%d %d", &x, &y);
            if (cmd[0] == 'Q')
            {
                tmp = TreeQuery(x, y, 1);
                printf("%d\n", tmp);
            }
            else if (cmd[0] == 'A')
            {
                TreeUpdate(1, x, 1, y);
            }
            else
            {
                TreeUpdate(1, x, 2, y);
            }
        }
    }
    
    return 0;
}
/*
    线段树基础题
*/