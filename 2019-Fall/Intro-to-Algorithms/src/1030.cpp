#include <iostream>
#include <map>

int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	std::map<int, int> m;
	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		m[a]++; m[b]--;
	}
	int time = -1, ans = -1, mice = 0;
	for (std::map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
		mice += it->second;
		if (mice > ans) {
			time = it->first;
			ans = mice;
		}
	}
	printf("%d %d\n", time, ans);
	return 0;
}