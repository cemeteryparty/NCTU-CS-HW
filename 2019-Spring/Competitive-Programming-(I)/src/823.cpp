#include <cstdio>
#include <vector>
// Problem: https://oj.nctu.edu.tw/problems/823/
int main(){
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n;
		scanf("%d", &n);
		static int a[1000005];
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		int ans = 0;
		std::vector<int> v;
		for (int i = n - 1; i >= 0; i--) {
			if (!v.empty() && a[i] >= v.back()) {
				if (v.size() > ans) { ans = v.size(); }
				while (!v.empty() && v.back() <= a[i]) { v.pop_back(); }
			}
			v.push_back(a[i]);
		}
		if (!v.empty() && v.size() > ans) { ans = v.size(); }
		printf("%d\n", ans);
	}
	return 0;
}
