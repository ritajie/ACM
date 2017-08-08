/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <iostream>
#include <cstdio>
using namespace std;

struct Node
{
    int parent;
    int rank;
};

Node node[100010];
bool flag[100010];
int data[100010];

void MakeSet(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        node[i].parent = i;
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
    
    if (x == y) return;
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

int main(int argc, char **argv)
{
    int n, i, x[2], edge;
    bool endflag = false;
    
    while(1)
    {
        MakeSet(100000);
        n = edge = 0;
        do
        {
            scanf("%d %d", &x[0], &x[1]);
            if (x[0] == 0) break;
            if (x[0] == -1)
            {
                endflag = true;
                break;
            }
            UnionSet(x[0], x[1]);
            ++edge;
            for (i = 0; i < 2; ++i)
            {
                if (!flag[x[i]])
                {
                    flag[x[i]] = true;
                    data[n] = x[i];
                    n++;
                }
            }
        } while (1);
        if (endflag) break;
        // 单独的0 0输出Yes
        if (n == 0 && edge == 0)
        {
            printf("Yes\n");
            continue;
        }
        if (n != edge + 1)
        {
            printf("No\n");
            continue;
        }
        int tmp = FindSet(data[0]);
        for (i = 1; i < n; ++i)
        {
            if (tmp != FindSet(data[i])) break;
        }
        if (i != n)
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
        }
    }
    return 0;
}
/*
    并查集基础题，需要注意的是单独的0 0输出Yes
    要满足条件，不能有环也不能存在多个子图
    满足条件1: 边数 + 1 = 点数
    满足条件2: 只有一颗树
*/
