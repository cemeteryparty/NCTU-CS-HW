#include <iostream>
#include <vector>
#include <queue>
#define INF 2147483647

class Frontier {
public:
	int I, COST;
	Frontier(int index, int cost) {
		I = index;
		COST = cost;
	}
	friend bool operator>(const Frontier & f1, const Frontier & f2) {
		return f1.COST > f2.COST;
	}
};
class Edge {
public:
	int dest, cost;
	Edge(int DEST = -1, int COST = -1) {
		dest = DEST;
		cost = COST;
	}
};
int main(int argc, char const *argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);
	bool inTree[n];
	int vcost[n], dis[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", vcost + i);
		dis[i] = i?INF:vcost[i];
		inTree[i] = false;
	}
	std::vector<Edge> graph[n];
	for (int i = 0; i < m; i++) {
		int a,b,c;
		scanf("%d%d%d", &a, &b, &c);
		graph[a].push_back(Edge(b, c));
		graph[b].push_back(Edge(a, c));
	}
	std::priority_queue<Frontier, std::vector<Frontier>, std::greater<Frontier> > q;
	q.push(Frontier(0, 0));
	while (!q.empty()) {
		Frontier f = q.top();
		q.pop();
		int select = f.I;
		if (inTree[select]) { continue; }
		inTree[select] = true;
		for (int i = 0; i < graph[select].size(); i++) {
			int total = dis[select] + graph[select][i].cost + vcost[graph[select][i].dest];
			if (total < dis[graph[select][i].dest]) {
				dis[graph[select][i].dest] = total;
				q.push(Frontier(graph[select][i].dest, total));
			}
		}
	}
	long long int ans = 0;
	for (int i = 0; i < n; i++) { ans += dis[i]; }
	printf("%lld\n", ans);
	return 0;
}