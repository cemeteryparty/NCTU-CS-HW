#include <iostream>
#include <vector>
#include <queue>

class Edge {
public:
	int dest, cost;
	Edge() = default;
	Edge(int DEST, int COST) {
		dest = DEST;
		cost = COST;
	};
};
class pos_info {
public:
	int src, pos;
	long long int grandcost;
	pos_info(int SRC,int POS, long long int GRANDCOST){
		src = SRC;
		pos = POS;
		grandcost = GRANDCOST;
	}
};
std::vector<Edge> v[100000]; // adjacency lists
long long int BFS(int begin, bool flag){
	long long int max_len = -1;
	std::queue<pos_info> q;
	q.push(pos_info(-1, begin, 0));
	while (!q.empty()) {
		int pos = q.front().pos, src = q.front().src;
		long long int grandcost = q.front().grandcost;
		q.pop();
		for (int i = 0; i < v[pos].size(); i++) {
			if (v[pos][i].dest != src) {
				q.push(pos_info(pos, v[pos][i].dest, grandcost + v[pos][i].cost));
			}
		}
		if (grandcost > max_len) {
			max_len = grandcost;
			begin = pos;
		}
	}
	if (flag) { return max_len; }
	return begin;
}
int main (int argc, char const *argv[]) {
	int n; // vertex 1 ~ n, n - 1 edge
	long long int ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i++) {
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		v[a].push_back(Edge(b, l));
		v[b].push_back(Edge(a, l));
		ans += (l << 1);
	}
	ans -= BFS(BFS(1, false), true); // 2 times of all path - longest path
	printf("%lld\n", ans);
	return 0;
}
