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
    int cover;
};
Node node[100000*3];
int g_nRes = 0;

void TreeMake(int left, int right, int i)
{
    node[i].left  = left;
    node[i].right = right;
    node[i].cover = 0;
    if (left == right)
    {
        return ;
    }
    
    int mid = (left + right)/2;
    TreeMake(left, mid, i*2);
    TreeMake(mid+1, right, i*2+1);
}

void TreeUpdate(int left, int right, int i)
{
    if (node[i].left == left && node[i].right == right)
    {
        node[i].cover++;
        return ;
    }
    // 叶子节点
    if (node[i].left == node[i].right)
    {
        return ;
    }
    
    int mid = (node[i].left + node[i].right)/2;
    if (right <= mid)
    {
        TreeUpdate(left, right, i*2);
    }
    else if (left > mid)
    {
        TreeUpdate(left, right, i*2+1);
    }
    else
    {
        TreeUpdate(left, mid, i*2);
        TreeUpdate(mid+1, right, i*2+1);
    }
}

void TreeQuery(int x, int i)
{
    if (node[i].left == x && node[i].right == x)
    {
        g_nRes += node[i].cover;
        return ;
    }
    
    g_nRes += node[i].cover;
    int mid = (node[i].left + node[i].right) / 2;
    if (x <= mid)
    {
        TreeQuery(x, i*2);
    }
    else //if (x > mid)
    {
        TreeQuery(x, i*2+1);
    }
}

int main(int argc, char **argv)
{
    //freopen("in.txt", "r", stdin);
    
    int n, i, l, r;
    
    while (EOF != scanf("%d", &n), n)
    {
        TreeMake(1, n, 1);
        for (i = 1; i <= n; ++i)
        {
            scanf("%d %d", &l, &r);
            TreeUpdate(l, r, 1);
        }
        for (i = 1; i < n; ++i)
        {
            g_nRes = 0;
            TreeQuery(i, 1);
            printf("%d ", g_nRes);
        }
        g_nRes = 0;
        TreeQuery(i, 1);
        printf("%d\n", g_nRes);
    }

    return 0;
}