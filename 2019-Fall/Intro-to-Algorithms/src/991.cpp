#include <iostream>

int main(int argc, char const *argv[]) {
	int M, a, b, c, d;
	scanf("%d", &M);
	while (M--) {
		long long int ans = 0, k = 1;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		while (true) {
			if (c == a && d == b) {
				ans += k;
				printf("%lld\n", ans % 524287);
				break;
			}
			if (d - c > 0) {
				k <<= 1;
				k %= 524287;
				d -= c;
			}
			else if (c - d > 0) {
				ans += k;
				k <<= 1;
				k %= 524287;
				ans %= 524287;
				c -= d;
			}
			else {
				ans = 0;
				break;
			}
		}
		if (!ans) { printf("-1\n"); }
	}
	return 0; 
}