#include <iostream>
#include <cmath>
#include <vector>

int maximum(const int & n1, const int & n2) {
	return n1 > n2?n1:n2;
}
int main(int argc, char const *argv[]) { 
	int n, m, num;
	scanf("%d%d", &n, &m);
	int level = ceil(log(n) / log(2)) + 1;
	std::vector<int> v[level]; // segment tree
	for (int i = 0; i < n; i++){
		scanf("%d", &num);
		v[0].push_back(num);
	}
	for (int li = 1; li < level; li++) {
		int ni = 0;
		for (int ni = 0; ni < v[li - 1].size() / 2; ni++) {
			v[li].push_back(maximum(v[li - 1][ni * 2], v[li - 1][ni * 2 + 1]));
		}
		if (v[li - 1].size() & 1) {
			v[li].push_back(v[li - 1][v[li - 1].size() - 1]);
		}
	}
	while (m--) {
		int t = 0, j = 0, k = 0;
		scanf("%d%d%d", &t, &j, &k);
		if (t == 1) {
			v[0][j] = k;
			for (int li = 1; li < level; li++) {
				if (j & 1) {
					v[li][j >> 1] = maximum(v[li - 1][j],v[li - 1][j - 1]);
				}
				else if (j + 1 == v[li - 1].size()) {
					v[li][j >> 1] = v[li - 1][j];
				}
				else {
					v[li][j >> 1] = maximum(v[li - 1][j],v[li - 1][j + 1]);
				}
				j >>= 1;
			}
		}
		else if (t == 2) {
			int ans = -2100000000;
			for (int li = 0; li < level && j <= k; li++){
				if (j == k) {
					ans = maximum(ans, v[li][j]);
					break;
				}
				if (j & 1) {
					ans = maximum(ans, v[li][j]);
					j = (j >> 1) + 1;
				}
				else { j >>= 1; }
				if (k & 1) { k >>= 1; }
				else {
					ans = maximum(ans, v[li][k]);
					k = (k >> 1) - 1;
				}
			}
			printf("%d\n", ans);
		}
		else {
			for (int li = 0; li < level; li++) {
				for (int i = 0; i < v[li].size(); i++) { printf("%d ",v[li][i]); }
				printf("\n");
			}
		}
	}
	return 0;
}