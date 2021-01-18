#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/857/
int main(int argc, char const *argv[]) {
	int n = 0, q = 0;
	scanf("%d%d", &n, &q);
	int xor_arr[n + 1], num;
	xor_arr[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &num);
		xor_arr[i] = num ^ xor_arr[i - 1];
	}
	while (q--) {
		int l = 0, r = 0;
		scanf("%d%d", &l, &r);
		printf("%d\n", xor_arr[l - 1] ^ xor_arr[r]);
	}
	return 0;
}