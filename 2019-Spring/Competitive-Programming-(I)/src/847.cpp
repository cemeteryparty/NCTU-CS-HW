#include <iostream>
#include <queue>
#include <map>
#include <vector>
// Problem: https://oj.nctu.edu.tw/problems/847/
int main(int argc, char const *argv[]) {
	int n = 0, q = 0;
	scanf("%d%d", &n, &q);
	int g[n]; bool process[n];
	std::map<int, std::vector<int> > m;
	for (int i = 0; i < n; i++) {
		process[i] = false;
		scanf("%d", g + i);
	}
	std::queue<int> group;
	int method = 0, pid = 0;
	while (q--) {
		scanf("%d", &method);
		if (method == 1) {
			scanf("%d", &pid);
			if (process[pid - 1]) {
				printf("Ignore\n");
				continue;
			}
			if (m[g[pid - 1]].empty()) { group.push(g[pid - 1]); }
			m[g[pid - 1]].push_back(pid);
			printf("Successful\n");
			process[pid - 1] = true;
		}
		else {
			if(group.empty()) { printf("0\n"); }
			else {
				printf("%d\n", m[group.front()].back());
				process[m[group.front()].back() - 1] = false;
				m[group.front()].pop_back();
				if (m[group.front()].empty()) { group.pop(); }
			}
		}
	}
	return 0;
}