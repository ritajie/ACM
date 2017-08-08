/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <bits/stdc++.h>
using namespace std;

struct Line
{
    int x;
    int y1;     // min
    int y2;     // max
    int flag;  // left = 1, right = -1
};

struct Node
{
    int l;      // left
    int r;      // right
    int c;      // cover
    int len;    // length
};

const int g_nMax = 10000;
Line line[2*g_nMax];    // 存放竖线
int Y[2*g_nMax];        // 存放纵坐标
Node node[2*4*g_nMax];  // 节点

bool cmp(const Line& lhs, const Line& rhs)
{
    return lhs.x < rhs.x;
}

void TreeMake(int l, int r, int i)
{
    node[i].l = l;
    node[i].r = r;
    node[i].c = 0;
    node[i].len = 0;
    
    if (r == l + 1)
    {
        return ;
    }
    int m = (l + r) / 2;
    TreeMake(l, m, i*2);
    // 从m开始，而不是m+1，因为叶节点要计算长度
    TreeMake(m, r, i*2+1);
}

void TreeQuery(int i)
{
    // 有覆盖
    if (node[i].c > 0)
    {
        node[i].len = Y[node[i].r] - Y[node[i].l];
    }
    // 没有覆盖，达到叶节点
    else if (node[i].r - node[i].l == 1)
    {
        node[i].len = 0;
    }
    // 其他情况
    else
    {
        node[i].len = node[i*2].len + node[i*2+1].len;
    }
}

void TreeUpdate(Line li, int i)
{
    if (Y[node[i].l] == li.y1 && Y[node[i].r] == li.y2)
    {
        // “左”边flag是1 “右”边flag是-1
        // 其实是计算完一个矩形的面积之和，cover减去1
        // 就相当于把这个矩形擦除掉了
        node[i].c += li.flag;
    }
    else
    {
        int m = (node[i].l + node[i].r) / 2;
        if (li.y1 >= Y[m])
        {
            TreeUpdate(li, i*2+1);
        }
        else if (li.y2 <= Y[m])
        {
            TreeUpdate(li, i*2);
        }
        else
        {
            Line ll, lr;
            ll.y1 = li.y1;
            ll.y2 = Y[m];
            ll.flag = li.flag;
            lr.y1 = Y[m];
            lr.y2 = li.y2;
            lr.flag = li.flag;
            TreeUpdate(ll, i*2);
            TreeUpdate(lr, i*2+1);
        }
    }
    // 每次插入节点后，计算覆盖的长度
    TreeQuery(i);
}

int main(int argc, char **argv)
{
    //freopen("in.txt", "r", stdin);
    int x1, y1, x2, y2;
    int i, n;
    bool bContinue = true;
    
    while (bContinue)
    {
        i = 1;
        while (1)
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            if (x1 == -1)
            {
                break;
            }
            if (x1 == -2)
            {
                bContinue = false;
                break;
            }
            // 规定每条竖边的y2比y1大
            if (y1 > y2)
            {
                swap(y1, y2);
            }
            // 左边的边横坐标是x1，所以x1必须是小的一个
            if (x1 > x2)
            {
                swap(x1, x2);
            }
            line[i].x = x1;
            line[i].y1 = y1;
            line[i].y2 = y2;
            line[i].flag = 1;
            Y[i++] = y1;
            line[i].x = x2;
            line[i].y1 = y1;
            line[i].y2 = y2;
            line[i].flag = -1;  // 抵消上次的覆盖
            Y[i++] = y2;
        }
        n = i - 1;
        sort(line+1, line+n+1, cmp);
        sort(Y+1, Y+n+1);
        TreeMake(1, n, 1);
        TreeUpdate(line[1], 1);
        
        int res = 0;
        for (i = 2; i <= n; ++i)
        {
            res += node[1].len * (line[i].x - line[i-1].x);
            TreeUpdate(line[i], 1);
        }
        printf("%d\n", res);
    }
    
    return 0;
}