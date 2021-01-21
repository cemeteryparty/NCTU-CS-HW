#include <iostream>
#include <algorithm>
#include <vector>

class Edge {
public:
	int src, dest, cost;
	Edge(int SRC = -1, int DEST = -1, int COST = -1) {
		src = SRC;
		dest = DEST;
		cost = COST;
	}
	friend bool operator<(const Edge & e1, const Edge & e2) {
		return e1.cost < e2.cost;
	}
};
int group[500000];
int FindGroup(int key) {
	while (key != group[key]) { key = group[key]; }
	return key;
}
void UnionGroup(int key1, int key2) {
	int g1 = FindGroup(key1), g2 = FindGroup(key2);
	if (g1 < g2) { group[g2] = g1; }
	else { group[g1] = g2; }
}
int main(int argc, char const *argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) { group[i] = i; }
	std::vector<Edge> graph;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		graph.push_back(Edge(a, b, c));
	}
	std::sort(graph.begin(), graph.end());
	long long int ans = 0;
	for (int i = graph.size() - 1; i >= 0; i--) {
		int g1 = FindGroup(graph[i].src), g2 = FindGroup(graph[i].dest);
		if (g1 == g2) { continue; }
		ans += graph[i].cost;
		UnionGroup(g1, g2);
	}
	printf("%lld\n", ans);
	return 0;
}