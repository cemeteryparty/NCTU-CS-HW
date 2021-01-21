#include <iostream>
#include <algorithm>
#include <vector>
// Kruskal's algorithm
class Edge {
public:
	int src, dest, cost;
	Edge() = default;
	Edge(int SRC, int DEST, int COST) {
		src = SRC;
		dest = DEST;
		cost = COST;
	}
	friend bool operator<(Edge e1, Edge e2) {
		return e1.cost < e2.cost;
	}
};
int group[100001];
int FindGroup(int key) {
	while (key != group[key]) { key = group[key]; }
	return key;
}
void UNION(int key1, int key2) {
	if (key1 < key2) { group[key2] = key1; }
	else { group[key1] = key2; }
}
int main(int argc, char const *argv[]){
	int n, m, edge_count = 0; // n verteies m edge railway cost w
	long long int min_cost = 0, w;

	scanf("%d%d%lld", &n, &m, &w);
	// init disjointset
	for(int key = 0; key < n; key++) { group[key] = key; }
	// edge
	std::vector<Edge> e;
	for (int i = 0; i < m; i++) {
		int src, dest, cost;
		scanf("%d%d%d", &src, &dest, &cost);
		if (w >= cost) { e.push_back(Edge(src, dest, cost)); }
	}

	// find mst
	std::sort(e.begin(), e.end());
	for (int i = 0; i < e.size(); i++) {
		int key1 = FindGroup(e[i].src), key2 = FindGroup(e[i].dest);
		if (key1 == key2) { continue; }
		UNION(key1, key2);
		edge_count++;
		min_cost += e[i].cost;
	}

	if (edge_count < n - 1) { printf("%lld\n", min_cost + w * (n - 1 - edge_count)); }
	else { printf("%lld\n", min_cost); }
	return 0;
}
