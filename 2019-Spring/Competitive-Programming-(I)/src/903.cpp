#include <iostream>
#include <algorithm>
// Problem: https://oj.nctu.edu.tw/problems/903/
class dot {
public:
	int x, y;
	friend bool operator<(const dot & d1, const dot & d2) {
		if (d1.x < d2.x) { return true; }
		else if(d1.y < d2.y && d1.x == d2.x) { return true; }
		else { return false; }
	}
	friend bool flag(const dot & d1, const dot & d2) {
		int dx = d1.x - d2.x, dy = d1.y - d2.y;
		if(dx >= 0 && dy >= 0) { return true; }
		else { return false; }
	}
};
int main(int argc, char const *argv[]) {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		int n = 0, max_index = 1;
		scanf("%d", &n);
		dot data[n], dp[n];
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			data[i].x = x; data[i].y = y;
			dp[i].x = 2100000000; dp[i].y = 2100000000;
		}
		std::sort(data, data + n);
		dp[0] = data[0];
		for (int i = 1; i < n; i++) {
			int lower = 0, upper = n - 1, mid = -1;
			while (lower < upper) {
				mid = (lower + upper) >> 1;
				if (flag(data[i], dp[mid])) { // can data[i] pad after dp[mid]
					lower = mid + 1;
				}
				else { upper = mid; }
			}
			dp[lower] = data[i];
			if (lower > max_index) { max_index = lower; }
		}
		printf("%d\n", max_index + 1);
	}
	return 0;
}