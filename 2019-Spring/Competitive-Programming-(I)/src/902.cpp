#include <iostream>
#include <cmath>
// Problem: https://oj.nctu.edu.tw/problems/902/
int main(int argc, char const *argv[]) { 
	long long int p2[60];
	p2[0] = 1;
	for(int i = 1 ;i < 60; i++)
		p2[i] = p2[i - 1] * 2;
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		int n = 0, q = 0;
		scanf("%d%d", &n, &q);
		while (q--) {
			int t = 0;
			scanf("%d", &t);
			if (t == 1) {
				long long int r, c;
				scanf("%lld%lld", &r, &c);
				r--; c--;
				long long int ans = 1;
				while (r | c) {
					long long int p = (r > c)?log(r) / log(2):log(c) / log(2);
					long long int mod = p2[p];
					long long int k = 2 * (r / mod) + c / mod;
					ans += k * p2[p * 2];
					r %= mod; c %= mod;
				}
				printf("%lld\n", ans);
			}
			else {
				long long int i = 0, r = 1, c = 1, k = 1;
				scanf("%lld", &i);
				i--;
				while (i != 0) {
					if (i % 4 == 1) { c += k; }
					else if (i % 4 == 2) { r += k; }
					else if (i % 4 == 3) { c += k; r += k; }
					k *= 2;
					i /= 4;
				}
				printf("%lld %lld\n", r, c);
			}
		}
	}
	return 0;
}