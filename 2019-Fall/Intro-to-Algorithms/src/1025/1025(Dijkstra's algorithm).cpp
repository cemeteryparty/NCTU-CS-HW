#include <iostream>
#include <vector>
#define INF 900000000000000000
// Single Source/All Destinations
// Dijkstra's algorithm
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

	long long int dis[n + 1][2], ans = 0;
	bool getAns[n + 1][2];

	std::vector<Edge> graph[n + 1]; // original graph
	std::vector<Edge> inverse_graph[n + 1]; // inverse vector of edge in graph

	for (int i = 0; i < m; i++) {
		int p1, p2, cost;
		scanf("%d%d%d", &p1, &p2, &cost);
		graph[p1].push_back(Edge(p2, cost));
		inverse_graph[p2].push_back(Edge(p1, cost));
	}
	for (int i = 0; i <= n; i++) {
		dis[i][0] = (!i)?0:INF;
		dis[i][1] = (!i)?0:INF;
		getAns[i][0] = (!i)?true:false;
		getAns[i][1] = (!i)?true:false;
	}

	int select = 0;
	while(select >= 0) {
		for (int i = 0; i < graph[select].size(); i++) {
			if (dis[select][0] + graph[select][i].cost < dis[graph[select][i].dest][0]) {
				dis[graph[select][i].dest][0] = dis[select][0] + graph[select][i].cost;
			}
		}
		long long int mindis = INF;
		select = -1;
		for (int i = 0; i <= n; i++) {
			if (!(getAns[i][0]) && dis[i][0] < mindis) {
				mindis = dis[i][0];
				select = i;
			}
		}
		if (select >= 0) { getAns[select][0] = true; }
	}

	select = 0;
	while (select >= 0) {
		for (int i = 0; i < inverse_graph[select].size(); i++) {
			if (dis[select][1] + inverse_graph[select][i].cost < dis[inverse_graph[select][i].dest][1]) {
				dis[inverse_graph[select][i].dest][1] = dis[select][1] + inverse_graph[select][i].cost;
			}
		}
		long long int mindis = INF;
		select = -1;
		for (int i = 0; i <= n; i++) {
			if (!(getAns[i][1]) && dis[i][1] < mindis) {
				mindis = dis[i][1];
				select = i;
			}
		}
		if (select >= 0) { getAns[select][1] = true; }
	}

	for (int i = 1; i <= n; i++) { ans += (dis[i][0] + dis[i][1]); }
	printf("%lld\n", ans);
	return 0;
}