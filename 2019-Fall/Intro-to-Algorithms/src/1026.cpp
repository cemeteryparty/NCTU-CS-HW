#include <iostream>
#include <vector>
#define INF 2147483647
// All-Pairs Shortest Paths
// Floyd-Warshall algorithm
int Minimum(int arg1, int arg2) {
	return arg1 < arg2?arg1:arg2;
}
int Maximum(int arg1, int arg2) {
	return arg1 > arg2?arg1:arg2;
}
int main(int argc, char const *argv[]) {
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	int dis[n][n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dis[i][j] = i != j?INF:0;
		}
	}
	for (int mi = 0; mi < m; mi++) {
		int i, j, k;
		scanf("%d%d%d", &i, &j, &k);
		dis[i][j] = Minimum(dis[i][j], k); // keep the minimal one
	}
	
	for (int mid = 0; mid < n; mid++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				dis[i][j] = Minimum(Maximum(dis[i][mid], dis[mid][j]), dis[i][j]);
			}
		}
	}
	for (int qi = 0; qi < q; qi++) {
		int i, j;
		scanf("%d%d", &i, &j);
		if (dis[i][j] == INF || dis[j][i] == INF) { printf("-1\n"); }
		else { printf("%d\n",Maximum(dis[i][j],dis[j][i])); }
	}
	return 0;
}