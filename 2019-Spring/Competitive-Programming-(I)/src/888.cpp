#include <iostream>
#include <cmath>
#include <vector>
// Problem: https://oj.nctu.edu.tw/problems/888/
int main(int argc, char const *argv[]) {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		int n = 0, q = 0;
		scanf("%d%d", &n, &q);
		int level = ceil(log(n) / log(2)) + 1;
		std::vector<int> v[level];
		for (int li = 0; li < level; li++) {
			if (!li) {
				for (int ni = 0; ni < n; ni++) { v[li].push_back(1); }
			}
			else {
				for(int ni = 0; ni < v[li - 1].size() / 2; ni++) {
					v[li].push_back(v[li - 1][ni * 2] + v[li - 1][ni * 2 + 1]);
				}
				if (v[li - 1].size() & 1) {
					v[li].push_back(v[li - 1][v[li - 1].size() - 1]);
				}
			}
		}
		while (q--) {
			int t = 0, x = 0;
			scanf("%d%d", &t, &x);
			if (t == 1) {
				x--;
				if (!v[0][x]) { continue; }
				for (int li = 0; li < level; li++) {
					v[li][x]++;
					x /= 2;
				}
			}
			else if (t == 2) {
				x--;
				if (!v[0][x]) { continue; }
				int div = v[0][x] - 1;
				for(int li = 0;li < level;li++){
					v[li][x] -= div;
					x /= 2;
				}
			}
			else {
				if (v[level - 1][0] < x) { printf("endro~!\n"); }
				else {
					int index = 0;
					for (int li = level - 1; li > 0 ;li--) {
						v[li][index]--;
						if (x > v[li - 1][2 * index]) {
							x -= v[li - 1][2 * index];
							index = 2 * index + 1;
						}
						else { index = 2 * index; }
					}
					v[0][index]--;
					printf("%d\n", index + 1);
				}
			}
		}
	}
	return 0;
}