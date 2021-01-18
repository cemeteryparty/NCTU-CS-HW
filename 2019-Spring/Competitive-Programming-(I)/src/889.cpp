#include <iostream>
#include <cmath>
#include <vector>
// Problem: https://oj.nctu.edu.tw/problems/889/
int gcd(int x, int y){
	if (y == 0) { return x; }
	else { return gcd(y, x % y); }
}
int main(int argc, char const *argv[]){ 
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		int n = 0, q = 0;
		scanf("%d%d", &n, &q);
		int level = ceil(log(n) / log(2)) + 1;
		std::vector<int> v[level];
		for (int li = 0; li < level; li++) {
			if(!li) { 
				for (int ni = 0; ni < n; ni++) { v[li].push_back(1); }
			}
			else {
				int ni = 0;
				for (int ni = 0; ni < v[li - 1].size() / 2; ni++) {
					v[li].push_back(gcd(v[li - 1][ni * 2],v[li - 1][ni * 2 + 1]));
				}
				if (v[li - 1].size() & 1) {
					v[li].push_back(v[li - 1][v[li - 1].size() - 1]);
				}
			}
		}
		while (q--) {
			int t = 0, x = 0, k = 0;
			scanf("%d%d%d", &t, &x, &k);
			x--;
			if (t == 1) {
				v[0][x] = k;
				for (int li = 1; li < level; li++) {
					if (x & 1) { v[li][x >> 1] = gcd(v[li - 1][x], v[li - 1][x - 1]); }
					else if (x + 1 == v[li - 1].size()) { v[li][x >> 1] = v[li - 1][x]; }
					else { v[li][x >> 1] = gcd(v[li - 1][x],v[li - 1][x + 1]); }
					x >>= 1;
				}
			}
			else {
				int cast = v[0][x], li = 0;
				if (cast <= k) {
					printf("%d\n", x + 1);
					continue;
				}
				bool ans = false;
				for (li = 0; li < level && x < v[li].size(); li++) {
					if (gcd(cast, v[li][x]) <= k) {
						ans = true;
						break;
					}
					cast = gcd(cast, v[li][x]);
					if (x & 1) { x = (x >> 1) + 1; }
					else { x >>= 1; }
				}
				if (!ans) {
					printf("DOYA!\n");
					continue;
				}
				for (int rli = li; rli >= 1; rli--) {
					if (gcd(cast, v[rli - 1][x << 1]) <= k) { x <<= 1; }
					else {
						cast = gcd(cast, v[rli - 1][x << 1]);
						x = (x << 1) + 1;
					}
				}
				printf("%d\n", x + 1);
			}
		}
	}		
	return 0;
}