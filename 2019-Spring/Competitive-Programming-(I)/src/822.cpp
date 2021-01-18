#include <iostream>
#include <vector>
#define MAX_SIZE 10000000
// Problem: https://oj.nctu.edu.tw/problems/822/
int main (int argc, char const *argv[]) {
	long long int t = 0;
	scanf("%lld", &t);
	while (t--) {
		int n = 0;
		long long int l = 0, r = 0, ai = 0;
		scanf("%d%lld%lld", &n, &l, &r);
		bool ans = false;
		std::vector<bool> v;
		for (long long int i = 0; i <= r - l && i <= MAX_SIZE; i++) { v.push_back(false); }
		while (n--) {
			scanf("%lld", &ai);
			if (l <= ai && ai <= r && ai - l <= MAX_SIZE) { v[ai - l] = true; }
		}
		for (long long int i = 0; i <= r - l && i <= MAX_SIZE; i++) {
			if (!v[i]) {
				printf("%lld\n", l + i);
				ans = true;
				break;
			}
		}
		if (!ans) { printf("^v^\n"); }
	}	
	return 0;
}
