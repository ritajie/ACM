/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <bits/stdc++.h>
using namespace std;

struct Line
{
    double x;
    double y1;     // min
    double y2;     // max
    int flag;   // left 1, right -1
};

struct Node
{
    int l;
    int r;
    int c;
    double len;
};

Line line[1010*2];
double Y[1010*2];
Node node[1010*2*4];
const double EPS = 1e-6;

bool cmp(const Line& lhs, const Line& rhs)
{
    if (fabs(lhs.x - rhs.x) <= EPS)
    {
        // 横坐标重叠的时候，优先扫描左边
        return lhs.flag > rhs.flag;
        // 好像是没有影响，实际提交测试也是这样的
    }
    return lhs.x < rhs.x ;
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
    TreeMake(m, r, i*2+1);
}

void TreeQuery(int i)
{
    if (node[i].c > 1) // 至少覆盖两次
    {
        node[i].len = Y[node[i].r] - Y[node[i].l];
    }
    else if (node[i].r - node[i].l == 1)
    {
        node[i].len = 0;
    }
    else
    {
        node[i].len = node[i*2].len + node[i*2+1].len;
    }
}

void TreeUpdate(Line li, int i)
{
    if (fabs(Y[node[i].l] - li.y1) <= EPS && fabs(Y[node[i].r] - li.y2) <= EPS)
    {
        node[i].c += li.flag;
    }
    //else
    // 这里需要把覆盖属性往子节点传下去
    // 因为对某一个节点没有多次覆盖，可能会对子节点有多次覆盖
    if (node[i].r > node[i].l + 1)
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
            TreeUpdate(lr, i*2 + 1);
        }
    }
    TreeQuery(i);
}

int main(int argc, char **argv)
{
    //freopen("in.txt", "r", stdin);
    
    int nCount = 0;
    int n, i, j;
    double x1, y1, x2, y2;
    
    scanf("%d", &nCount);
    while (nCount--)
    {
        scanf("%d", &n);
        j = 1;
        for (i = 0; i < n; ++i)
        {
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y1);
            line[j].x = x1;
            line[j].y1 = y1;
            line[j].y2 = y2;
            line[j].flag = 1;
            Y[j++] = y1;
            line[j].x = x2;
            line[j].y1 = y1;
            line[j].y2 = y2;
            line[j].flag = -1;
            Y[j++] = y2;
        }
        
        n = j - 1;
        sort(Y+1, Y+n+1);
        sort(line+1, line+n+1, cmp);
        // Y去重
        j = 1;
        for (i = 1; i <= n; ++i)
        {
            if (fabs(Y[i] - Y[j]) <= EPS) continue;
            Y[++j] = Y[i];
        }
        TreeMake(1, j, 1);
        TreeUpdate(line[1], 1);
        
        double res = 0.0;
        for (i = 2; i <= n; ++i)
        {
            res += (line[i].x - line[i-1].x)*node[1].len;
            TreeUpdate(line[i], 1);
        }
        
        printf("%.2f\n", res);
    }

    return 0;
}