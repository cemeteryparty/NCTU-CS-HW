#include <iostream>
#include <algorithm>
// Problem: https://oj.nctu.edu.tw/problems/844/
int main(int argc, char const *argv[]) {
	int n = 0, k = 0;
	scanf("%d%d", &n, &k);
	int a[n];
	for (int i = 0; i < n; i++) { scanf("%d",(a + i)); }
	bool output = false;
	while (std::next_permutation(a, a + n) && k--) {
		for (int i = 0; i < n; i++) { printf("%d ", a[i]); }
		printf("\n");
		output = true;
	}
	if (!output) { printf("hello world!\n"); }
	return 0; 
}