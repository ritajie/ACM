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
    double y1;  // min
    double y2;  // max
    int flag;   // left 1, right -1
};

struct Node
{
    int l;      // left
    int r;      // right
    int c;      // cover
    double len; // length
};

Line line[110*2];
Node node[110*2*3];
double Y[110*2];
const double EPS = 1e-6;

bool cmp(const Line& lhs, const Line& rhs)
{
    return lhs.x < rhs.x;
}

void TreeMake(int left, int right, int i)
{
    node[i].l = left;
    node[i].r = right;
    node[i].c = 0;
    node[i].len = 0.0;
    
    if (right == left + 1)
    {
        return ;
    }
    
    int mid = (left + right) / 2;
    TreeMake(left, mid, i*2);
    TreeMake(mid, right, i*2+1);
}

void TreeQuery(int i)
{
    if (node[i].c > 0)
    {
        node[i].len = Y[node[i].r] - Y[node[i].l];
    }
    else if (node[i].l + 1 == node[i].r)
    {
        node[i].len = 0;
    }
    else
    {
        node[i].len = node[i*2].len + node[i*2+1].len;
    }
}

void TreeUpdate(const Line& li, int i)
{
    if (fabs(Y[node[i].l] - li.y1) <= EPS &&
        fabs(Y[node[i].r] - li.y2) <= EPS)
    {
        node[i].c += li.flag;
    }
    else
    {
        int m = (node[i].l + node[i].r) / 2;
        if (li.y2 <= Y[m])
        {
            TreeUpdate(li, i*2);
        }
        else if (li.y1 >= Y[m])
        {
            TreeUpdate(li, i*2+1);
        }
        else
        {
            Line ll, lr;
            ll.x = li.x;
            ll.y1 = li.y1;
            ll.y2 = Y[m];
            ll.flag = li.flag;
            lr.x = li.x;
            lr.y1 = Y[m];
            lr.y2 = li.y2;
            lr.flag = li.flag;
            TreeUpdate(ll, i*2);
            TreeUpdate(lr, i*2+1);
        }
    }
    TreeQuery(i);
}

int main(int argc, char **argv)
{
    //freopen("in.txt", "r", stdin);
    int n, i, j, k = 0;
    double x1, y1, x2, y2;
    
    while (scanf("%d", &n), n)
    {
        ++k;
        j = 1;
        for (i = 1; i <= n; ++i)
        {
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            line[j].x  = x1;
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
        sort(line+1, line+n+1, cmp);
        sort(Y+1, Y+n+1);
        j = 1;
        for (i = 1; i <= n; ++i)
        {
            if (fabs(Y[i] - Y[j]) <= EPS) continue;
            Y[++j] = Y[i];
        }
        TreeMake(1, j, 1);
        TreeUpdate(line[1], 1);
        
        double res = 0;
        for (i = 2; i <= n; ++i)
        {
            res += node[1].len * (line[i].x - line[i-1].x);
            TreeUpdate(line[i], 1);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", k, res);
    }

    return 0;
}