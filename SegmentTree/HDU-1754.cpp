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
    int max;
};

Node node[200000*4];

void TreeMake(int l, int r, int i)
{
    node[i].left = l;
    node[i].right = r;
    node[i].max = 0;

    if (node[i].left == node[i].right)
    {
        return ;
    }

    int m = (l + r)/2;
    TreeMake(l, m, i*2);
    TreeMake(m+1, r, i*2 + 1);
}

// i 节点下标
// x 节点的值
// s 要更新的属性
void TreeUpdate(int i, int x, int s)
{
    int l = node[i].left;
    int r = node[i].right;
    int m = (l + r) / 2;

    if (node[i].max < s)
    {
        node[i].max = s;
    }
    if (l == x && r == x)
    {
        node[i].max = s;
        return ;
    }

    if (x > m)
    {
        TreeUpdate(i*2+1, x, s);
    }
    else if (x <= m)
    {
        TreeUpdate(i*2, x, s);
    }
}

int TreeQuery(int i, int x, int y)
{
    int l = node[i].left;
    int r = node[i].right;
    int m = (l + r) / 2;
    int res = 0;

    if (l == x && r == y)
    {
        return node[i].max;
    }

    if (y <= m)
    {
        res = TreeQuery(i*2, x, y);
    }
    else if (x > m)
    {
        res = TreeQuery(i*2+1, x, y);
    }
    else
    {
        res = max(TreeQuery(i*2, x, m), TreeQuery(i*2+1, m+1, y));
    }

    return res;
}

int main(int argc, char **argv)
{
    //freopen("in.txt", "r", stdin);

    int n, m;
    int i, j, tmp;
    char op;

    while (EOF != scanf("%d %d", &n, &m))
    {
        TreeMake(1, n, 1);
        for (i = 1; i <= n; ++i)
        {
            scanf("%d", &tmp);
            TreeUpdate(1, i, tmp);
        }
        for (i = 1; i <= m; ++i)
        {
            getchar();
            scanf("%c %d %d", &op, &j, &tmp);
            if (op == 'U')
            {
                TreeUpdate(1, j, tmp);
            }
            else
            {
                tmp = TreeQuery(1, j, tmp);
                printf("%d\n", tmp);
            }
        }
    }

    return 0;
}