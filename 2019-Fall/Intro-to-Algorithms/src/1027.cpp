#include <iostream>
#include <queue>
#define INF 2147483647

int parent[300],n,flow[300][300];
int Minimum(int arg1, int arg2){
	return arg1 < arg2?arg1:arg2;
}
bool BFS(){
	bool canReach[n];
	for (int i = 0; i < n; i++) {
		canReach[i] = i?false:true;
	}
	std::queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int pos = q.front();
		q.pop();
		for (int i = 0; i < n; i++) {
			if(flow[pos][i] && !canReach[i]){
				canReach[i] = true;
				parent[i] = pos;
				q.push(i);
			}
		}
	}
	return canReach[n - 1];
}
int main(int argc, char const *argv[]) {
	int m, ans = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
		for (int j = 0; j < n; j++) { flow[i][j] = 0; }
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		flow[a][b]++;
		flow[b][a]++;
	}
	while (BFS()) {
		int minflow = INF;
		for (int i = n - 1; i > 0; i = parent[i]) {
			minflow = Minimum(Minimum(flow[parent[i]][i], flow[i][parent[i]]), minflow);
		}
		for (int i = n - 1; i > 0; i = parent[i]) {
			flow[parent[i]][i] -= minflow;
			flow[i][parent[i]] -= minflow;
		}
		ans += minflow;
	}
	printf("%d\n", ans);
	return 0;
}