/*
    Author: Yuki
    GitHub: https://github.com/Yuki-14544869/
    Blog:   http://https://yuki-14544869.github.io/
*/
#include <bits/stdc++.h>
using namespace std;
typedef struct Edge {
	int u, v;
	int w;
	int flag;
}Edge;
Edge e[10005];
int fa[105];
int n, m,i;
bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}
 
int find_set(int x) {
	if(fa[x] == x) return x;
	else return find_set(fa[x]); 
}
void union_set(int x,int y)
{
	int root_x = find_set(x);
	int root_y = find_set(y);
	if(root_x != root_y)
		fa[root_x] = root_y;
}
int main() {
	while(~scanf("%d", &n), n) 
	{
		int ans;
		m = n * (n - 1) / 2;
		for(i = 0; i < m; i++) 
			scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].w, &e[i].flag);
		sort(e, e + m, cmp);
		for(int i = 1; i <= n; i++)
			fa[i] = i;
		for(int i = 0; i < m; i++) {
			if(1 == e[i].flag) { 
				union_set(e[i].u,e[i].v);
			}
		}
		ans = 0;
		for(int i = 0; i < m; i++) {
			if(0 == e[i].flag) {
				int t1 = find_set(e[i].u);
				int t2 = find_set(e[i].v);
				if(t1 != t2) {
					fa[t1] = t2;
					ans += e[i].w;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
