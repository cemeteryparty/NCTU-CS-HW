#include <iostream>
#include <vector>
#define INF 90000000000000000
// All-Pairs Shortest Paths
// Floyd-Warshall algorithm
int main(int argc, char const *argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);
	long long int dis[n + 1][n + 1], ans = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dis[i][j] = i != j?INF:0;
		}
	}
	for (int i = 0; i < m; i++) {
		int p1, p2, cost;
		scanf("%d%d%d", &p1, &p2, &cost);
		dis[p1][p2] = cost;
	}
	for (int mid = 0; mid <= n; mid++) {
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				if (dis[i][mid] + dis[mid][j] < dis[i][j]) {
					dis[i][j] = dis[i][mid] + dis[mid][j];
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		ans += (dis[0][i] + dis[i][0]);
	}
	printf("%lld\n", ans);
	return 0;
}