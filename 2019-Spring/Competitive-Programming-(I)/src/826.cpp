#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/826/
int main(int argc, char const *argv[]) {
	long long int n = 0, m = 0;
	int q = 0;
	scanf("%d%d%d", &n, &m, &q);
	bool cho[n][m];
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) { cho[x][y] = true;	}
	}
	int total = n * m;
	while (q--) {
		int i = 0, j = 0, count = 0;
		scanf("%d%d", &i, &j);
		for (int x = i - 1; x >= 0 && cho[x][j - 1]; x--) {
			for (int y = j - 1; y >= 0; y--) {
				if (!cho[x][y]) { break; }
				count++;
				cho[x][y] = false;
			}
		}
		if (!count) { printf("QAQ\n"); }
		else { printf("%d\n", count); }
		total -= count;
	}
	printf("%d\n", total);
	return 0;
}