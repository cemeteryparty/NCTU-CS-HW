#include <iostream>
#include <algorithm>
#define INF 1000000001

int main(int argc, char const *argv[]) {
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	int arr[n];
	for(int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	while (m--) {
		scanf("%d%d", &i, &j);
		int temp[j - i + 1];
		for(int x = 0; x <= j - i; x++) {
			temp[x] = arr[i + x];
		}
		int min1 = INF, min2 = INF, count = 0;
		for(int x = 0; x <= j - i; x++) {
			if (temp[x] < min1) { min1 = temp[x]; }
		}
		for (int x = 0; x <= j - i; x++) {
			if (temp[x] == min1) { count++; }
			if (count >= 2) {
				printf("%d\n", min1);
				count = 0;
				break;
			}
			if (temp[x] < min2 && temp[x] != min1) {
				min2 = temp[x];
			}
		}
		if (count) { printf("%d\n", min2); }
	}
	return 0;
}