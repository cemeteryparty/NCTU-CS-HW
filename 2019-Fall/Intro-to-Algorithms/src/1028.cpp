#include <iostream>
#include <queue>
#define INF 2147483647
// vc = # of vertex = m + n + 2(vertex count)
// s: vc - 2 = m + n
// t: vc - 1 = m + n + 1
// prop: 0 ~ m - 1, idea: m ~ m + n- 1
int vc, parent[262], flow[262][262];
int Minimum(int arg1, int arg2) {
	return arg1 < arg2?arg1:arg2;
}
bool BFS(){
	bool canReach[vc];
	for(int i = 0; i < vc; i++) {
		canReach[i] = i != vc - 2?false:true;
	}
	std::queue<int> q;
	q.push(vc - 2);
	while (!q.empty()) {
		int pos = q.front();
		q.pop();
		for (int i = 0; i < vc; i++) {
			if(flow[pos][i] && !canReach[i]){
				canReach[i] = true;
				parent[i] = pos;
				q.push(i);
			}
		}
	}
	return canReach[vc - 1];
}
int main(int argc, char const *argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);
	vc = m + n + 2;
	for (int i = 0; i < vc; i++){
		parent[i] = -1;
		for(int j = 0; j < vc; j++) {
			flow[i][j] = 0;
		}
	}
	int profit = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &flow[m + i][vc - 1]); // flow idea[i]->output(t)
		profit += flow[m + i][vc - 1];
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &flow[vc - 2][i]); // flow input(s)->prop[i]
	}
	
	for (int i = 0; i < n; i++) { // idea
		int k, p;
		scanf("%d", &k);
		for (int ki = 0; ki < k; ki++) {
			scanf("%d", &p); // prop
			flow[p][m + i] = INF; // prop[p]->idea[i]
		}
	}
	while (BFS()) {
		int minflow = INF;
		for(int i = vc - 1; i != vc - 2; i = parent[i]) {
			minflow = Minimum(flow[parent[i]][i], minflow);
		}
		for (int i = vc - 1; i != vc - 2; i = parent[i]){
			flow[parent[i]][i] -= minflow;
			flow[i][parent[i]] += minflow;
		}
		profit -= minflow;
	}
	printf("%d\n", profit);
	return 0;
}