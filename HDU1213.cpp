/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int id;
    int parent;
    int rank;
};

Node node[1010];
bool flag[1010];

void MakeSet(int n)
{
    for(int i = 0; i < n; ++i)
    {
        node[i].id = node[i].parent = i;
        node[i].rank = 0;
        flag[i] = false;
    }
}

int FindSet(int x)
{
    if (x != node[x].parent)
    {
        node[x].parent = FindSet(node[x].parent);
    }
    return node[x].parent;
}

void UnionSet(int x, int y)
{
    x = FindSet(x);
    y = FindSet(y);
    
    if (x == y) return ;
    if (node[x].rank > node[y].rank)
    {
        node[y].parent = x;
    }
    else
    {
        node[x].parent = y;
        if (node[x].rank == node[y].rank)
        {
            node[y].rank++;
        }
    }
}

int main(int argc, char *argv)
{
    int m, n, edge;
    int i, t, res, x, y;
    
    scanf("%d", &m);
    while(m--)
    {
        scanf("%d %d", &n, &edge);
        MakeSet(n);
        for (i = 0; i < edge; ++i)
        {
            scanf("%d %d", &x, &y);
            --x, --y;
            UnionSet(x, y);
        }
        res = 0;
        for (i = 0; i < n; ++i)
        {
            t = FindSet(i);
            if (!flag[t])
            {
                flag[t] = true;
                ++res;
            }
        }
        printf("%d\n", res);
    }
    
    return 0;
}
/*
    并查集基础题，注意编码是从1开始算的
*/
